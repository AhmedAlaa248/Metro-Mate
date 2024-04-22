#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>

#include "Station.h"

using namespace std;

class Ride
{
public:
	int id;
	string source, destination;
	int stationId;
	
	unordered_map<int, unordered_set<int>> adjacencyList;
	vector<vector<int>> allPaths;

public:
	Ride();
	Ride(int rideId, string src, string dest, int stationId);
	void dfs(int source, int destination, vector<int>& path, vector<bool>& visited);
	
	vector<vector<int>> findAllPaths(int source, int destination);
	void showPaths(unordered_map<int, Station> stations, Station &sourceStation, Station& destinationStation);

	void addRide(unordered_map<int, Station> stations);
};

