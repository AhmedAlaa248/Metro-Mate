#include "Menu.h"

using namespace std;

void main() {

	Menu menu;

	int choice;
	cout << "Press:\n1. To login.\n2. To register.\n";
	cin >> choice;

	switch (choice)
	{
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
	

	cout << "This is the fucking best project";

}