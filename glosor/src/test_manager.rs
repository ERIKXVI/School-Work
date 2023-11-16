use sqlx::MySqlPool;

pub async fn create_test(
    pool: &MySqlPool,
    name: &str,
    max_attempts: i32,
) -> Result<i64, sqlx::Error> {
    let record = sqlx::query!(
        "INSERT INTO tests (name, max_attempts) VALUES (?, ?)",
        name,
        max_attempts
    )
    .execute(pool)
    .await?
    .last_insert_id();

    Ok(record)
}

pub async fn add_question_to_test(
    pool: &MySqlPool,
    test_id: i64,
    question_word: &str,
    answer_word: &str,
) -> Result<(), sqlx::Error> {
    sqlx::query!(
        "INSERT INTO questions (test_id, question_word, answer_word) VALUES (?, ?, ?)",
        test_id,
        question_word,
        answer_word
    )
    .execute(pool)
    .await?;
    Ok(())
}
