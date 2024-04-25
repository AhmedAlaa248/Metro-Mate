A.Waheed
waheed2200
Invisible

A.Waheed — 04/15/2023 1:37 AM
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
bool check_ph;
int sign;
Expand
message.txt
11 KB
A.Waheed
 started a call that lasted 5 minutes.
 — 12/28/2023 10:42 PM
Midoo
 started a call that lasted 7 minutes.
 — 01/19/2024 7:57 PM
A.Waheed — 04/17/2024 3:24 PM
https://discord.gg/CxbFNMcy
Midoo — 04/18/2024 8:12 PM
Attachment file type: unknown
mydb.db
56.00 KB
A.Waheed — 04/19/2024 8:08 PM
Attachment file type: unknown
mydb_1.db
56.00 KB
A.Waheed — 04/23/2024 9:45 PM
User.H
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
    User( int id,string name,string email,string password,int balance,int subId,int rideId,string userName):id(id),name(name),email(email), password(password), balance(balance), subId(subId),rideId(rideId),userName(userName){}
    User(int userId, int userBalance, const std::string& userName, const std::string& userPassword, const std::string& userEmail)
        : id(userId), balance(userBalance), name(""), userName(userName), password(userPassword), email(userEmail)
    {
        userBalance = 0;
    }


    vector<User> Register(string name,string userName,string email ,string password);
    static vector<User> RetrieveUsersFromDatabase();

    void Login(string userName, string password);
    void purchaseSub(int subType, int stage);
    void renewSub();
    void changeSub();
    void checkIn(Station source, Station destination);
    void checkOut();
    Ride viewRide();  // view ride for specific user
    void updateInfo();



};
User.cpp
#include "User.h"
#include "Validator.h"
User::User() {
id = 0; // Initialize id to 0
balance = 0; // Initialize balance to 0
// Initialize other member variables as needed
Expand
message.txt
5 KB
A.Waheed — 04/23/2024 10:05 PM
#pragma once
#include<iostream>
#include "User.h"
#include "Validator.h"

using namespace std;
Expand
wqw.txt
37 KB
A.Waheed — 04/23/2024 10:23 PM
int main()
{
    // Create a new user account
    User newUser;
    vector <User> usersappend;
    usersappend = newUser.Register("John Doe", "john_doe", "john@example.com", "password123");
    cout << "List of users after creating a new account:\n";
    for (const auto& user : usersappend)
    {
        cout << "ID: " << user.id << endl;
        cout << "Name: " << user.name << endl;
        cout << "Email: " << user.email << endl;
        cout << "Password: " << user.password << endl;
        cout << "Balance: " << user.balance << endl;
        cout << "Subscription ID: " << user.subId << endl; // Adjust as per your data structure
        cout << "Ride ID: " << user.rideId << endl; // Adjust as per your data structure
        cout << "User Name: " << user.userName << endl;
        cout << "------------------------" << endl;
    }



}
A.Waheed — Yesterday at 3:22 PM
#include"SubscriptionPlan.h"


SubscriptionPlan::SubscriptionPlan()
{
}
Expand
message.txt
7 KB
You missed a call from 
Midoo
 that lasted a few seconds.
 — Yesterday at 4:02 PM
A.Waheed — Yesterday at 4:03 PM
#include <iostream>
#include <string>
#include<vector>
#include"sqlite/sqlite3.h"
using namespace std;
class SubscriptionPlan {
private:
    int type;
    int price;
    int duration;
    int numStations;
    string plan_name;
    int trips;
    int stages;
    int plan_id;


    // constructor
public:
    SubscriptionPlan();
    SubscriptionPlan(int type, int price, int duration, int numStations)
        : type(type), price(price), duration(duration), numStations(numStations) {}

    SubscriptionPlan(int plan_id, string plan_name, int duration,int price,int trips, int stages, int type)
        : plan_id(plan_id), plan_name(plan_name), duration(duration), price(price), trips(trips), stages(stages), type(type){}


    // Setters
    void setType(int newtype);
    void setPrice(int newPrice);
    void setDuration(int newDuration);
    void setNumStations(int newNumStations);
    void setplan_name(string newplan_name);
    void setplan_id(int newplan_id);
    void settrips(int newtrips);
    void setstages(int newstages);

    // Getters
    int getType() const;
    int getPrice() const;
    int getDuration() const;
    int getNumStations() const;
    int getplan_id() const;
    int getstages() const;
    int gettrips() const;
    string getplan_name() const;

    int calcFare(int subscriptionType, int stage);
    int calculateStudentFare(int stage) const;
    int calculateMonthlyPublicFare(int stage) const;
    int calculateYearlyPublicFare(int stage) const;
    int calculateCashWalletFare(int numStations) const;
    void DisplayAllPlans() const;

    static vector<SubscriptionPlan>RetrieveSubplansFromDatabase();

};
Midoo — Today at 8:51 PM
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Station
{
    int id;
    string name;
    int lineNum;
public:
    string linenum2;
    static int nextId;    //auto increament
    long totalIncome; //increased when add subscription
    long numOfSoldTickets;
    long numOfSubscriptions; //increased when add subscription
    long long numOfPassengers;

    unordered_map<int, unordered_set<int>> adjacencyList;
    vector<vector<int>> allPaths;

    Station();
    Station(int id, string name, int inc, int tix, int passengers, string line, int subscriptions);
    Station(string n, int line);

    //Getters
    int getID() const;
    string getName() const;
    int getLineNum() const;
    vector <Station> RetrieveStationsFromDatabase();
    static pair<bool, Station> findStationByName(string name, unordered_map<int, Station> stations);
    void rideStarted(string type);
    void addConnection(int station1, int station2);
    void removeConnection(int station1, int station2);
    void removeStation(int station);
    void addConnectionToStation(Station& station, unordered_map<int, Station> stations);
    void addStation(unordered_map<int, Station> stations);
    void displayDetails(string type);
    void printDetails();
};

#include "Station.h"
#include "sqlite/sqlite3.h"
#include <winsqlite/winsqlite3.h>

Station::Station()
{

totalIncome = 0;
numOfSoldTickets = 0;
numOfSubscriptions = 0;
numOfPassengers = 0;
}

Station::Station(string n, int line)
{

name = n;
lineNum = line;
totalIncome = 0;
numOfSoldTickets = 0;
numOfSubscriptions = 0;
numOfPassengers = 0;

}
Station::Station(int idd, string namee, int inc, int tix, int passengers, string line, int subscriptions) {
id = idd;
name = namee;
totalIncome = inc;
numOfSoldTickets = tix;
numOfPassengers = passengers;
linenum2 = line;
numOfSubscriptions = subscriptions;
}

int Station::getID() const
{
return id;
}

string Station::getName() const
{
return name;
}

int Station::getLineNum() const
{
return lineNum;
}

pair<bool, Station> Station::findStationByName(string name, unordered_map<int, Station> stations)
{
Station station;
bool found = false;
for (auto it = stations.begin(); it != stations.end(); it++)
{
if ((*it).second.name == name)
{
station = (*it).second;
found = true;
break;
}
}
return pair<bool, Station>(found, station);
}

void Station::rideStarted(string type)
{
if (type == "Cash Wallet")
numOfSoldTickets++;

numOfPassengers++;
}


void Station::addConnection(int station1, int station2) {
adjacencyList[station1].insert(station2);
adjacencyList[station2].insert(station1);
}

void Station::removeConnection(int station1, int station2) {
adjacencyList[station1].erase(station2);
adjacencyList[station2].erase(station1);
}

void Station::removeStation(int station) {
adjacencyList.erase(station);
for (auto& pair : adjacencyList) {
pair.second.erase(station);
}
}
void Station::addConnectionToStation(Station& station, unordered_map<int, Station> stations) {
cout << "Enter connections for station " << station.name;
string connection;
int choice = 1;
bool first = true;
do {
if (!first)
{
cout << "1. To add another connection.\n0. To stop.";
... (120 lines left)
Collapse
message.txt
6 KB
﻿

#include "Station.h"
#include "sqlite/sqlite3.h"
#include <winsqlite/winsqlite3.h>

Station::Station()
{
	
	totalIncome = 0;
	numOfSoldTickets = 0;
	numOfSubscriptions = 0;
	numOfPassengers = 0;
}

Station::Station(string n, int line)
{

	name = n;
	lineNum = line;
	totalIncome = 0;
	numOfSoldTickets = 0;
	numOfSubscriptions = 0;
	numOfPassengers = 0;

}
Station::Station(int idd, string namee, int inc, int tix, int passengers, string line, int subscriptions) {
	id = idd;
	name = namee;
	totalIncome = inc;
	numOfSoldTickets = tix;
	numOfPassengers = passengers;
	linenum2 = line;
	numOfSubscriptions = subscriptions;
}

int Station::getID() const
{
	return id;
}

string Station::getName() const
{
	return name;
}

int Station::getLineNum() const
{
	return lineNum;
}

pair<bool, Station> Station::findStationByName(string name, unordered_map<int, Station> stations)
{
	Station station;
	bool found = false;
	for (auto it = stations.begin(); it != stations.end(); it++)
	{
		if ((*it).second.name == name)
		{
			station = (*it).second;
			found = true;
			break;
		}
	}
	return pair<bool, Station>(found, station);
}

void Station::rideStarted(string type)
{
	if (type == "Cash Wallet")
		numOfSoldTickets++;

	numOfPassengers++;
}


void Station::addConnection(int station1, int station2) {
	adjacencyList[station1].insert(station2);
	adjacencyList[station2].insert(station1);
}

void Station::removeConnection(int station1, int station2) {
	adjacencyList[station1].erase(station2);
	adjacencyList[station2].erase(station1);
}

void Station::removeStation(int station) {
	adjacencyList.erase(station);
	for (auto& pair : adjacencyList) {
		pair.second.erase(station);
	}
}
void Station::addConnectionToStation(Station& station, unordered_map<int, Station> stations) {
	cout << "Enter connections for station " << station.name;
	string connection;
	int choice = 1;
	bool first = true;
	do {
		if (!first)
		{
			cout << "1. To add another connection.\n0. To stop.";
			cin >> choice;
		}
		else first = false;
		pair<bool, Station> response;

		switch (choice)
		{
		case 0:
			break;
		case 1:
			cout << "Enter the station you want connect with: ";
			cin >> connection;
			response = findStationByName(connection, stations);

			if (response.first)
				addConnection(station.id, response.second.id);
			else
				cout << "There is no station named " + connection + " in our databse.";
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (choice != 0);
}

void Station::addStation(unordered_map<int, Station> stations)
{
	string name;
	int line;
	cout << "Enter station name: ";
	cin >> name;
	cout << "Enter station line number: ";
	cin >> line;

	Station station(name, line);
	addConnectionToStation(station, stations);

	//Add it to the list
	stations[id] = station;
}

void Station::displayDetails(string type)
{
	cout << "Station details:\n";
	cout << "name: " + name;
	cout << "\tline number: " + lineNum;
	if (type == "admin")
	{
		cout << "\ttotal income: " + totalIncome;
		cout << "\nnumber of sold tickets: " + numOfSoldTickets;
		cout << "\tnumber of subscriptions: " + numOfSubscriptions;
		cout << "\tnumber of passengers: " + numOfPassengers;
	}
}
vector<Station> Station::RetrieveStationsFromDatabase()
{
	vector<Station> Stations;
	sqlite3* db;
	int rc = sqlite3_open("mydb_1 (1).db", &db);

	if (rc != SQLITE_OK)
	{
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return Stations;
	}


	const char* sql = "SELECT * FROM Stations";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK)
	{
		cout << "Error preparing the SQL statement" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return Stations;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int station_id = sqlite3_column_int(stmt, 0);
		const char* station_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		int income = sqlite3_column_int(stmt, 2);
		int tickets = sqlite3_column_int(stmt, 3);
		int n_passengers = sqlite3_column_int(stmt, 4);
		const char* metroline = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		int n_subscribtions = sqlite3_column_int(stmt, 6);


		// Creating SubscriptionPlan objects and adding them to the vector
		Station s (station_id, station_name, income, tickets, n_passengers, metroline, n_subscribtions);
		Stations.push_back(s);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return Stations;
}
void Station::printDetails()  {
	cout << "Station ID: " << id << endl;
	cout << "Station Name: " << name << endl;
	cout << "Income: " << totalIncome << endl;
	cout << "Tickets: " << numOfSoldTickets << endl;
	cout << "Number of Passengers: " << numOfPassengers << endl;
	cout << "Metro Line: " << linenum2 << endl;
	cout << "Number of Subscriptions: " << numOfSubscriptions << endl;
	cout << endl;
}
int main() {
	Station w;
	vector <Station> q = w.RetrieveStationsFromDatabase();
	for (auto z : q) {
		z.printDetails();
	}
}
message.txt
6 KB
