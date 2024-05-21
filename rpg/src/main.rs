use crossterm::cursor;
use crossterm::{
    event::{poll, read, Event, KeyCode},
    terminal::{self, ClearType},
    ExecutableCommand, Result,
};
use std::{thread, time::Duration};

const WIDTH: u16 = 20;
const HEIGHT: u16 = 20;
const PLAYER: char = '^';
const ALIEN: char = 'A';
const BULLET: char = '|';

struct Game {
    player_x: u16,
    bullet_x: Option<u16>,
    bullet_y: Option<u16>,
    alien_x: u16,
    alien_y: u16,
    alien_direction: i16,
    bullet_speed: u16,
    points: u16,
    game_over: bool,
}

impl Game {
    fn new() -> Game {
        Game {
            player_x: WIDTH / 2,
            bullet_x: None,
            bullet_y: None,
            alien_x: 0,
            alien_y: 0,
            alien_direction: 1,
            bullet_speed: 1,
            points: 0,
            game_over: false,
        }
    }

    fn draw(&self) -> Result<()> {
        let mut buffer = vec![vec![' '; WIDTH as usize]; HEIGHT as usize];

        for y in 0..HEIGHT {
            for x in 0..WIDTH {
                let c = if x == self.player_x && y == HEIGHT - 1 {
                    PLAYER
                } else if Some(x) == self.bullet_x && Some(y) == self.bullet_y {
                    BULLET
                } else if x == self.alien_x && y == self.alien_y {
                    ALIEN
                } else {
                    ' '
                };

                buffer[y as usize][x as usize] = c;
            }
        }

        let output: String = buffer
            .into_iter()
            .map(|row| row.into_iter().collect::<String>())
            .collect::<Vec<_>>()
            .join("\n");

        std::io::stdout().execute(cursor::MoveTo(0, 0))?;
        println!("{}\n\nPoints: {}", output, self.points);

        Ok(())
    }

    fn update(&mut self) {
        if self.bullet_x == Some(self.alien_x) && self.bullet_y == Some(self.alien_y) {
            self.bullet_x = None;
            self.bullet_y = None;
            self.alien_x = (rand::random::<u16>() % WIDTH) as u16;
            self.alien_y = 0;
            self.points += 1;
        }

        if let Some(y) = self.bullet_y {
            if y > 0 {
                self.bullet_y = Some(y - 1);
            } else {
                self.bullet_x = None;
                self.bullet_y = None;
            }
        }
        self.alien_x = (self.alien_x as i16 + self.alien_direction) as u16;
        if self.alien_x == 0 || self.alien_x == WIDTH - 1 {
            self.alien_direction *= -1;
            self.alien_y += 1;
        }

        // Add the game over condition here
        if self.alien_y == HEIGHT - 1 {
            self.game_over = true;
        }
    }

    fn input(&mut self) -> Result<()> {
        if poll(Duration::from_millis(100))? {
            if let Event::Key(event) = read()? {
                match event.code {
                    KeyCode::Char('a') => self.player_x -= 1,
                    KeyCode::Char('d') => self.player_x += 1,
                    KeyCode::Char(' ') => {
                        if self.bullet_y.is_none() {
                            self.bullet_x = Some(self.player_x);
                            self.bullet_y = Some(HEIGHT - 2);
                        }
                    }
                    _ => {}
                }
            }
        }
        Ok(())
    }

    fn run(&mut self) -> Result<()> {
        std::io::stdout().execute(terminal::Clear(ClearType::All))?;
        loop {
            self.draw()?;
            self.update();
            self.input()?;
            thread::sleep(Duration::from_millis(100));
        }
    }

    fn main_menu(&mut self) -> Result<()> {
        println!("Points: {}", self.points);
        println!("1. Upgrade bullet speed (10 points)");
        println!("2. Start game");

        let mut input = String::new();
        std::io::stdin().read_line(&mut input)?;

        match input.trim() {
            "1" => {
                if self.points >= 10 {
                    self.points -= 10;
                    self.bullet_speed += 1;
                }
            }
            "2" => {
                self.run()?;
            }
            _ => {}
        }

        Ok(())
    }
}

fn main() -> Result<()> {
    let mut game = Game::new();
    game.main_menu()
}
