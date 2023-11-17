use rusqlite::{params, Connection, Result};

pub fn create_test(conn: &Connection, name: &str, max_attempts: i32) -> Result<i64> {
    conn.execute(
        "INSERT INTO tests (name, max_attempts) VALUES (?, ?)",
        params![name, max_attempts],
    )?;

    Ok(conn.last_insert_rowid())
}

pub fn add_question_to_test(
    conn: &Connection,
    test_id: i64,
    question_word: &str,
    answer_word: &str,
) -> Result<()> {
    conn.execute(
        "INSERT INTO questions (test_id, question_word, answer_word) VALUES (?, ?, ?)",
        params![test_id, question_word, answer_word],
    )?;

    Ok(())
}
