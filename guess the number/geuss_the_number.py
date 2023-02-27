import random
n = random.randint(1, 10)
guess = int(input("Gissa ett nummer mellan 1 och 10: "))
while guess != n:
    if guess < n:
        guess = int(input("Gissa igen: "))
    elif guess == n:
        guess = int(input("Gissa igen: "))
    else:
     break
print("Du gissade rätt!")