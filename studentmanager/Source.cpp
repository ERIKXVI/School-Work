#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <filesystem> // for checking file existence
#include <cstdlib> // for system()

using namespace std;
namespace fs = std::filesystem;

struct Student
{
    string name;
    int age;
    string course;
    int number;
    int id;
};

void addstudent(vector<Student>& students, mt19937& rng, ofstream& outfile)
{
    Student student;
    cout << "Enter name: ";
    cin >> student.name;
    cout << "Enter age: ";
    cin >> student.age;
    cout << "Enter course: ";
    cin >> student.course;
    cout << "Enter phonenumber: ";
    cin >> student.number;
    uniform_int_distribution<int> dist(1000, 9999);
    student.id = dist(rng);
    cout << "ID: " << student.id << endl;
    students.push_back(student);

    outfile << student.name << endl;
    outfile << student.age << endl;
    outfile << student.course << endl;
    outfile << student.number << endl;
    outfile << student.id << endl;
}

void displaystudent(const vector<Student>& students)
{
    for (const auto& student : students)
    {
        cout << "Name: " << student.name << endl;
        cout << "Age: " << student.age << endl;
        cout << "Course: " << student.course << endl;
        cout << "Phonenumber: " << student.number << endl;
        cout << "ID: " << student.id << endl;
        cout << endl;
    }
}

void deletestudent(vector<Student>& students)
{
    int id;
    cout << "Enter ID: ";
    cin >> id;
    for (auto it = students.begin(); it != students.end(); ++it)
    {
        if (it->id == id)
        {
            students.erase(it);
            cout << "Successfully deleted student with ID " << id << endl;
            return;
        }
    }
    cout << "Could not find student with ID " << id << endl;
}

int main()
{
    vector<Student> students;
    mt19937 rng(random_device{}());
    string filename = "students.txt";
    ofstream outfile;

    if (fs::exists(filename))
    {
        outfile.open(filename, ios::app);
    }
    else
    {
		outfile.open(filename);
	}

    while (true)
    {
        std::system("cls");
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            addstudent(students, rng, outfile);
            cout << "Student added" << endl;
            break;

        case 2:
            displaystudent(students);
            break;

        case 3:
            deletestudent(students);
            break;

        case 4:
            cout << "Exiting..." << endl;
            outfile.close();
            return 0;

        default:
            cout << "Invalid choice" << endl;
            break;
        }
        std::system("pause");
    }
    return 0;
}
