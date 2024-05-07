#pragma once
#include<iostream>
#include "Subscription.h"
#include "Ride.h"
#include"sqlite/sqlite3.h"

using namespace std;
class User
{
public:
	int id;
	int balance;
	string name;
	string userName;
	string password;
	string email;
	Subscription subscription;
	Ride ride;
	int subId;
	int rideId;
	vector<User> users;


	User();
	User(int id, string name, string email, string password, int balance, int subId, int rideId, string userName) :id(id), name(name), email(email), password(password), balance(balance), subId(subId), rideId(rideId), userName(userName) {}
	User(int userId, int userBalance, const std::string& userName, const std::string& userPassword, const std::string& userEmail)
		: id(userId), balance(userBalance), name(""), userName(userName), password(userPassword), email(userEmail)
	{
		userBalance = 0;
	}


	void Register(vector<User>& users, bool& infoUpdated); // make the bool infoUpdated = true if successfully Registered
	static void saveUsersToDatabase(vector<User>& users, bool Register);
	static vector<User> RetrieveUsersFromDatabase();
	string Login(vector<User> users);		// return the username
	void updateInfo(vector<User>& users, bool& infoUpdated); // make the bool infoUpdated = true if Info successfully updated

	Subscription purchaseSub(vector <Subscription>&, User&);
	void renewSub(int, vector <Subscription>&, User&);
	tm addDaysToDate(const tm& date, int daysToAdd);
	void renewSub();   
	void changeSub();
	void checkIn(Station source, Station destination);
	void checkOut();
	Ride viewRide();  // view ride for specific user


};

