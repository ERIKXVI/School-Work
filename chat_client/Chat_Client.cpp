#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
	cout << "Hello and welcome to sexy chat!" << endl;
	cout << "-----------------------------" << endl;
	cout << "Please enter your Username: ";
	string username;
	cin >> username;

	cout << "Welcome " << username << " to sexy chat!" << endl;
	cout << "--------------------------------------" << endl;
	cout << "Please press 1 to connect to the chat server: ";
	int database;
	cin >> database;

	switch (database)
	{
	case 1:

			break;
	default:
		cout << "Invalid Selection!" << endl;
		break;
	}

	return 0;
}