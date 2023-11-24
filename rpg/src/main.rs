use std::convert::TryInto;
use std::io;
use std::process::Command;

fn clear_screen() {
    if cfg!(target_os = "windows") {
        Command::new("cmd").args(&["/C", "cls"]).status().unwrap();
    } else {
        // Unix-like OS
        print!("\x1B[2J\x1B[1;1H");
    }
}
struct Track {
    waypoints: Vec<(usize, usize)>,
}

impl Track {
    fn new(waypoints: Vec<(usize, usize)>) -> Track {
        Track { waypoints }
    }
}

struct Balloon {
    track_position: usize,
    speed: i32,
    health: i32,
    active: bool,
}

impl Balloon {
    fn new(speed: i32, health: i32) -> Balloon {
        Balloon {
            track_position: 0,
            speed,
            health,
            active: true,
        }
    }

    fn move_forward(&mut self, track: &Track) {
        if self.active && self.track_position < track.waypoints.len() - 1 {
            self.track_position += self.speed as usize;
        }

        if self.track_position >= track.waypoints.len() - 1 {
            self.active = false;
        }
    }
}

fn draw_track(board: &mut Vec<Vec<char>>, track: &Track) {
    for (x, y) in &track.waypoints {
        board[*y as usize][*x as usize] = '+';
    }
}

fn draw_balloon(board: &mut Vec<Vec<char>>, balloon: &Balloon, track: &Track) {
    if balloon.active && balloon.track_position < track.waypoints.len() {
        let (x, y) = track.waypoints[balloon.track_position];
        board[y as usize][x as usize] = 'o';
    }
}

fn render_board(board: &Vec<Vec<char>>) {
    for row in board {
        for &cell in row {
            print!("{}", cell);
        }
        println!();
    }
}

fn play_game() {
    'outer: loop {
        let width = 80; // Width of the CMD window
        let height = 25; // Height of the CMD window

        // Create a track from top left to bottom right
        let mut waypoints = Vec::new();
        let mut x = 0;
        let mut y = 0;

        // Example path logic - diagonal path
        while x < width - 1 || y < height - 1 {
            waypoints.push((x as usize, y as usize));
            if x < width - 1 {
                x += 1;
            }
            if y < height - 1 {
                y += 1;
            }

            // Inside the loop
            let x_usize: usize = x.try_into().unwrap();
            let y_usize: usize = y.try_into().unwrap();
            waypoints.push((x_usize, y_usize));
        }
        waypoints.push((width - 1, height - 1));

        let track = Track::new(waypoints);
        let mut balloon = Balloon::new(5, 100);

        let mut board = vec![vec!['.'; width]; height];

        while balloon.active {
            // Clear the screen
            clear_screen();

            board.iter_mut().for_each(|row| row.fill('.'));

            balloon.move_forward(&track);

            draw_track(&mut board, &track);
            draw_balloon(&mut board, &balloon, &track);
            render_board(&board);

            // Sleep or wait for some time before next iteration
            std::thread::sleep(std::time::Duration::from_millis(500));
        }

        println!("The balloon reached the end of the track.");
        if !prompt_play_again() {
            break 'outer;
        }
    }
}

fn prompt_play_again() -> bool {
    println!("Do you want to play again? (y/n): ");
    let mut choice = String::new();
    io::stdin()
        .read_line(&mut choice)
        .expect("Failed to read line");

    matches!(choice.trim(), "y" | "Y")
}

fn main() {
    if main_menu() {
        play_game();
    } else {
        println!("Exiting game.");
    }
}

fn main_menu() -> bool {
    loop {
        println!("Main Menu");
        println!("1. Play");
        println!("2. Quit");
        println!("Enter your choice (1 or 2):");

        let mut choice = String::new();
        io::stdin()
            .read_line(&mut choice)
            .expect("Failed to read line");

        match choice.trim() {
            "1" => return true,
            "2" => return false,
            _ => println!("Invalid choice, please enter 1 or 2"),
        }
    }
}
