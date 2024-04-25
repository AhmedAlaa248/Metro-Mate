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
