#include <iostream>
#include "fruit.h"
using namespace std;

int choice;

fruit::fruit()
{
	cout << "Pick a fruit";
	cout << "1. Apple";
	cout << "2. Banana";
	cout << "3. Pear";
	cout << "4. Orange";
	cout << "5. Grape";
	cout << "6. Watermelon";
	cout << "7. Pineapple";
	cin >> choice;

	if (choice = 1)
	{
		cout << "You picked an apple";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

	if (choice = 2)
	{
		cout << "You picked a banana";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

	if (choice = 3)
	{
		cout << "You picked a pear";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

	if (choice = 4)
	{
		cout << "You picked an orange";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

	if (choice = 5)
	{
		cout << "You picked a grape";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

	if (choice = 6)
	{
		cout << "You picked a watermelon";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

	if (choice = 7)
	{
		cout << "You picked a pineapple";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

	else
	{
		cout << "You picked an invalid fruit";
		cout << "wanna pick another fruit?";
		cin >> choice;
	}

}