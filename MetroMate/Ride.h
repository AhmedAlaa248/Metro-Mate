#pragma once
#include <string>
#include <iostream>
using namespace std;
class Ride
{
public:
	int id;
	string source, destination;
	int station_id;
public:
	Ride();
	Ride(int rideId, string src, string dest, int stationId)
		: id(rideId), source(src), destination(dest), station_id(stationId) {}
};

