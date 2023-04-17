def menu():
    print("1. Balance")
    print("2. Withdraw")
    print("3. Deposit")
    print("4. Logout")

with open("atm_log.txt", "a") as f:
    f.write("Welcome to ATM\n")

    p = input("Enter your pin: ")
    f.write(f"Pin entered: {p}\n")

    if p == "1234":
        menu()
        c = int(input("Enter your choice: "))
        f.write(f"Choice entered: {c}\n")

        if c == 1:
            f.write("Balance requested\n")
            print("Your balance is 10000 Sek")
        elif c == 2:
            a = int(input("Enter amount to withdraw: "))
            f.write(f"Withdraw requested: {a}\n")
            if a <= 10000:
                f.write("Cash dispensed\n")
                print("Collect your cash below")
            else:
                f.write("Insufficient balance\n")
                print("Insufficient balance")
        elif c == 3:
            b = int(input("Enter amount of cash to deposit: "))
            f.write(f"Deposit requested: {b}\n")
            f.write(f"Your balance is {b+10000}\n")
            print("Your balance is", b+10000)
        elif c == 4:
            f.write("Logout requested\n")
            print("Thank you for using ATM")
        else:
            f.write("Invalid choice\n")
            print("Invalid choice")
    else:
        f.write("Invalid pin entered\n")
        print("Invalid pin entered")

    f.write("\n")

print("Transaction complete.")
