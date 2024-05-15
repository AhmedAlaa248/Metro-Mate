#include <iostream>
#include "Validator.h"
#include "Admin.h"
using namespace std;
int tmp = 0;
string username;
bool infoupdate = false;
User user;
Station station;
SubscriptionPlan subplan;
Ride ride;
Admin admin;
Subscription sub;
vector<Subscription> subscriptions = sub.RetrieveSubscriptionFromDatabase();
vector<User> users = user.RetrieveUsersFromDatabase();
vector<Station> stations = station.RetrieveStationsFromDatabase();
vector<SubscriptionPlan> subplans = subplan.RetrieveSubplansFromDatabase();
vector<Ride> rides = ride.RetrieveRidesFromDatabase();


void saveAlltoDataBase(vector <Subscription>& subs, vector <User>& users, vector <Ride>& rides, vector <SubscriptionPlan>& plans, vector <Station>& stations)
{
	sub.saveSubscriptionsToDatabase(subs);
	user.saveUsersToDatabase(users);
	ride.saveRideToDatabase(rides);
	subplan.saveSubplanToDatabase(subplans);
	station.saveStationToDatabase(stations);
}



void userfunctions(vector <Subscription>& subs, User& user, vector <User>& users, vector <Ride>& ridee, vector <SubscriptionPlan>& plans, vector <Station>& stations) {
	Validator va;
	int srcid, dstid; string src, dst;
	Station st;
	int choice;
	cout << "Hello " + user.name + "\n";
	cout << "1. Purchase subscription.\n2. Manage subscription.\n3. Check in.\n4. View ride history.\n5. Update info.\n0. Log out\n";
	cout << "Choose your choice:\n";

	cin >> choice;
	switch (choice)
	{
	case 0:

		break;
	case 1:
		cout << "Purchase Sub\n";
		user.purchaseSub(subs, user, stations);


		cout << endl;
		cout << "Reffered to Main menu ! \n";
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
	case 2:
		int choicee;
		while (true) {
			cout << "Manage Subscription.\n";
			cout << "1- View Current Subscribtion \n";
			cout << "2- Change Subscribtion \n";
			cout << "3- Renew Subscription \n";
			cout << "4- Main Menu \n";
			cout << "Enter your choice: ";

			cin >> choicee;
			if (choicee >= 1 && choicee <= 4) {

				break;
			}
			else {
				cout << "Invalid choice. Please enter a number between 1 and 3.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		switch (choicee) {
		case 1:
			Subscription::printsubdetails(user.subscription);
			break;
		case 2:
			user.changeSub(subs, user, stations);
			break;
		case 3:
			user.renewSub(user.subscription.ID, subs, user, plans);

			break;
		case 4:
			break;
		default:

			cout << "Invalid choice.\n";
			break;
		}
		cout << endl;
		cout << "Reffered to Main menu ! \n";
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
	case 3:
		cout << "\t \t \t Checking In !\n";
		if (user.subscription.Type != "Cash Wallet Cards") {
			va.StationExist(stations, user, ridee);
		}
		else
		{
			for (auto& station : stations) {
				cout << "ID : " << station.getID() << "  ->  " << station.getName() << endl;
			}
			cout << "Enter Your Source Station ID :) \n";
			cin >> srcid;
			cout << "Enter Your Destiantion Station ID :) \n";
			cin >> dstid;
			src = st.GetStationNameFromID(stations, srcid);
			dst = st.GetStationNameFromID(stations, dstid);
			user.checkIn(src, dst, ridee, stations, user);
		}
		cout << endl;
		cout << "Reffered to Main menu ! \n";
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
	case 4:
		cout << "Rides history.\n";
		user.viewRide(user);
		
		cout << endl;
		cout << "Reffered to Main menu ! \n";
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
	case 5:
		user.updateInfo(users);

		cout << "Reffered to Main menu ! \n";
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
	default:
		cout << "Invalid choice\n";


		cout << "Reffered to Main menu ! \n";
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
	}

}
void usermenu(vector <Subscription>& subs, User& user, vector <User>& users, vector <Ride>& ridee, vector <SubscriptionPlan>& plans, vector <Station>& stations) {
	int choice;
	bool login = false;
	while (true) {
		cout << "1- Login\n";
		cout << "2- Register\n";
		cout << "3- Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice >= 1 && choice <= 3) {

		break;
		}
		else {
			cout << "Invalid choice. Please enter a number between 1 and 3.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}


	switch (choice) {
	case 1:
		cout << "Login selected.\n";
		user = user.Login(users, login);
		cout << user.id << " " << user.userName << endl << user.subscription.final_station << "  " << user.ride[0].id;
		if (login) {
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
		}

		else {
			usermenu(subs, user, users, ridee, plans, stations);
		}
		break;
	case 2:

		cout << "Register selected.\n";
		user.Register(users);
		userfunctions(subs, user, users, ridee, plans, stations);
		break;
	case 3:

		cout << "Exiting...\n";
		break;
	default:

		cout << "Invalid choice.\n";
		break;
	}
	saveAlltoDataBase(subscriptions, users, rides, subplans, stations);


}
int adminMenu()
{
	Admin admin;
	User user;
	Ride ride;
	SubscriptionPlan subs;
	Subscription sub;
	vector<User> users = user.RetrieveUsersFromDatabase();
	vector<Station> stations = station.RetrieveStationsFromDatabase();
	vector<SubscriptionPlan> Subplans = subs.RetrieveSubplansFromDatabase();
	vector<Ride> rides = ride.RetrieveRidesFromDatabase();
	int choice;
	int user_id = 0;
	bool loggedIn = true;
	cout << "Hello boss!\n";
	while (loggedIn) {
		cout << "1. Manage users\n2. Manage stations\n3. Manage subscriptions\n4. Manage rides\n5. Mange fare\n0. Log out\n";
		cout << "Choose your choice:\n";
		cin >> choice;

		switch (choice)
		{
		case 0:
			loggedIn = false;
			break;
		case 1:
			cout << "------------------\n";
			while (true) {
				cout << "1. Edit user\n2. Delete user\n3. View user details\n4. View all users\n0. Return to main menu\n";
				cout << "Choose your choice:\n";
				cin >> choice;
				if (choice == 0)
					break;
				switch (choice)
				{
				case 1:
					admin.editUser(users);
					cout << "-----------------------------------\n";
					break;
				case 2:
					admin.deleteUser(users);
					cout << "-----------------------------------\n";
					break;
				case 3:
					admin.viewUser(users);
					cout << "-----------------------------------\n";
					break;
				case 4:
					admin.viewAllUsers(users);
					cout << "-----------------------------------\n";
					break;
				default:
					cout << "Invalid choice\n";
					break;
				}
			}
			cout << "\n";
			break;
		case 2:
			cout << "------------------\n";
			while (true) {
				cout << "1. Add station\n2. Edit station\n3. Delete station\n4. View station details\n5. View all stations\n0. Return to main menu\n";
				cout << "Choose your choice:\n";
				cin >> choice;
				if (choice == 0)
					break;
				switch (choice)
				{
				case 1:
					admin.addStation(stations);
					cout << "-----------------------------------\n";
					break;
				case 2:
					admin.editStation(stations);
					cout << "-----------------------------------\n";
					break;
				case 3:
					admin.deleteStation(stations);
					cout << "-----------------------------------\n";
					break;
				case 4:
					admin.viewStation(stations);
					cout << "-----------------------------------\n";
					break;
				case 5:
					admin.viewAllStations(stations);
					cout << "-----------------------------------\n";
					break;
				default:
					cout << "Invalid choice\n";
					break;
				}
			}
			cout << "\n";
			break;

		case 3:
			cout << "------------------\n";
			while (true) {
				cout << "1. Add subscription\n2. Edit subscription\n3. Delete subscription\n4. View all subscriptions\n0. Return to main menu\n";
				cout << "Choose your choice:\n";
				cin >> choice;
				if (choice == 0)
					break;
				switch (choice)
				{
				case 1:
					admin.addSubscriptionPlan(Subplans);
					cout << "-----------------------------------\n";
					break;
				case 2:
					admin.editSubscriptionPlan(Subplans);
					cout << "-----------------------------------\n";
					break;
				case 3:
					admin.deleteSubscriptionPlan(Subplans);
					cout << "-----------------------------------\n";
					break;
				case 4:
					admin.viewAllSubscriptionPlans(Subplans);
					cout << "-----------------------------------\n";
					break;
				default:
					cout << "Invalid choice\n";
					break;
				}
			}
			cout << "\n";
			break;

		case 4:
			cout << "------------------\n";
			while (true) {
				cout << "1. View specific user rides detail.\n2. View all rides.\n0. Return to main menu\n";
				cout << "Choose your choice:\n";
				cin >> choice;
				if (choice == 0)
					break;
				switch (choice)
				{
				case 1:
					ride.GetRidesForUser(user_id);
					cout << "-----------------------------------\n";
					break;
				case 2:
					admin.viewAllRideLogs(rides);
					cout << "-----------------------------------\n";
					break;
				default:
					cout << "Invalid choice\n";
					break;
				}
			}
			cout << "\n";
			break;
		case 5:
			cout << "------------------\n";
			while (true) {
				cout << "1. Manage fare\n0. Return to main menu\n";
				cout << "Choose your choice:\n";
				cin >> choice;
				if (choice == 0)
					break;
				switch (choice)
				{
				case 1:
					admin.FareManagement(Subplans);
					cout << "-----------------------------------\n";
					break;
				default:
					cout << "Invalid choice\n";
					break;
				}
			}
		}
	}
	saveAlltoDataBase(subscriptions, users, rides, subplans, stations);

	return choice;


}
void adminLogin() {
	string username;
	string password;
	bool loggedIn = false;

	while (!loggedIn) {
		cout << "--------------- Login ---------------\n";
		cout << "Enter your username: ";
		cin >> username;
		cout << "Enter your password: ";
		cin >> password;

		if (username == "admin" && password == "admin") {
			loggedIn = true;
			cout << "Login successful!\n";
			adminMenu();
		}
		else {
			cout << "Invalid username or password. Please try again.\n";
		}
	}
}
int main() {
	string username;

	cout << "welcome to fcis stations, glad to see you back!\n";
	int choice;
	while (true) {
		cout << "1- admin\n";
		cout << "2- user\n";
		cout << "3- exit\n";
		cout << "enter your choice: ";
		cin >> choice;

		if (choice >= 1 && choice <= 3) {

			break;
		}
		else {
			cout << "invalid choice. please enter a number between 1 and 3.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	switch (choice) {
	case 1:
		adminLogin();
		break;
	case 2:
		usermenu(subscriptions, user, users, rides, subplans, stations);
		userfunctions(subscriptions, user, users, rides, subplans, stations);

		break;
	case 3:

		cout << "exiting...\n";
		break;
	default:

		cout << "invalid choice.\n";
		break;
	}

}

