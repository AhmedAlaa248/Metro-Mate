#include "Subscription.h"
#include <iostream>
#include <string>
using namespace std;

Subscription::Subscription(int id, string type, string subDate, string endDate, int remainingRides, int userId, int subId) {
    ID = id;
    Type = type;
    Sub_datee = subDate;
    End_datee = endDate;
    remaining_rides = remainingRides;
    user_idd = userId;
    sub_idd = subId;
}

