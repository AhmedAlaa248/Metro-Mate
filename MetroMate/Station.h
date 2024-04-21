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
public:
	static int nextId;	//auto increament
	int id;
	string name;
	int lineNum;
	long totalIncome; //increased when add subscription
	long numOfSoldTickets;
	long numOfSubscriptions; //increased when add subscription
	long long numOfPassengers;
	unordered_map<int, unordered_set<int>> adjacencyList;
	vector<vector<int>> allPaths;

	Station();
	Station(string n, int line);
	void rideStarted(string type);
	void addConnection(int station1, int station2);
	void removeConnection(int station1, int station2);
	void removeStation(int station);
	void addStationWithConnections(int station);
	void displayDetails(string type);

};
