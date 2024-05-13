#pragma once
#include<iostream>
#include "Subscription.h"
#include "Ride.h"
#include"sqlite/sqlite3.h"
#include "Station.h"

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
	vector<Ride> ride;
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


	void Register(vector<User>& users); // make the bool infoUpdated = true if successfully Registered
	static void saveUsersToDatabase(vector<User>& users);
	static vector<User> RetrieveUsersFromDatabase();
	void updateInfo(vector<User>& users); // make the bool infoUpdated = true if Info successfully updated
	User Looogin(vector<User> users, bool& q);

	Subscription purchaseSub(vector <Subscription>&, User&, vector <Station>&);
	void renewSub(int, vector <Subscription>&, User&, vector <SubscriptionPlan>);
	tm addDaysToDate(const tm& date, int daysToAdd);
	string Login(vector<User> users);
	void checkIn(string, string, vector <Ride>&, vector <Station>&, User&);
	void viewRide(User& user);
	Subscription changeSub(vector <Subscription>& subscriptionsList, User& user, vector <Station> stations);

};

