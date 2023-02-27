import random

n = random.randrange(1,10)
guess = int(input("Gissa ett nummer mellan 1 och 10: "))
guesses = 2

while guess != n:
    if guesses > 0 and guess < n:
        print(n)
        print("Gissa högre!")
        guesses = guesses - 1
        guess = int(input("Gissa igen: "))
    elif guesses > 0 and guess > n:
        print("Gissa lägre!")
        guesses = guesses - 1
        guess = int(input("Gissa igen: "))
    elif guesses <= 0:
        print("Du har inga gissningar kvar!")
        break
else: 
 print("Du gissade rätt!")