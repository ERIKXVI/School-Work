use futures_util::StreamExt;
use futures_util::SinkExt; // Add this line
use std::sync::{Arc, Mutex};
use tokio::net::TcpStream;
use tokio_tungstenite::{connect_async, tungstenite::protocol::Message, MaybeTlsStream, WebSocketStream};
use std::sync::RwLock;
use once_cell::sync::Lazy;

static WS_STREAM: Lazy<RwLock<Option<Arc<Mutex<WebSocketStream<MaybeTlsStream<TcpStream>>>>>> = Lazy::new(|| RwLock::new(None));

#[tauri::command]
async fn connect_to_server(window: tauri::Window, url: String) {
    let (ws_stream, _) = connect_async(&url).await.unwrap();
    let ws_stream = Arc::new(Mutex::new(ws_stream)); // Wrap ws_stream in Arc<Mutex<>> here
    *WS_STREAM.write().unwrap() = Some(ws_stream.clone()); // Now you can clone it

    tokio::spawn(async move {
        let mut ws_stream = ws_stream.lock().unwrap();
        while let Some(msg) = ws_stream.next().await {
            match msg {
                Ok(msg) => {
                    if let Message::Text(text) = msg {
                        window.emit("message", Some(text)).unwrap();
                    }
                }
                Err(_) => break,
            }
        }
    });
}

#[tauri::command]
async fn send_message(message: String) {
    let ws_stream = WS_STREAM.read().unwrap();
    if let Some(ws_stream) = &*ws_stream {
        ws_stream
            .send(Message::Text(message))
            .await
            .unwrap();
    }
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![connect_to_server, send_message])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}