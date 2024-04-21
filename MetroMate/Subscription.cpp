#include "Subscription.h"
#include <iostream>
#include <string>
using namespace std;

Subscription::Subscription()
{
}

Subscription::Subscription(int id, string type, string subDate, string endDate, int remainingRides, int userId, int subId) {
    ID = id;
    Type = type;
    Sub_datee = subDate;
    End_datee = endDate;
    remaining_rides = remainingRides;
    user_idd = userId;
    sub_idd = subId;
}

int Subscription::stages(int numOfStations)
{
    if (numOfStations >= 1 && numOfStations <= 9) {
        stageNumber = 1;
    }
    if (numOfStations >= 10 && numOfStations <= 16) {
        stageNumber = 2;
    }
    if (numOfStations >= 17 && numOfStations <= 23) {
        stageNumber = 3;
    }
    if (numOfStations > 23) {
        stageNumber = 4;
    }
    return stageNumber;
}

void Subscription::printDetails(int type, int duration)
{
    switch (type)
    {
    case 1:
        switch (stages(1))
        {
        case 1:
            cout << "you are on stage 1" << endl;
            cout << "your remaining rides :" << remaining_rides << endl;
            break;
        case 2:
            cout << "you are on stage 2" << endl;
            cout << "your remaining rides :" << remaining_rides << endl;
            break;
        case 3:
            cout << "you are on stage 3" << endl;
            cout << "your remaining rides :" << remaining_rides << endl;
            break;
        case 4:
            cout << "you are on stage 4" << endl;
            cout << "your remaining rides :" << remaining_rides << endl;
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (duration)
        {
        case 1:
            switch (stageNumber)
            {
            case 1:
                cout << "you are on stage 1" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            case 2:
                cout << "you are on stage 2" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            case 3:
                cout << "you are on stage 3" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            case 4:
                cout << "you are on stage 4" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            default:
                break;
            }
            break;
        case 12:
            switch (stageNumber)
            {
            case 1:
                cout << "you are on stage 1" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            case 2:
                cout << "you are on stage 2" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            case 3:
                cout << "you are on stage 3" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            case 4:
                cout << "you are on stage 4" << endl;
                cout << "your remaining rides :" << remaining_rides << endl;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

}


