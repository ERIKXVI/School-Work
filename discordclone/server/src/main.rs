use futures_util::{SinkExt, StreamExt};
use hyper::service::{make_service_fn, service_fn};
use hyper::upgrade::Upgraded;
use hyper::{Body, Request, Response, Server};
use hyper::{Method, StatusCode};
use std::convert::Infallible;
use std::net::SocketAddr;
use tokio_tungstenite::WebSocketStream;

async fn handle_connection(mut ws: WebSocketStream<Upgraded>) {
    println!("User connected");

    while let Some(msg) = ws.next().await {
        match msg {
            Ok(msg) => {
                println!("Received message: {}", msg);
                ws.send(msg).await.unwrap();
            }
            Err(_) => {
                break;
            }
        }
    }
}

async fn handle(req: Request<Body>) -> Result<Response<Body>, Infallible> {
    match (req.method(), req.uri().path()) {
        (&Method::GET, "/") => Ok(Response::new(Body::from("Hello, World!"))),
        (&Method::GET, "/ws") => match hyper::upgrade::on(req).await {
            Ok(upgraded) => {
                let ws_stream = WebSocketStream::from_raw_socket(
                    upgraded,
                    tokio_tungstenite::tungstenite::protocol::Role::Server,
                    None,
                )
                .await;
                tokio::spawn(handle_connection(ws_stream));
                Ok(Response::new(Body::empty()))
            }
            Err(_) => {
                let mut not_found = Response::default();
                *not_found.status_mut() = StatusCode::NOT_FOUND;
                Ok(not_found)
            }
        },
        _ => {
            let mut not_found = Response::default();
            *not_found.status_mut() = StatusCode::NOT_FOUND;
            Ok(not_found)
        }
    }
}

#[tokio::main]
pub async fn main() -> Result<(), Box<dyn std::error::Error + Send + Sync>> {
    let addr = SocketAddr::from(([127, 0, 0, 1], 3000));

    let make_svc = make_service_fn(|_conn| async { Ok::<_, Infallible>(service_fn(handle)) });

    let server = Server::bind(&addr).serve(make_svc);

    println!("Listening on http://{}", addr);

    server.await?;

    Ok(())
}
