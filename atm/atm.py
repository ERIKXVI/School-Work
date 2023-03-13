print("Welcome to ATM")

p=input("Enter your pin: ")
if p=="1234":
    print("1. Balance")
    print("2. Withdraw")
    print("3. Deposit")
    print("4. Logout")
    c=int(input("Enter your choice: "))
    if c ==1:
        print("Your balance is 10000 Sek")
    elif c==2:
        a=int(input("enter amount to withdraw:"))
        if a<=10000:
            print("collect your cash below")
        else:
            print("insufficient balance")
    elif c==3:
        b=int(input("enter amount of cash to deposit:"))
        print("your balance is",b+10000)
    elif c==4:
            print("Thank you for using ATM")
    else:
            print("Invalid choice")