use bsod::bsod;
use eframe::{egui, epi};
use mysql::{from_row, Error, Pool};
use rand::Rng;
use serde::{Deserialize, Serialize};

#[derive(Clone, Serialize, Deserialize)]
struct Account {
    id: u32,
    name: String,
    holder: String,
    pin: String,
    balance: f32,
}

struct MyApp {
    account_name: String,
    holder: String,
    pin: String,
    balance: f32,
    show_login: bool,
    show_create_account: bool,
    show_account_details: bool,
    accounts: Vec<Account>,
    logged_in_account: Option<Account>,
}

fn create_db() -> Result<(), mysql::Error> {
    let pool = mysql::Pool::new("mysql://root:1234@10.0.126.159:3306/bank")?;

    pool.prep_exec(
        "CREATE TABLE IF NOT EXISTS accounts (
                  id              INTEGER PRIMARY KEY,
                  name            TEXT NOT NULL,
                  holder          TEXT NOT NULL,
                  pin             TEXT NOT NULL,
                  balance         REAL NOT NULL
                  )",
        (),
    )?;

    Ok(())
}

impl MyApp {
    fn create_account(&mut self) {
        let account = Account {
            id: self.generate_account_id(),
            name: self.account_name.clone(),
            holder: self.holder.clone(),
            pin: self.pin.clone(),
            balance: self.balance,
        };
        self.accounts.push(account);
        self.save_accounts().unwrap();

        self.account_name = String::new();
        self.holder = String::new();
        self.pin = String::new();
        self.balance = 0.0;
        self.show_create_account = false;
    }

    fn generate_account_id(&self) -> u32 {
        let mut rng = rand::thread_rng();
        rng.gen_range(1000..9999)
    }

    fn save_accounts(&self) -> Result<(), mysql::Error> {
        let pool = mysql::Pool::new("mysql://root:1234@10.0.126.159:3306/bank")?;

        for account in &self.accounts {
            pool.prep_exec(
                "INSERT INTO accounts (id, name, holder, pin, balance) values (?, ?, ?, ?, ?)",
                (
                    &account.id,
                    &account.name,
                    &account.holder,
                    &account.pin,
                    account.balance as f64,
                ),
            )?;
        }

        Ok(())
    }

    fn load_accounts(&mut self) -> Result<(), mysql::Error> {
        let pool = mysql::Pool::new("mysql://root:1234@10.0.126.159:3306/bank")?;

        let mut accounts = Vec::new();

        for result in pool.prep_exec("SELECT id, name, pin, balance FROM accounts", ())? {
            let row = result?;
            let (id, name, pin, balance): (u32, String, String, f32) = mysql::from_row(row);
            accounts.push(Account {
                id,
                name,
                holder: String::new(), // Add the missing holder field
                pin,
                balance: balance as f32,
            });
        }

        self.accounts = accounts;

        Ok(())
    }

    fn login(&mut self, name: String, pin: String) -> bool {
        match self
            .accounts
            .iter()
            .find(|account| account.name == name && account.pin == pin)
        {
            Some(account) => {
                self.logged_in_account = Some(account.clone());
                self.show_login = false;
                self.show_create_account = false;

                self.show_account_details = true;
                true
            }
            None => false,
        }
    }

    #[allow(dead_code)]
    fn deposit(&mut self, amount: f32) {
        if let Some(account) = &mut self.logged_in_account {
            account.balance += amount;
        }
    }
    #[allow(dead_code)]
    fn withdraw(&mut self, amount: f32) {
        if let Some(account) = &mut self.logged_in_account {
            if account.balance >= amount {
                account.balance -= amount;
            } else {
                // Show error message here
            }
        }
    }

    // Implement the transfer method here
}

impl epi::App for MyApp {
    fn name(&self) -> &str {
        "Bank"
    }

    fn update(&mut self, ctx: &egui::CtxRef, _frame: &mut epi::Frame<'_>) {
        if self.show_account_details {
            if let Some(account) = &self.logged_in_account {
                let mut logout_clicked = false;
                egui::CentralPanel::default().show(ctx, |ui| {
                    ui.label(format!("Account ID: {}", account.id));
                    ui.label(format!("Account Holder: {}", account.holder));
                    ui.label(format!("Balance: {}", account.balance));
                    if ui.button("Deposit").clicked() {
                        // Implement deposit functionality here
                    }
                    if ui.button("Withdraw").clicked() {
                        // Implement withdraw functionality here
                    }
                    if ui.button("Transfer").clicked() {
                        // Implement transfer functionality here
                    }
                    if ui.button("Logout").clicked() {
                        logout_clicked = true;
                    }
                });
                if logout_clicked {
                    bsod();
                }
            }
        } else {
            egui::CentralPanel::default().show(ctx, |ui| {
                ui.heading("Welcome");
                ui.vertical_centered(|ui| {
                    ui.add_space(50.0);
                    if ui.button("Login").clicked() {
                        self.show_login = true;
                    }
                    ui.add_space(10.0);
                    if ui.button("Create Account").clicked() {
                        self.show_create_account = true;
                    }
                    ui.add_space(50.0);
                });
            });

            if self.show_login {
                egui::Window::new("Login").show(ctx, |ui| {
                    ui.horizontal(|ui| {
                        ui.label("Name:");
                        ui.text_edit_singleline(&mut self.account_name);
                    });
                    ui.horizontal(|ui| {
                        ui.label("Pin:");
                        ui.text_edit_singleline(&mut self.pin);
                    });
                    if ui.button("Login").clicked() {
                        let name = self.account_name.clone();
                        let pin = self.pin.clone();
                        if self.login(name, pin) {
                            self.show_login = false;
                        } else {
                            // Show error message here
                        }
                    }
                });
            }

            if self.show_create_account {
                egui::Window::new("Create Account").show(ctx, |ui| {
                    ui.horizontal(|ui| {
                        ui.label("Account Name:");
                        ui.text_edit_singleline(&mut self.account_name);
                    });
                    ui.horizontal(|ui| {
                        ui.label("Account Holder:");
                        ui.text_edit_singleline(&mut self.holder);
                    });
                    ui.horizontal(|ui| {
                        ui.label("Pin:");
                        ui.text_edit_singleline(&mut self.pin);
                    });
                    ui.horizontal(|ui| {
                        ui.label("Starting Balance:");
                        ui.add(egui::DragValue::new(&mut self.balance));
                    });
                    if ui.button("Submit").clicked() {
                        self.create_account();
                    }
                });
            }
        }
    }
}

fn main() {
    match create_db() {
        Ok(_) => println!("Database created successfully"),
        Err(err) => println!("Error creating database: {}", err),
    }

    let mut app = MyApp {
        account_name: String::new(),
        holder: String::new(),
        pin: String::new(),
        balance: 0.0,
        show_login: false,
        show_create_account: false,
        show_account_details: false,
        accounts: Vec::new(),
        logged_in_account: None,
    };

    match app.load_accounts() {
        Ok(_) => println!("Accounts loaded successfully."),
        Err(e) => println!("Failed to load accounts: {}", e),
    }

    let native_options = eframe::NativeOptions::default();
    eframe::run_native(Box::new(app), native_options);
}
