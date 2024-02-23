use clearscreen;
use std::io;
use std::thread::sleep;
use std::time::Duration;

fn main() {
    println!("Hello and welcome to this small game. I hope you enjoy!");

    println!("Please enter your name:");

    let mut name = String::new();

    io::stdin()
        .read_line(&mut name)
        .expect("Failed to read your name");

    println!("Welcome {name}");

    sleep(Duration::from_secs(5));

    clearscreen::clear().expect("Failed to clear screen");
}
