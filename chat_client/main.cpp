#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{

    cout << "Welcome to Sex Chat" << endl;

    cout << "We are currently loading the chat" << endl;

    cout << "Please wait..." << endl;

    this_thread::sleep_for(chrono::seconds(10));
    system("cls");

    cout << "Hi, I'm a bot" << endl;

    cout << "Press Enter to close";
    cin.ignore();

    return 0;
}