import os
import pickle
import uuid

class Student:
    def __init__(self, id, name, age, program, phone):
        self.id = id
        self.name = name
        self.age = age
        self.program = program
        self.phone = phone

class StudentManagement:
    def __init__(self):
        self.filename = "students.dat"
        self.data = []
        self.read_from_file()

    #menu
    def menu(self):
        print("1. Add new student")
        print("2. Show all students")
        print("3. Sort by name")
        print("4. Delete a student")
        print("5. Exit")
        choice = int(input("Enter your choice: "))
        if choice == 1:
            self.add_new_student()
        elif choice == 2:
            self.show_all_students()
        elif choice == 3:
            self.sort_by_name()
        elif choice == 4:
            self.delete_student()
        elif choice == 5:
            self.write_to_file()
            exit()
        else:
            print("Invalid choice")

    #add new student
    def add_new_student(self):
        name = input("Enter name: ")
        age = int(input("Enter age: "))
        program = input("Enter program: ")
        phone = int(input("Enter Phone: "))
        id = str(uuid.uuid4())[:8]
        student = Student(id, name, age, program, phone)
        self.data.append(student)

    #show all students
    def show_all_students(self):
        for student in self.data:
            print(f"ID: {student.id}, Name: {student.name}, Age: {student.age}, Program: {student.program}, Phone: {student.phone}")

    #sort by name
    def sort_by_name(self):
        self.data.sort(key=lambda x: x.name)

    #delete a student
    def delete_student(self):
        id = input("Enter the ID of the student you want to delete: ")
        for student in self.data:
            if student.id == id:
                self.data.remove(student)
                print(f"Student with ID {id} has been deleted.")
                break
        else:
            print(f"Student with ID {id} not found.")

    #write to file
    def write_to_file(self):
        with open(self.filename, 'wb') as file:
            pickle.dump(self.data, file)

    #read from file
    def read_from_file(self):
        if not os.path.exists(self.filename):
            with open(self.filename, 'wb') as file:
                pickle.dump([], file)

        with open(self.filename, 'rb') as file:
            self.data = pickle.load(file)

if __name__ == "__main__":
    student_management = StudentManagement()
    while True:
        student_management.menu()
