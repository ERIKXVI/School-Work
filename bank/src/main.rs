use eframe::{egui, epi};
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

        // Reset the form and return to the main page
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

    fn save_accounts(&self) -> std::result::Result<(), std::io::Error> {
        let encoded = bincode::serialize(&self.accounts)
            .map_err(|e| std::io::Error::new(std::io::ErrorKind::Other, e))?;
        std::fs::write("accounts.txt", encoded)?;
        Ok(())
    }

    fn load_accounts(&mut self) -> std::result::Result<(), std::io::Error> {
        if std::path::Path::new("accounts.txt").exists() {
            let data = std::fs::read("accounts.txt")?;
            self.accounts = bincode::deserialize(&data)
                .map_err(|e| std::io::Error::new(std::io::ErrorKind::Other, e))?;
        }
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
                self.show_login = false; // Hide login page
                self.show_create_account = false; // Hide create account page if it's there
                                                  // Hide any other pages here...
                self.show_account_details = true; // Show account details page
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
        "My App"
    }

    fn update(&mut self, ctx: &egui::CtxRef, _frame: &mut epi::Frame<'_>) {
        if self.show_account_details {
            if let Some(account) = &self.logged_in_account {
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
                });
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
