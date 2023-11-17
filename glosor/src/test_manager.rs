use rusqlite::{params, Connection, Result};
use std::{fmt::format, simd::SimdConstPtr};

pub fn create_test(conn: &Connection, name: &str, max_attempts: i32) -> Result<i64> {
    let test_table_name = format!("{}_questions", name.replace("", "_"));

    conn.execute(&format!("CREATE TABLE IF IF NOT EXISTS {} ( id INTEGER PRIMARY KEY, question_word TEXT NOT NULL, answer_word TEXT NOT NULL)", test_table_name), [], )?;
}
