import requests
import random

looping = True

while looping:

    random_number = random.randint(1, 40000)

    url = f"https://skatteverket.entryscape.net/rowstore/dataset/b4de7df7-63c0-4e7e-bb59-1f156a591763/json?_offset={random_number}&_limit=1"

    req = requests.get(url)
    data = req.json()
    list_result = data['results']
    personnummer = list_result[0]['testpersonnummer']

    print (list_result[2: 12])

    input("\nvill du välja ett nytt personnummer? (j/n)\n")

if (input == "n"):
    looping = False
    print ("Tack för att du använde programmet!")