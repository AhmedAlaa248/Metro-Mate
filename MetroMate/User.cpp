#include "User.h"
#include "Validator.h"
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

//int main() {
//	User user;
//	vector<User> users = User::RetrieveUsersFromDatabase();
//	user.updateInfo(users);
//
//	cout << "Updated List of Users:\n";
//	for (const auto& u : users) {
//		cout << "Name: " << u.name << ", Username: " << u.userName << ", Email: " << u.email << endl;
//	}
//
//	return 0;
//}

