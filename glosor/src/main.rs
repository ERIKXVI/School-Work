mod db;
mod test_manager;

use dotenv::dotenv;
//use sqlx::pool;
use tokio;

#[tokio::main]
async fn main() -> Result<(), sqlx::Error> {
    dotenv().ok();

    Ok(())
}
