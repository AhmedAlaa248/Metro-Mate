#include "User.h"
#include "Validator.h"
#include "map"
#include "set"
#include <iomanip>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
User::User() {
	id = 0;
	balance = 0;
	name = "";
	userName = "";
	password = "";
	email = "";
}

void User::Register(vector<User>& users, User& user)
{

	Validator validator;
	bool goodPassword = false;
	cout << "************* Welcome to User Registration *************\n";
	// Get the number of existing users
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

	user.id = newUserId;
	users.push_back(user);
}
void User::updateInfo(vector<User>& users) {
	bool goodPassword = false;
	int choice;
	bool q = false;
	User signedInUser = Login(users, q); // Get the signed in user

	// Find the index of the signed in user in the users vector
	int signedInUserIndex = -1;
	for (size_t i = 0; i < users.size(); ++i) {
		if (users[i].userName == signedInUser.userName) {
			signedInUserIndex = i;
			break;
		}
	}

	Validator validator;

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
		getline(cin, signedInUser.name);
		break;
	}
	case 2: {
		while (true) {
			cout << "Enter your new email:\n";
			cin >> signedInUser.email;

			if (validator.isValidEmailAddress(signedInUser.email)) {
				break;
			}
			else {
				cout << "Invalid email, please try again\n";
			}
		}
		break;
	}
	case 3: {
		while (true) {
			cout << "Enter your new password:\n";
			cin >> signedInUser.password;

			cout << "Confirm your password:\n";
			string confirmPassword;
			cin >> confirmPassword;

			if (signedInUser.password != confirmPassword) {
				cout << "Passwords do not match!\n";
				continue;
			}

			if (!validator.isStrongPassword(signedInUser.password)) {
				cout << "Password is weak. Please choose a stronger one.\n";
				continue;
			}

			goodPassword = true;
			break;
		}
		break;
	}
	case 4: {
		string newUsername;
		while (true) {
			cout << "Enter your user name:\n";
			getline(cin, signedInUser.userName);

			if (!validator.UsedUserName(signedInUser.userName)) {
				break;
			}
			else {
				cout << "Already taken username, please try again\n";
			}
		}
	}
	default:
		break;
	}

	// Update the corresponding user in the users vector with the modified signedInUser
	if (signedInUserIndex != -1) {
		users[signedInUserIndex] = signedInUser;
	}
	cout << "Info updated Successfully\n";
}
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
User User::Login(vector<User> users, bool& q) {
	Validator validator;
	Ride Rides;
	Subscription Subs;

	int maxAttempts = 3;
	int attempts = 0;

	string userName;
	string password;
	bool validUsername = false;
	bool validPassword = false;
	while (attempts < maxAttempts) {

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
			++attempts;
			continue;
		}
		if (validUsername) {
			attempts = 0;;
			break;
		}

	}
	if (validUsername) {
		while (attempts < maxAttempts) {


			cout << "Enter password: ";
			cin >> password;

			for (const auto& user : users) {
				if (user.userName == userName && user.password == password) {

					validPassword = true;
					q = true;
					User founduser(user.id, user.name, user.email, user.password, user.balance, user.subId, user.rideId, user.userName);
					founduser.ride = Rides.GetRidesForUser(founduser.id);
					founduser.subscription = Subs.getSubscriptionForUser(founduser.id);
					Station test;
					vector <Station> stationss = test.RetrieveStationsFromDatabase();
					test.addToAdjacency(stationss);
					vector<vector<string>> allPaths = test.findAllPaths(founduser.subscription.source_station, founduser.subscription.final_station);

					founduser.subscription.pathchoices = Subs.stationofpath(allPaths, founduser.subscription.path - 1);
					return founduser;

					break;


				}

			}

			if (!validPassword) {
				cout << "Wrong Password. Please try again.\n";
				++attempts;
			}
			else {
				cout << "Login successful\n";
				break;

			}
		}
	}
	else {
		// If max attempts reached without successful login, inform user and return empty string
		cout << "Maximum login attempts reached. Exiting.\n";


	}

}
void User::saveUsersToDatabase(vector<User>& users) {
	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK) {
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// Delete all existing records from the User table
	const char* delete_sql = "DELETE FROM User";
	rc = sqlite3_exec(db, delete_sql, nullptr, nullptr, nullptr);

	if (rc != SQLITE_OK) {
		cout << "Error deleting records from the User table: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// SQL query to insert a new record
	const char* insert_sql = "INSERT INTO User (ID, Name, Email, Password, Balance, [Subscription-idd], [rides_idd], [User_Name]) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

	for (const auto& user : users) {
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);

		if (rc != SQLITE_OK) {
			cout << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}

		// Bind parameters to the prepared statement
		sqlite3_bind_int(stmt, 1, user.id);
		sqlite3_bind_text(stmt, 2, user.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, user.email.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, user.password.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 5, user.balance);
		sqlite3_bind_int(stmt, 6, user.subId);
		sqlite3_bind_int(stmt, 7, user.rideId);
		sqlite3_bind_text(stmt, 8, user.userName.c_str(), -1, SQLITE_STATIC);

		// Execute the SQL statement
		rc = sqlite3_step(stmt);

		if (rc != SQLITE_DONE) {
			cout << "Error executing the SQL statement: " << sqlite3_errmsg(db) << endl;
		}

		// Finalize the statement
		sqlite3_finalize(stmt);
	}

	sqlite3_close(db);
}
vector<User> User::RetrieveUsersFromDatabase()
{
	vector <User> userList;
	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

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

		userList.push_back(User(id, name, email, password, balance, subId, rideId, userName));
		//userList.push_back(User(id));
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return userList;
}

Subscription User::purchaseSub(vector <Subscription>& z, User& user, vector <Station>& stationss) {
	int inn;
	bool validInputt = false;
	int price;
	while (!validInputt) {
		cout << "For Cash Wallet System Press 1 else 0: ";
		cin >> inn;

		if (cin.fail() || (inn != 0 && inn != 1)) {
			cout << "Invalid input. Please enter 1 or 0." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			validInputt = true;
		}
	}
	if (inn == 0) {
		vector<SubscriptionPlan> plans = SubscriptionPlan::RetrieveSubplansFromDatabase();
		Station test;
		int srcId, dstId;
		string src, dst;
		bool validSrcId = false;
		while (!validSrcId) {
			cout << "Choose ID of your Source Station: " << endl;
			for (auto& station : stationss) {
				cout << "ID : " << station.getID() << "  , Name:    " << station.getName() << endl;
			}


			cin >> srcId;
			for (auto& station : stationss) {
				if (station.getID() == srcId) {
					validSrcId = true;
					src = test.GetStationNameFromID(stationss, srcId);
					break;
				}
			}
			if (!validSrcId) {
				cout << "Invalid station ID. Please choose a valid ID from the list." << endl;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		bool validDstId = false;
		while (!validDstId) {
			cout << "Choose ID of your Destination Station:" << endl;
			cin >> dstId;


			for (auto& station : stationss) {
				if (station.getID() == dstId) {
					validDstId = true;
					dst = test.GetStationNameFromID(stationss, dstId);
					break;
				}
			}
			if (dstId == srcId) {
				cout << "Destination station ID cannot be the same as the source station ID." << endl;
				cout << "Insert Another one \n ";
				validDstId = false;
			}
			if (!validDstId) {
				cout << "Invalid station ID. Please choose a valid ID from the list." << endl;
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}


		test.addToAdjacency(stationss);
		vector<vector<string>> allPaths = test.findAllPaths(test.GetStationNameFromID(stationss, srcId), test.GetStationNameFromID(stationss, dstId));
		string source = test.GetStationNameFromID(stationss, srcId);
		string destination = test.GetStationNameFromID(stationss, dstId);
		if (!allPaths.empty()) {
			cout << "Shortest path between stations " << source << " and " << destination << ":" << endl;
			for (const string& station : allPaths.front()) {
				cout << station << "  ";
			}
			cout << endl << endl;

			cout << "All paths between stations " << source << " and " << destination << ":" << endl;
			for (size_t i = 0; i < allPaths.size(); ++i) {
				cout << "Path " << i + 1 << ": ";
				for (const string& station : allPaths[i]) {
					cout << station << "    ";
				}
				cout << endl;
			}
		}
		else {
			cout << "No path found between stations " << source << " and " << destination << endl;
		}
		int pathchoice;
		int length;
		vector <string> pathsss;
		while (true) {
			cin >> pathchoice;
			if (pathchoice > 0 && pathchoice <= allPaths.size()) {
				length = test.FindLengthOfSpecificPath(pathchoice - 1);
				pathsss = subscription.stationofpath(allPaths, pathchoice - 1);
				break;
			}
			else {

				cout << "Invalid path choice. Please enter a valid path choice." << endl;
			}
		}


		cout << "--------------------Available programs--------------------" << endl;
		int count = 1;
		map<int, string> planTypeMap;
		set<int> uniqueTypes;

		for (const auto& plan : plans) {
			if (plan.getplan_name() == "Cash Wallet Cards") {
				continue;
			}

			if (uniqueTypes.find(plan.getType()) == uniqueTypes.end()) {
				count++;
				cout << "- " << plan.getType() << "- " << plan.getplan_name() << endl;
				planTypeMap[count - 1] = plan.getplan_name();
				uniqueTypes.insert(plan.getType());
			}
		}

		int selectedType;
		bool validInput = false;
		while (!validInput) {
			cout << "Please Select Number of Desired Program Type: ";
			cin >> selectedType;

			if (planTypeMap.find(selectedType) != planTypeMap.end()) {
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
			if (plan.getType() == selectedType && length <= plan.getNumStations()) {
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
				if (plan.getplan_id() == planId && plan.getType() == selectedType && length <= plan.getNumStations()) {

					validId = true;
					typee = plan.getplan_name();
					durationn = plan.getDuration();
					remainingrides = plan.gettrips();
					price = plan.getPrice();
					if (user.balance < price) {
						validId = false;
					}
					else {
						user.balance -= price;
					}
					break;
				}
			}

			if (!validId) {
				cout << "Invalid input. Please Try Again . \n" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		cout << "-------------------------------------\n";
		cout << "Subscription Done Successfully :) \n";
		time_t currentTime = time(nullptr);
		tm currentDate;
		localtime_s(&currentDate, &currentTime);
		stringstream currentDateString;
		currentDateString << (currentDate.tm_year + 1900) << "/" << (currentDate.tm_mon + 1) << "/" << currentDate.tm_mday;

		string currentDateStr = currentDateString.str();
		tm newDate = addDaysToDate(currentDate, durationn * 30);
		stringstream newDateString;
		newDateString << (newDate.tm_year + 1900) << "/" << (newDate.tm_mon + 1) << "/" << newDate.tm_mday;



		string newDateStr = newDateString.str();


		int sub_id = z.size() + 1;
		Subscription  s(sub_id, typee, currentDateStr, newDateStr, remainingrides, user.id, planId, src, dst, pathchoice);
		z.push_back(s);
		user.subId = sub_id;
		user.subscription = s;
		user.subscription.pathchoices = pathsss;
		for (auto& u : users) {
			if (u.id == user.id) {
				u.subId = sub_id;
				u.balance -= price;
			}
		}
		for (auto& st : stationss) {
			if (st.name == src) {
				st.totalIncome += price;
				st.numOfPassengers++;
				st.numOfSoldTickets++;
			}
		}
		return s;

	}
	else {
		int cardlimit;
		bool validInput = false;

		while (!validInput) {
			cout << "Enter Balance to Add to your Card (Max 400, Multiple of 10): ";
			cin >> cardlimit;

			if (cin.fail() || cardlimit < 0 || cardlimit > 400 || cardlimit % 10 != 0) {
				cout << "Invalid input. Please enter a value between 0 and 400 that is a multiple of 10." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else {
				validInput = true;
			}
		}
		user.balance = cardlimit;
		time_t currentTime = time(nullptr);
		tm currentDate;
		localtime_s(&currentDate, &currentTime);
		stringstream currentDateString;
		currentDateString << (currentDate.tm_year + 1900) << "/" << (currentDate.tm_mon + 1) << "/" << currentDate.tm_mday;

		string currentDateStr = currentDateString.str();

		int sub_id = z.size() + 1;
		Subscription  s(sub_id, "Cash Wallet Cards", currentDateStr, " ", 999999, user.id, 13, " ", " ", 0);
		z.push_back(s);
		user.subId = sub_id;
		user.subscription = s;
		for (auto& u : users) {
			if (u.id == user.id) {
				u.subId = sub_id;
			}
		}

		return s;
		cout << "-------------------------------------\n";
		cout << "Subscription Done Successfully :) \n";

	}

}
void User::renewSub(int subscid, vector <Subscription>& z, User& o, vector <SubscriptionPlan> plans) {
	string ptype;
	cout << "Your Current plan details will be loaded ! \n";
	for (auto& w : z) {
		if (subscid == w.ID) {
			cout << "Subscription ID: " << w.ID << endl;
			cout << "Subscription Type: " << w.Type << endl;
			cout << "Subscription Start Date: " << w.Sub_datee << endl;
			if (w.Type != "Cash Wallet Cards")
			{
				cout << "Subscription End Date: " << w.End_datee << endl;
			}
			cout << "Remaining Rides: " << w.remaining_rides << endl;
			ptype = w.Type;

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

	string dateStr = o.subscription.End_datee;
	tm parsedDate = {};
	istringstream ss(dateStr);
	const char* format = "%Y/%m/%d";
	ss >> std::get_time(&parsedDate, format);
	tm date;
	if (!ss.fail()) {

		date = parsedDate;

	}
	else {
		std::cout << "Failed to parse date." << std::endl;
	}

	stringstream newDateString;
	string newDateStr = newDateString.str();


	if (ptype == "Student Card") {

		cout << "Subscription Renewed Successfully :) \n";


		date = addDaysToDate(date, 90);
		newDateString << (date.tm_year + 1900) << "/" << (date.tm_mon + 1) << "/" << date.tm_mday;
		newDateStr = newDateString.str();
		o.subscription.End_datee = newDateStr;
		o.subscription.remaining_rides += 180;


	}
	else if (ptype == "Public Card")
	{
		int n;
		while (true) {
			cout << "1- Renew Month\n";
			cout << "2- Renew Year \n";
			cout << "enter your choice: ";
			cin >> n;

			if (n >= 1 && n <= 2) {

				break;
			}
			else {
				cout << "invalid choice. please enter a number between 1 and 3.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		switch (n) {
		case 1:

			date = addDaysToDate(date, 30);
			o.subscription.remaining_rides += 60;
			newDateString << (date.tm_year + 1900) << "/" << (date.tm_mon + 1) << "/" << date.tm_mday;
			newDateStr = newDateString.str();
			o.subscription.End_datee = newDateStr;
			cout << "Renewed Successfully \n";
			break;
		case 2:
			date = addDaysToDate(date, 365);
			o.subscription.remaining_rides += 730;
			newDateString << (date.tm_year + 1900) << "/" << (date.tm_mon + 1) << "/" << date.tm_mday;
			newDateStr = newDateString.str();
			o.subscription.End_datee = newDateStr;
			cout << "Renewed Successfully \n";

			break;
		default:

			cout << "invalid choice.\n";
			break;
		}



	}
	else if (ptype == "Cash Wallet Cards")
	{
		int cardlimit;
		bool validInput = false;

		while (!validInput) {
			cout << "Enter Balance to Add to your Card (Max 400, Multiple of 10): ";
			cin >> cardlimit;

			if (cin.fail() || cardlimit < 0 || cardlimit > 400 || cardlimit % 10 != 0 || (o.balance + cardlimit) > 400) {
				cout << "Invalid input. Please enter a value between 0 and 400 that is a multiple of 10 and ensures total balance does not exceed 400." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else {
				validInput = true;
				cout << "Done Successfully \n";
			}
		}


	}
	else {
		int duration;
		int remainingrides;
		cout << "Subscription Renewed Successfully :) \n";
		for (auto& subs : plans) {
			if (subs.getplan_id() == o.subId) {
				duration = subs.getDuration();
				remainingrides = subs.gettrips();
			}
		}
		date = addDaysToDate(date, duration * 30);
		newDateString << (date.tm_year + 1900) << "/" << (date.tm_mon + 1) << "/" << date.tm_mday;
		newDateStr = newDateString.str();
		o.subscription.End_datee = newDateStr;
		o.subscription.remaining_rides += remainingrides;


	}
	if (o.subscription.Type != "Cash Wallet Cards") {
		for (auto& subs : z) {

			if (subs.ID == o.subscription.ID) {
				subs.End_datee = o.subscription.End_datee;
				subs.remaining_rides = o.subscription.remaining_rides;

			}
		}
	}



}
void User::checkIn(string source, string destination, vector<Ride>& rides, vector<Station>& stations, User& user) {

	time_t currentTime = time(nullptr);
	tm currentDate;
	localtime_s(&currentDate, &currentTime);
	stringstream currentDateString;
	currentDateString << (currentDate.tm_year + 1900) << "/" << (currentDate.tm_mon + 1) << "/" << currentDate.tm_mday;
	string currentDateStr = currentDateString.str();

	Station test;
	int stationid = test.GetStationIdFromName(stations, source);
	int rideid = rides.size() + 1;
	int fare;



	if (user.subscription.Type == "Cash Wallet Cards")
	{

		test.addToAdjacency(stations);
		vector<vector<string>> allPaths = test.findAllPaths(source, destination);

		if (!allPaths.empty()) {
			cout << "Shortest path between stations " << source << " and " << destination << ":" << endl;
			for (const string& station : allPaths.front()) {
				cout << station << " ";
			}
			cout << endl;

			cout << "All paths between stations " << source << " and " << destination << ":" << endl;
			for (size_t i = 0; i < allPaths.size(); ++i) {
				cout << "Path " << i + 1 << ": ";
				for (const string& station : allPaths[i]) {
					cout << station << "    ";
				}
				cout << endl;
			}
		}
		else {
			cout << "No path found between stations " << source << " and " << destination << endl;
		}
		int pathchoice;
		int length;

		while (true) {
			cin >> pathchoice;
			if (pathchoice > 0 && pathchoice <= allPaths.size()) {
				length = test.FindLengthOfSpecificPath(pathchoice - 1);
				break;
			}
			else {

				cout << "Invalid path choice. Please enter a valid path choice." << endl;
			}
		}
		if (length <= 9) {
			for (auto& sts : stations)
			{
				if (sts.getID() == stationid) {
					sts.totalIncome += 6;
					fare = 6;
					user.balance -= fare;
				}
			}
		}
		else if (length <= 16) {
			for (auto& sts : stations)
			{
				if (sts.getID() == stationid) {
					sts.totalIncome += 8;
					fare = 8;
					user.balance -= fare;
				}
			}
		}
		else if (length <= 23)
		{
			for (auto& sts : stations)
			{
				if (sts.getID() == stationid) {
					sts.totalIncome += 12;
					fare = 12;
					user.balance -= fare;
				}
			}
		}
		else {
			for (auto& sts : stations)
			{
				if (sts.getID() == stationid) {
					sts.totalIncome += 15;
					fare = 15;
					user.balance -= fare;
				}
			}
		}
		for (auto& sts : stations)
		{
			if (sts.getID() == stationid) {
				sts.numOfPassengers++;
				sts.numOfSoldTickets++;
			}
		}
	}
	else {
		for (auto& sts : stations)
		{
			if (sts.getID() == stationid) {
				sts.numOfPassengers++;
				sts.numOfSoldTickets++;
				fare = 0;
			}
		}
	}
	Ride s(rideid, source, destination, stationid, currentDateStr, user.id, fare);
	rides.push_back(s);
	user.ride.push_back(s);
	cout << "Done Successfully \n";
	cout << "Have A Nice Dayy \n";
}
Subscription User::changeSub(vector <Subscription>& subscriptionsList, User& user, vector<Station> stations)
{

	for (size_t i = 0; i < subscriptionsList.size(); ++i)
	{
		if (subscriptionsList[i].ID == user.subscription.ID) {
			subscriptionsList.erase(subscriptionsList.begin() + i);
			return purchaseSub(subscriptionsList, user, stations);

		}
	}
	return Subscription();
}
void User::viewRide(User& user) {
	cout << endl;
	for (int i = 0; i < user.ride.size(); i++) {
		cout << "Ride Id : " << user.ride[i].id << endl;
		cout << "Ride Source : " << user.ride[i].source << endl;
		cout << "Ride Destination : " << user.ride[i].destination << endl;
		cout << "Ride Date : " << user.ride[i].ridedate << endl;
		cout << "Ride Fare : " << user.ride[i].fare << endl;
		cout << endl;
	}
}
