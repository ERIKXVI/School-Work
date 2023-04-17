import pickle

class Account:
    def __init__(self, name, balance):
        self.name = name
        self.balance = balance

class Bank:
    def __init__(self):
        self.accounts = {}
        self.current_account_id = None

    def load_accounts(self):
        try:
            with open("accounts.pkl", "rb") as f:
                self.accounts = pickle.load(f)
        except FileNotFoundError:
            pass

    def save_accounts(self):
        with open("accounts.pkl", "wb") as f:
            pickle.dump(self.accounts, f)

    def create_account(self, name, balance):
        account_id = len(self.accounts) + 1
        self.accounts[account_id] = Account(name, balance)
        self.save_accounts()
        print(f"Account created with ID {account_id}")

    def delete_account(self, account_id):
        if account_id in self.accounts:
            del self.accounts[account_id]
            self.save_accounts()
            print(f"Account {account_id} deleted")
        else:
            print(f"Account {account_id} not found")

    def select_account(self, account_id):
        if account_id in self.accounts:
            self.current_account_id = account_id
            print(f"Account {account_id} selected")
        else:
            print(f"Account {account_id} not found")

    def deposit(self, account_id, amount):
        if account_id in self.accounts:
            account = self.accounts[account_id]
            account.balance += amount
            self.save_accounts()
            print(f"Deposit of {amount} to account {account_id} successful. New balance: {account.balance}")
        else:
            print(f"Account {account_id} not found")

    def withdraw(self, amount):
        account = self.accounts[self.current_account_id]
        if account.balance >= amount:
            account.balance -= amount
            self.save_accounts()
            print(f"Withdrawal of {amount} successful. New balance: {account.balance}")
        else:
            print(f"Insufficient balance. Current balance: {account.balance}")

    def get_balance(self, account_id):
        if account_id in self.accounts:
            account = self.accounts[account_id]
            print(f"Balance for account {account_id}: {account.balance}")
        else:
            print(f"Account {account_id} not found")

# Load the accounts from file
bank = Bank()
bank.load_accounts()

while True:
    print("1. Create account")
    print("2. Delete account")
    print("3. Select account")
    print("4. Deposit")
    print("5. Withdraw")
    print("6. Check balance")
    print("7. Exit")
    choice = input("Enter your choice: ")

    if choice == "1":
        name = input("Enter account name: ")
        balance = float(input("Enter initial balance: "))
        bank.create_account(name, balance)
    elif choice == "2":
        account_id = int(input("Enter account ID to delete: "))
        bank.delete_account(account_id)
    elif choice == "3":
        account_id = int(input("Enter account ID to select: "))
        bank.select_account(account_id)
    elif choice == "4":
        account_id = int(input("Enter account ID to deposit into: "))
        amount = float(input("Enter amount to deposit: "))
        bank.deposit(account_id, amount)
    elif choice == "5":
        amount = float(input("Enter amount to withdraw: "))
        bank.withdraw(amount)
    elif choice == "6":
        account_id = int(input("Enter account ID to check balance: "))
        bank.get_balance(account_id)

    elif choice == "7":
            break
    else:
        print("Invalid choice")

    print("Exiting program")

    bank.save_accounts()
