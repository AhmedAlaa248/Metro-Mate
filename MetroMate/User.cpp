#include "User.h"
#include "Validator.h"
#include "map"
#include "set"
#include <iomanip>
#include <chrono>
#include <sstream>
User::User() {
	id = 0; // Initialize id to 0
	balance = 0; // Initialize balance to 0
	// Initialize other member variables as needed
	name = "";
	userName = "";
	password = "";
	email = "";
}

void User::Register(vector<User>& users)
{
	User user;
	Validator validator;
	bool goodPassword = false;
	cout << "************* Welcome to User Registration *************\n";
	int newUserId = users.size() + 1;



	while (true)
	{
		cout << "Enter Your name:\n";
		cin >> user.name;
		while (true)
		{
			cout << "Enter your user name:\n";
			cin >> user.userName;

			if (!validator.UsedUserName(user.userName))
			{
				break;
			}
			else
			{
				cout << "Already taken username, please try again\n";
			}
		}
		break;
	}
	user.id = newUserId;
	user.balance = 0;  
	user.subId = 0;    
	user.rideId = 0;
	while (true)
	{
		cout << "Enter your password:\n";
		cin >> user.password;

		cout << "Confirm your password:\n";
		string confirmPassword;
		cin >> confirmPassword;

		if (user.password != confirmPassword)
		{
			cout << "Passwords do not match!\n";
			continue;
		}

		if (!validator.isStrongPassword(user.password))
		{
			cout << "Password is weak. Please choose a stronger one.\n";
			continue;
		}

		goodPassword = true;
		break;
	}

	while (true)
	{
		cout << "Enter your email:\n";
		cin >> user.email;

		if (validator.isValidEmailAddress(user.email))
		{
			break;
		}
		else
		{
			cout << "Invalid email, please try again\n";
		}
	}

	cout << "Account created successfully.\n\n";
	users.push_back(user);


}

vector<User> User::RetrieveUsersFromDatabase()
{
	vector <User> userList;
	sqlite3* db;
	int rc = sqlite3_open("mydb.db", &db);

	if (rc != SQLITE_OK)
	{
		// Error opening the database
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db); 
		return userList;   
	}


	const char* sql = "Select ID,Name,Email,Password,Balance,[Subscription-idd],[rides_idd],[User_Name] FROM User";
	//const char* sql = "Select ID From User";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK)
	{
		cout << "Error preparing the SQL statement" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return userList;
		cout << "SQL Query: " << sql << endl;


	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int id = sqlite3_column_int(stmt, 0);
		const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		const char* password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		int balance = sqlite3_column_int(stmt, 4);
		int subId = sqlite3_column_int(stmt, 5);
		int rideId = sqlite3_column_int(stmt, 6);
		const char* userName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
	
		userList.push_back(User(id, name, email,password, balance, subId,rideId,userName));
		//userList.push_back(User(id));
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return userList;
}
Subscription User::purchaseSub(vector <Subscription>& z, User& oo) {
	vector<SubscriptionPlan> plans = SubscriptionPlan::RetrieveSubplansFromDatabase();
	cout << "--------------------Available programs--------------------" << endl;
	int count = 1;
	map<int, string> planTypeMap;
	set<int> uniqueTypes;

	for (const auto& plan : plans) {
		if (uniqueTypes.find(plan.getType()) == uniqueTypes.end()) {
			count++; cout << "- " << plan.getType() << "- " << plan.getplan_name() << endl;
			planTypeMap[count - 1] = plan.getplan_name();
			uniqueTypes.insert(plan.getType());
		}
	}

	int selectedType;
	bool validInput = false;
	while (!validInput) {
		cout << "Please Select Number of Desired Program Type: ";
		cin >> selectedType;

		if (uniqueTypes.find(selectedType) != uniqueTypes.end()) {
			validInput = true;
		}
		else {
			cout << "Invalid input. Please enter a valid program type number." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}


	cout << "--------------------Stages for Selected Program Type " << selectedType << "--------------------" << endl;
	for (const auto& plan : plans) {
		if (plan.getType() == selectedType) {
			cout << "Plan ID :  " << plan.getplan_id() << endl;
			cout << "Plan Name: " << plan.getplan_name() << endl;
			cout << "Stage: " << plan.getstages() << endl;
			cout << "Price: " << plan.getPrice() << endl;
			cout << "Duration: " << plan.getDuration() << " Months" << endl;
			cout << "Number of Stations: " << plan.getNumStations() << endl;
			cout << "--------------------------------------------" << endl;
		}
	}

	int planId;
	string typee;
	int durationn, remainingrides;
	bool validId = false;
	while (!validId) {
		cout << "Please Choose ID Of Desired Plan: ";
		cin >> planId;

		for (const auto& plan : plans) {
			if (plan.getplan_id() == planId && plan.getType() == selectedType) {
				validId = true;
				typee = plan.getplan_name();
				durationn = plan.getDuration();
				remainingrides = plan.gettrips();
				break;
			}
		}

		if (!validId) {
			cout << "Invalid input. Please enter a valid plan ID for the selected program type." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	time_t currentTime = time(nullptr);
	tm currentDate;
	localtime_s(&currentDate, &currentTime);


	stringstream currentDateString;
	currentDateString << (currentDate.tm_year + 1900) << "/" << (currentDate.tm_mon + 1) << "/" << currentDate.tm_mday;
	string currentDateStr = currentDateString.str();

	//	cout << "Current Date: " << currentDateStr << endl;


	tm newDate = addDaysToDate(currentDate, durationn * 30);


	stringstream newDateString;
	newDateString << (newDate.tm_year + 1900) << "/" << (newDate.tm_mon + 1) << "/" << newDate.tm_mday;
	string newDateStr = newDateString.str();

	//	cout << "New Date after adding 8 days: " << newDateStr << endl;
			//int id, std::string type, std::string subDate, std::string endDate
			// , int remainingRides, int userId, int subId, string sourceStation, string finalStation
	int idp = z.size() + 1;
	Subscription  ebla3(idp, typee, currentDateStr, newDateStr, remainingrides, oo.id, planId, "avva", "sas");
	z.push_back(ebla3);
	oo.subId = idp;
	oo.subscription = ebla3;
	return ebla3;
};
tm User::addDaysToDate(const tm& date, int daysToAdd) {
	// Convert the input date to a time_t
	time_t time = mktime(const_cast<tm*>(&date));

	// Add the specified number of seconds (seconds in a day * daysToAdd)
	time += (daysToAdd * 24 * 60 * 60);

	// Convert the updated time back to a tm structure
	tm newDate;
	localtime_s(&newDate, &time);

	return newDate;
}
void User::renewSub(int subscid, vector <Subscription>& z, User& o) {
	cout << "Your Current plan details will be loaded ! \n";
	for (auto& w : z) {
		if (subscid == w.ID) {
			cout << "Subscription ID: " << w.ID << endl;
			cout << "Subscription Type: " << w.Type << endl;
			cout << "Subscription Start Date: " << w.Sub_datee << endl;
			cout << "Subscription End Date: " << w.End_datee << endl;
			cout << "Remaining Rides: " << w.remaining_rides << endl;
		}
	}

	int num;
	bool validInput = false;
	while (!validInput) {
		cout << "Press 1 to Renew your Subscription plan ! ";
		cin >> num;
		if (cin.fail() || num != 1) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter 1 to renew your subscription plan." << endl;
		}
		else {
			validInput = true;
		}
	}


}
string User::Login(vector<User> users) {
	Validator validator;

	bool validUsername = false;
	bool validPassword = false;
	string userName;
	string password;

	while (!validUsername) {
		cout << "Enter username: ";
		cin >> userName;

		for (const auto& user : users) {
			if (user.userName == userName) {
				validUsername = true;
				break;
			}
		}

		if (!validUsername) {
			cout << "Username not correct. Please try again.\n";
		}
	}

	while (!validPassword) {
		cout << "Enter password: ";
		cin >> password;

		for (const auto& user : users) {
			if (user.userName == userName && user.password == password) {
				validPassword = true;
				break;
			}
		}

		if (!validPassword) {
			cout << "Wrong Password. Please try again.\n";
		}
	}

	cout << "Login successful\n";
	return userName;
}

void User::updateInfo(vector<User>& users) {
	int choice;
	string signedInUsername = Login(users);
	Validator validator;

	int signedInUserIndex = -1;
	for (size_t i = 0; i < users.size(); ++i) {
		if (users[i].userName == signedInUsername) {
			signedInUserIndex = i;
			break;
		}
	}


	
		cout << "Choose what you want to change:\n"
			<< "1. Change Name\n"
			<< "2. Change Email\n"
			<< "3. Change Password\n"
			<< "4. Change Username\n"
			<< "Enter your choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1: {
			cout << "Enter new name: ";
			getline(cin, users[signedInUserIndex].name);
			break;
		}
		case 2: {
			cout << "Enter new email: ";
			getline(cin, users[signedInUserIndex].email);
			break;
		}
		case 3: {
			cout << "Enter new password: ";
			getline(cin, users[signedInUserIndex].password);
			break;
		}
		case 4: {
			string newUsername;
			/*cout << "Enter new username: ";
			getline(cin, users[signedInUserIndex].userName);
			break;*/
			while (true)
			{
				cout << "Enter your user name:\n";
				getline(cin, users[signedInUserIndex].userName);

				if (!validator.UsedUserName(users[signedInUserIndex].userName))
				{
					break;
				}
				else
				{
					cout << "Already taken username, please try again\n";
				}
			}
		}
		default:
			break;
		}
	
}

int main() {
	User o;
	o.id = 1;
	SubscriptionPlan v;
	Subscription z;
	vector <Subscription> q = z.Subscriptions();
	vector <Subscription> wqw = z.Subscriptions();
	z = o.purchaseSub(wqw, o);
	for (auto& w : wqw) {
		cout << "Subscription ID: " << w.ID << endl;
		cout << "Subscription Type: " << w.Type << endl;
		cout << "Subscription Start Date: " << w.Sub_datee << endl;
		cout << "Subscription End Date: " << w.End_datee << endl;
		cout << "Remaining Rides: " << w.remaining_rides << endl;
		cout << "User ID: " << w.user_idd << endl;
		cout << "Subscription Plan ID: " << w.sub_idd << endl;
		cout << "Source Station: " << w.source_station << endl;
		cout << "Final Station: " << w.final_station << endl;
	}
}

