#pragma once
#include<iostream>
#include <string>
#include <unordered_set>
#include <optional>
#include <utility>

using namespace std;

class Station
{
	int id;
	string name;
	string lineNum;

public:
	static int nextId;	//auto increament
	long totalIncome; //increased when add subscription
	long numOfSoldTickets;
	long numOfSubscriptions; //increased when add subscription
	long long numOfPassengers;

	unordered_set<int> connections;

	Station();
	Station(string n, int line);
	Station(int idd, string namee, int inc, int tix, int passengers, string line, int subscriptions, string link);

	//Getters
	int getID() const;
	string getName() const;
	string getLineNum() const;

	static pair<bool, Station> findStationByName(string name);
	void rideStarted(string type);
	void addConnection(int con);
	void removeConnection(int con);
	void addConnectionToStation();
	static void removeStation();
	static void addStation();
	void displayDetails(string type);
};
