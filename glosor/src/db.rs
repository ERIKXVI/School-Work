use rusqlite::{Connection, Result};

pub fn connect() -> Result<Connection> {
    let database_url = "sqlite:my_rust_app.db";
    Connection::open(&database_url)
}
