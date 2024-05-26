use futures_util::{SinkExt, StreamExt};
use once_cell::sync::Lazy;
use std::sync::Arc;
use tokio::net::TcpStream;
use tokio::sync::{Mutex, RwLock};
use tokio_tungstenite::{
    connect_async, tungstenite::protocol::Message, MaybeTlsStream, WebSocketStream,
};

static WS_STREAM: Lazy<RwLock<Option<Arc<Mutex<WebSocketStream<MaybeTlsStream<TcpStream>>>>>>> =
    Lazy::new(|| RwLock::new(None));

#[tauri::command]
async fn connect_to_server(window: tauri::Window, url: String) {
    match connect_async(&url).await {
        Ok((ws_stream, _)) => {
            let ws_stream = Arc::new(Mutex::new(ws_stream));
            *WS_STREAM.write().await = Some(ws_stream.clone());

            tokio::spawn(async move {
                let mut ws_stream = ws_stream.lock().await;
                while let Some(msg) = ws_stream.next().await {
                    match msg {
                        Ok(msg) => {
                            if let Message::Text(text) = msg {
                                window.emit("message", Some(text)).unwrap();
                            }
                        }
                        Err(e) => {
                            println!("Failed to receive message: {:?}", e);
                            break;
                        }
                    }
                }
            });
        }
        Err(e) => {
            println!("Failed to connect: {:?}", e);
        }
    }
}

#[tauri::command]
async fn send_message(message: String) {
    if let Some(ws_stream) = &*WS_STREAM.read().await {
        let mut ws_stream = ws_stream.lock().await;
        if let Err(e) = ws_stream.send(Message::Text(message)).await {
            println!("Failed to send message: {:?}", e);
        }
    }
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![connect_to_server, send_message])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}