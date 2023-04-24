#include <iostream>

using namespace std;

int main()
{
	int cost, paid;
	cout << "Enter cost: ";
	cin >> cost;
	system("cls");
	cout << "Enter paid: ";
	cin >> paid;

	int change = paid - cost;

	int femhundra = change / 500;
	change = change % 500;

	int hundra = change / 100;
	change = change % 100;

	int femtio = change / 50;
	change = change % 50;

	int tjugo = change / 20;
	change = change % 20;

	int tio = change / 10;
	change = change % 10;

	int fem = change / 5;
	change = change % 5;

	int en = change / 1;
	
	system("cls");
	cout << "Your change is: " << femhundra << " Femhundralappar, " << hundra << " hundralappar, " << femtio << " femtiolappar, " << tjugo << " tjugolappar, " << tio << " tiokronor, " << fem << " femkronor, " << en << " enkronor." << endl;

	return 0;
}