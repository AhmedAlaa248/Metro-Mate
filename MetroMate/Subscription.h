#pragma once
using namespace std;
#include <iostream>
#include <string>
class Subscription
{
    int ID;
    string Type;
    string Sub_datee;
    string End_datee;
    int remaining_rides;
    int user_idd;
    int sub_idd;
public:
    Subscription(int id, string type, string subDate,
        string endDate, int remainingRides, int userId,
        int subId);
};
