#include "Menu.h"

Menu::Menu(){
}

bool Menu::login() {
	cout << "Enter your userName:\n";
	cin >> userName;
	cout << "Enter your password:\n";
	cin >> password;

	if (userName == "admin" && password == "admin")
	{
		while (adminMenu());
		return 1;
	}
	else
		return 0;
}

int Menu::adminMenu()
{
	int choice;
	cout << "Hello boss!\n";
	cout << "1. Manage users\n2. Manage stations\n3. Manage subscriptions\n4. Manage rides\n5. Mange fare\n0. Exit\n";
	cout << "Choose your choice:\n";
	cin >> choice;

	switch (choice)
	{
	case 0:
		break;
	case 1:
		cout << "1. Edit user\n2. Delete user\n3. View user details\n4. View all users\n";
		cout << "Choose your choice:\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			//TODO call edit user FN.
			cout << "Edit user";
			break;
		case 2:
			//TODO call delete user FN.
			cout << "Delete user";
			break;
		case 3:
			//TODO call view user details FN.
			cout << "View user";
			break;
		case 4:
			//TODO call view all users FN.
			cout << "All users";
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "\n";
		break;
	case 2:
		cout << "1. Add station\n2. Edit station\n3. Delete station\n4. View station details\n5. View all stations\n";
		cout << "Choose your choice:\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			//TODO call add station FN.
			cout << "Add Station";
			break;
		case 2:
			//TODO call edit station FN.
			cout << "Edit station";
			break;
		case 3:
			//TODO call delete station FN.
			cout << "Delete station";
			break;
		case 4:
			//TODO call view station details FN.
			cout << "View station";
			break;
		case 5:
			//TODO call view all station FN.
			cout << "All stations";
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "\n";
		break;
	case 3:
		cout << "1. Add subscription\n2. Edit subscription\n3. Delete subscription\n4. View subscription details\n5. View all subscriptions\n";
		cout << "Choose your choice:\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			//TODO call add subscription FN.
			cout << "Add subscription";
			break;
		case 2:
			//TODO call edit subscription FN.
			cout << "Edit subscription";
			break;
		case 3:
			//TODO call delete subscription FN.
			cout << "Delete subscription";
			break;
		case 4:
			//TODO call view subscription details FN.
			cout << "View subscription";
			break;
		case 5:
			//TODO call view all subscriptions FN.
			cout << "All subscriptions";
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "\n";
		break;
	case 4:
		cout << "1. View specific users rieds.\n2. View specific day rides.\n3. View specific station rides.\n4. View all rides.\n";
		cout << "Choose your choice:\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			//TODO call viewRidesByUser FN.
			cout << "user rides\n";
			break;
		case 2:
			//TODO call viewRidesByDay FN.
			cout << "day rides\n";
			break;
		case 3:
			//TODO call viewRidesByStation FN.
			cout << "station rides\n";
			break;
		case 4:
			//TODO call viewAllRides FN.
			cout << "all user rides\n";
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
		break;
	case 5:
		//TODO put the fare options
		break;
	default:
		cout << "Invalid choice\n";
		break;
	}
	return choice;
}

int Menu::userMenu()
{
	return 0;
}
