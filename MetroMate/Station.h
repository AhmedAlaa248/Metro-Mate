#pragma once
#include<iostream>
#include<vector>
#include <string>
#include <unordered_set>
#include <optional>
#include <utility>
#include <map>


using namespace std;

class Station
{
	

public:
	static int nextId;	//auto increament
	int id;
	string name;
	string lineNum;
	string link;
	long totalIncome; //increased when add subscription
	long numOfSoldTickets;
	long numOfSubscriptions; //increased when add subscription
	long long numOfPassengers;
	unordered_map<string, unordered_set<string>> adjacencyList;
	vector<vector<string>> allPaths;
	Station();
	Station(string n, int line);
	Station(int idd, string namee, int inc, int tix, int passengers, string line, int subscriptions, string link);
	string GetStationNameFromID(vector<Station>& stations, int id);
	int GetStationIdFromName(vector<Station>, string);	
	int getID() const;
	string getName() const;
	string getLineNum() const;
	int FindLengthOfSpecificPath(int);
	//static pair<bool, Station> findStationByName(string name);
    //void rideStarted(string type);
	//void addConnection(int con);
	//void removeConnection(int con);
	//void addConnectionToStation();
	//static void removeStation();
	//static void addStation();
	//void displayDetails(string type);
	//static string getNameById(int id);
	void saveStationToDatabase(vector<Station>& stations);
	vector<Station> RetrieveStationsFromDatabase();
	vector<vector<string>> findAllPaths(string, string);
	void addStation(string station);
	void removeConnection(string, string);
	void addConnection(string , string );
	void dfs(string, string, vector<string>&, map<string,bool>&);
	void removeStation(string station);
	void addToAdjacency(vector<Station>& stations);

};
