#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sqlite3.h>

using namespace std;

void showLoadingScreen()
{
	cout << "Loading..." << endl;
	cout << "[";
	for (int i = 0; i <= 10; i++)
	{
		cout << "=";
		cout.flush();
		this_thread::sleep_for(chrono::seconds(1));
	}
	cout << "]" << endl;
}

int main()
{
	cout << "Hello and welcome to sexy chat!" << endl;
	cout << "-----------------------------" << endl;
	cout << "Please enter your Username: ";
	string username;
	cin >> username;

	showLoadingScreen();

	cout << "Welcome " << username << " to sexy chat!" << endl;
	cout << "--------------------------------------" << endl;

	return 0;
}