#pragma once
#include <iostream>
#include <string>

using namespace std;

class Station
{
public:
	static int nextId;	//auto increament
	int id;
	string name;
	int lineNum;
	long totalIncome; //increased when add subscription
	long numOfSoldTickets;
	long numOfSubscriptions; //increased when add subscription
	long long numOfPassengers;

	Station();
	Station(string n, int line);
	void rideStarted(string type);
	void addConnection();
	void displaYDetails(string type);

};

