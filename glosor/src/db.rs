use sqlx::{Error, MySqlPool};

pub async fn connect() -> Result<MySqlPool, Error> {
    dotenv::dotenv().ok();
    let database_url = std::env::var("DATABASE_URL").expect("DATABASE_URL must be set");
    MySqlPool::connect(&database_url).await
}
