#pragma once
#include <iostream>
#include <string>
#include "SubscriptionPlan.h"
#include <vector> 
#include<winsqlite/winsqlite3.h>

class Subscription {
public:
    int ID;
    string Type;
    string Sub_datee;
    string End_datee;
    int remaining_rides;
    int user_idd;
    int sub_idd;
    int stageNumber;
    int path;
    string source_station; // New field
    string final_station; // New field
    SubscriptionPlan subPlan;
    Subscription();
    Subscription(int id, std::string type, std::string subDate, std::string endDate, int remainingRides, int userId, int subId);
    Subscription(int, string, string, string, int, int, int, string, string,int);
    Subscription getSubscriptionForUser(int);
    vector <string> stationofpath(vector<vector<string>>, int);
    vector<string>pathchoices;
    int stages();
    void saveSubscriptionToDatabase();
    void printDetails();
    vector<Subscription>RetrieveSubscriptionFromDatabase();
    void static printsubdetails(Subscription&);
};
