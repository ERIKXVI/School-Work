use crossterm::cursor;
use crossterm::{
    event::{poll, read, Event, KeyCode},
    terminal::{self, ClearType},
    ExecutableCommand, Result,
};
use std::{thread, time::Duration};

const WIDTH: u32 = 10;
const HEIGHT: u32 = 10;
const PLAYER: char = '^';
const BULLET: char = '|';
const ALIEN: char = 'v';
const BOSS: char = 'B';
const SHOT_COOLDOWN: u32 = 5;
const BOSS_HP: u32 = 10;

struct Game {
    player_x: u32,
    bullets: Vec<(u32, u32)>,
    aliens: Vec<(u32, u32)>,
    boss: Option<(u32, u32, u32)>, // (x, y, hp)
    alien_direction: i32,
    bullet_speed: u32,
    multi_shot: bool,
    points: u32,
    game_over: bool,
    shot_cooldown: u32,
    level: u32,
}

impl Game {
    fn new() -> Game {
        let initial_level = 1;
        Game {
            player_x: WIDTH / 2,
            bullets: Vec::new(),
            aliens: (0..initial_level)
                .map(|_| ((rand::random::<u32>() % WIDTH) as u32, 0))
                .collect(),
            boss: None,
            alien_direction: 1,
            bullet_speed: 5,
            multi_shot: false,
            points: 1000,
            game_over: false,
            shot_cooldown: SHOT_COOLDOWN,
            level: initial_level,
        }
    }

    fn fire_bullet(&mut self) {
        if self.shot_cooldown == 0 {
            if self.multi_shot {
                // Fire three bullets in a spread
                self.bullets.push((self.player_x - 1, HEIGHT - 2));
                self.bullets.push((self.player_x, HEIGHT - 2));
                self.bullets.push((self.player_x + 1, HEIGHT - 2));
            } else {
                // Fire a single bullet
                self.bullets.push((self.player_x, HEIGHT - 2));
            }
            self.shot_cooldown = SHOT_COOLDOWN;
        }
    }

    fn draw(&self) -> Result<()> {
        let mut buffer = vec![vec![' '; (WIDTH + 2) as usize]; (HEIGHT + 2) as usize];

        // Draw the border
        for y in 0..(HEIGHT + 2) {
            for x in 0..(WIDTH + 2) {
                if y == 0 || y == HEIGHT + 1 || x == 0 || x == WIDTH + 1 {
                    buffer[y as usize][x as usize] =
                        if y == 0 || y == HEIGHT + 1 { '-' } else { '|' };
                }
            }
        }

        // Draw the game objects
        for y in 1..(HEIGHT + 1) {
            for x in 1..(WIDTH + 1) {
                let c = if x - 1 == self.player_x && y - 1 == HEIGHT - 1 {
                    PLAYER
                } else if self.bullets.contains(&(x - 1, y - 1)) {
                    BULLET
                } else if self.aliens.contains(&(x - 1, y - 1)) {
                    ALIEN
                } else if let Some((boss_x, boss_y, _)) = self.boss {
                    if x - 1 == boss_x && y - 1 == boss_y {
                        BOSS
                    } else {
                        ' '
                    }
                } else {
                    ' '
                };

                buffer[y as usize][x as usize] = c;
            }
        }

        // Draw the boss HP
        if let Some((_, _, hp)) = self.boss {
            for i in 0..hp {
                buffer[i as usize + 1][(WIDTH + 3) as usize] = '#';
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

    fn spawn_boss(&mut self) {
        self.boss = Some(((WIDTH / 2) as u32, 0, BOSS_HP));
    }

    fn update(&mut self) {
        if self.shot_cooldown > 0 {
            self.shot_cooldown -= 1;
        }

        let mut boss_defeated = false;
        if let Some(boss) = &mut self.boss {
            for bullet in &mut self.bullets {
                let (x, y) = *bullet;
                if x == boss.0 && y == boss.1 {
                    boss.2 -= 1;
                    if boss.2 == 0 {
                        self.points += BOSS_HP;
                        boss_defeated = true;
                    }
                    *bullet = (x, y);
                } else if y > 0 {
                    *bullet = (x, y - 1);
                }
            }
        }

        if boss_defeated {
            self.boss = None;
            self.level += 1;
            self.spawn_boss();
        }

        for bullet in &mut self.bullets {
            let (x, y) = *bullet;
            for alien in &mut self.aliens {
                if x == alien.0 && y == alien.1 {
                    alien.0 = (rand::random::<u32>() % WIDTH) as u32;
                    alien.1 = 0;
                    self.points += 1;
                }
            }
            if y > 0 {
                *bullet = (x, y - 1);
            }
        }
        self.bullets.retain(|&bullet| bullet.1 != 0);

        for alien in &mut self.aliens {
            alien.0 = (alien.0 as i32 + self.alien_direction) as u32;
            if alien.0 == 0 || alien.0 == WIDTH - 1 {
                self.alien_direction *= -1;
                alien.1 += 1;
            }

            // Add the game over condition here
            if alien.1 == HEIGHT - 1 {
                self.game_over = true;
            }
        }
    }

    fn input(&mut self) -> Result<()> {
        if poll(Duration::from_millis(100))? {
            if let Event::Key(event) = read()? {
                match event.code {
                    KeyCode::Char('a') => self.player_x -= 1,
                    KeyCode::Char('d') => self.player_x += 1,
                    KeyCode::Char(' ') => {
                        self.fire_bullet();
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
        println!("2. Upgrade to multi-shot (20 points)");
        println!("3. Start game");

        let mut input = String::new();
        std::io::stdin().read_line(&mut input)?;

        match input.trim() {
            "1" => {
                if self.points >= 10 {
                    self.points -= 10;
                    self.bullet_speed += 1;
                    println!("Bullet speed upgraded!");
                } else {
                    println!("Not enough points!");
                }
            }
            "2" => {
                if self.points >= 20 {
                    self.points -= 20;
                    self.multi_shot = true;
                    println!("Upgraded to multi-shot!");
                } else {
                    println!("Not enough points!");
                }
            }
            "3" => {
                self.run()?;
            }
            _ => {
                println!("Invalid option!");
            }
        }

        Ok(())
    }
}

fn main() -> Result<()> {
    let mut game = Game::new();
    game.main_menu()
}
