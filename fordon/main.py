import trailer
import car

looping = True

#-------------------#
#cars
bwm_silver = car.bil("BWM", "Silver", 100)
volvo_black = car.bil("Volvo", "Black", 200)

#trailers
scanina_red = trailer.trailer("Scanina", "Red", 10000)
man_gray = trailer.trailer("Man", "Gray", 20000)

#lists
car_list = [bwm_silver, volvo_black]
trailer_list = [scanina_red, man_gray]
#-------------------#

def print_vehicle_list(vehicle_list):
    for vehicle in vehicle_list:
        vehicle.print_fordon()

#-------------------#
#loop
while looping:
    print("-------------------")
    print("What do you want to do? (1) Print all vehicles, (2) Print all cars, (3) Print all trailers, (4) Exit")
    choice = input("Choice: ")
    if choice == "1":
        print("All trailers and cars:")
        print_vehicle_list(trailer_list)
        print_vehicle_list(car_list)

    elif choice == "2":
        print("All cars:")
        print_vehicle_list(car_list)

    elif choice == "3":
        print("All trailers:")
        print_vehicle_list(trailer_list)

    elif choice == "4":
        looping = False

    else:
        print("Invalid choice")
#-------------------#

   