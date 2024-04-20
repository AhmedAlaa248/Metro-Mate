#include "Menu.h"
#include "Station.h"

using namespace std;
int Station::nextId = 1;

void main() {

	Menu menu;

	int choice;
	do
	{
		cout << "Press:\n1. To login.\n2. To register.\n0. To exit.\n";
		cin >> choice;

		switch (choice)
		{
		case 0:
			break;
		case 1:
			while (!menu.login())
				cout << "wrong username or password.\n";
			break;
		case 2:
			menu.signUp();
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
	} while (choice);
	
	

	cout << "This is the fucking best project";

}