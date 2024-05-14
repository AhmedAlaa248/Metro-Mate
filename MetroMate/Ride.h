#pragma once
#include <unordered_map>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

class Ride
{

public:
    int id;
    string source, destination;
    int stationId;
    string ridedate;
    int user_id;
    int fare;
    Ride();
    Ride(int rideId, string src, string dest, int stationId, string date, int usr_id, int faree);
    vector<Ride> RetrieveRidesFromDatabase();
    vector<Ride> GetRidesForUser(int);
    void saveRideToDatabase(vector<Ride>& rides);
};