#include "Menu.h"

using namespace std;

void main() {

	Menu menu;

	while (!menu.login())
		cout << "wrong username or password.\n";

	menu.adminMenu();

	cout << "This is the fucking best project";

}