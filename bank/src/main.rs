use bsod::bsod;
use dotenv::dotenv;
use eframe::{egui, epi};
use futures::future::Lazy;
use futures::stream::StreamExt;
use mongodb::bson::Document;
use mongodb::options::ServerApi;
use mongodb::options::ServerApiVersion;
use mongodb::{bson::doc, options::ClientOptions, Client};
use rand::Rng;
use serde::{Deserialize, Serialize};
use std::env;
use std::string;
use tokio;

#[derive(Clone, Serialize, Deserialize)]
struct Account {
    id: u32,
    name: String,
    holder: String,
    pin: String,
    balance: f32,
}

#[derive(Clone)]
struct MyApp {
    account_name: String,
    holder: String,
    pin: String,
    balance: f32,
    show_login: bool,
    show_create_account: bool,
    show_account_details: bool,
    show_deposit: bool,
    show_withdraw: bool,
    show_transfer: bool,
    amount: String,
    accounts: Vec<Account>,
    logged_in_account: Option<Account>,
    account_id: String,
}

async fn create_db() -> mongodb::error::Result<()> {
    let password = "dumle".to_string();
    let mut client_options = ClientOptions::parse(&format!("mongodb+srv://ERIKXVI:{}@bank.1d20drg.mongodb.net/?retryWrites=true&w=majority&appName=bank", password)).await?;

    let server_api = ServerApi::builder().version(ServerApiVersion::V1).build();
    client_options.server_api = Some(server_api);

    let client = Client::with_options(client_options)?;

    client
        .database("admin")
        .run_command(doc! {"ping": 1}, None)
        .await?;
    println!("Database created successfully");

    Ok(())
}

impl MyApp {
    async fn create_account(&mut self) {
        let account = Account {
            id: self.generate_account_id(),
            name: self.account_name.clone(),
            holder: self.holder.clone(),
            pin: self.pin.clone(),
            balance: self.balance,
        };
        self.accounts.push(account);
        self.save_accounts().await.unwrap();

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

    async fn load_accounts(&mut self) -> mongodb::error::Result<()> {
        let password = "dumle".to_string();
        let mut client_options = ClientOptions::parse(&format!("mongodb+srv://ERIKXVI:{}@bank.1d20drg.mongodb.net/?retryWrites=true&w=majority&appName=bank", password)).await?;
        let server_api = ServerApi::builder().version(ServerApiVersion::V1).build();
        client_options.server_api = Some(server_api);
        let client = Client::with_options(client_options)?;
        let db = client.database("bank");
        let collection = db.collection("accounts");

        let mut cursor = collection.find(None, None).await?;
        while let Some(result) = cursor.next().await {
            match result {
                Ok(document) => {
                    let account: Account = bson::from_document(document)?;
                    self.accounts.push(account);
                }
                Err(e) => return Err(e.into()),
            }
        }
        println!("Accounts loaded successfully");
        Ok(())
    }

    async fn save_accounts(&mut self) -> mongodb::error::Result<()> {
        let password = "dumle".to_string();
        let mut client_options = ClientOptions::parse(&format!("mongodb+srv://ERIKXVI:{}@bank.1d20drg.mongodb.net/?retryWrites=true&w=majority&appName=bank", password)).await?;
        let server_api = ServerApi::builder().version(ServerApiVersion::V1).build();
        client_options.server_api = Some(server_api);
        let client = Client::with_options(client_options)?;
        let db = client.database("bank");
        let collection = db.collection("accounts");

        for account in &self.accounts {
            let document = bson::to_document(account)?;
            collection.insert_one(document, None).await?;
        }
        println!("Accounts saved successfully");
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

    fn deposit(&mut self, amount: f32) {
        if let Some(account) = &mut self.logged_in_account {
            account.balance += amount;
        }
    }

    fn withdraw(&mut self, amount: f32) {
        if let Some(account) = &mut self.logged_in_account {
            if account.balance >= amount {
                account.balance -= amount;
            } else {
                println!("Failed to withdraw")
            }
        }
    }

    fn transfer(&mut self, to_account_id: String, amount: f32) {
        if let Some(account) = &mut self.logged_in_account {
            if account.balance >= amount {
                account.balance -= amount;
                if let Some(to_account) = self
                    .accounts
                    .iter_mut()
                    .find(|a| a.id.to_string() == to_account_id)
                {
                    to_account.balance += amount;
                } else {
                    println!("No account found")
                }
            } else {
                println!("your broke")
            }
        } else {
            println!("your not even logged in")
        }
    }
}

impl epi::App for MyApp {
    fn name(&self) -> &str {
        "Bank"
    }

    fn on_exit(&mut self) {
        //bsod();
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
                        self.show_deposit = true;
                    }
                    if ui.button("Withdraw").clicked() {
                        self.show_withdraw = true;
                    }
                    if ui.button("Transfer").clicked() {
                        self.show_transfer = true;
                    }
                    if ui.button("Logout").clicked() {
                        logout_clicked = true;
                    }
                });
                if logout_clicked {
                    bsod();
                }
                if self.show_deposit {
                    egui::Window::new("Deposit").show(ctx, |ui| {
                        ui.add(egui::widgets::TextEdit::singleline(&mut self.amount));
                        if ui.button("Submit").clicked() {
                            self.deposit(self.amount.parse().unwrap_or(0.0));
                            self.show_deposit = false;
                        }
                    });
                }

                if self.show_withdraw {
                    egui::Window::new("Withdraw").show(ctx, |ui| {
                        ui.add(egui::widgets::TextEdit::singleline(&mut self.amount));
                        if ui.button("Submit").clicked() {
                            self.withdraw(self.amount.parse().unwrap_or(0.0));
                            self.show_withdraw = false;
                        }
                    });
                }

                if self.show_transfer {
                    egui::Window::new("Transfer").show(ctx, |ui| {
                        ui.add(egui::widgets::TextEdit::singleline(&mut self.amount));
                        ui.add(egui::widgets::TextEdit::singleline(&mut self.account_id));
                        if ui.button("Submit").clicked() {
                            self.transfer(
                                self.account_id.clone(),
                                self.amount.parse().unwrap_or(0.0),
                            );
                            self.show_transfer = false;
                        }
                    });
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
                            println!("Failed to login")
                        }
                    }
                });
            }

            if self.show_create_account {
                egui::Window::new("Create Account").show(ctx, |ui| {
                    if ui.button("Close").clicked() {
                        self.show_create_account = false;
                    }
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
                        let mut this = self.clone();
                        tokio::task::spawn_blocking(move || {
                            let rt = tokio::runtime::Runtime::new().unwrap();
                            rt.block_on(this.create_account());
                        });
                    }
                });
            }
        }
    }
}

#[tokio::main]
async fn main() {
    for (key, value) in env::vars() {
        println!("{}: {}", key, value);
    }

    match create_db().await {
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
        show_deposit: false,
        show_withdraw: false,
        show_transfer: false,
        amount: String::from("0"),
        accounts: Vec::new(),
        logged_in_account: None,
        account_id: String::from("0"),
    };

    match app.load_accounts().await {
        Ok(_) => println!("Accounts loaded successfully."),
        Err(e) => println!("Failed to load accounts: {}", e),
    }

    let native_options = eframe::NativeOptions::default();
    eframe::run_native(Box::new(app), native_options);
}
