#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "SubscriptionPlan.h"

class Subscription
{
    int ID;
    string Type;
    string Sub_datee;
    string End_datee;
    int remaining_rides ;
    int user_idd;
    int sub_idd;
    int stageNumber;
     SubscriptionPlan subPlan;
public:
    Subscription();
    Subscription(int id, string type, string subDate,
        string endDate, int remainingRides, int userId,
        int subId);
    int stages();
    void printDetails();
    

};

