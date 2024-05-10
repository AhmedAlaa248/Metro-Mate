#pragma once
#include <unordered_map>
#include <algorithm>

#include "GlobalData.h"

using namespace std;

class Ride
{
public:
public:
	int id;
	string source, destination;
	int stationId;
	vector<vector<int>> allPaths;

public:
	Ride();
	Ride(int rideId, string src, string dest, int stationId);

	void dfs(int source, int destination, vector<int>& path, vector<bool>& visited);
	vector<vector<int>> findAllPaths(int source, int destination);
	void showPaths(Station& sourceStation, Station& destinationStation);
	static void startTheAdjacency();
	void addRide();
};

