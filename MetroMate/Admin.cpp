#include "Admin.h"
#include<iostream>
#include"sqlite/sqlite3.h"
#include "map"
#include "set"
#include <string>
#include "iomanip"
#include "algorithm"
#include "sstream"
using namespace std;

Admin::Admin()
{
}
void Admin::viewUser( vector<User>& users)
{
    bool userfound = false;
    while (!userfound)
    {
      
        cout << "Enter the User ID you want to view it's details" << endl;
        int userID;
        cin >> userID;
        for (const auto& user : users)
        {
            if (user.id == userID)
            {
                cout << "User Details:" << endl;
                cout << "ID: " << user.id << endl;
                cout << "Name: " << user.name << endl;
                cout << "Username: " << user.userName << endl;
                cout << "Email: " << user.email << endl;
                cout << "Password: " << user.password << endl;
                cout << "Balance: " << user.balance << endl;
                cout << "Subscription ID: " << user.subId << endl;
                cout << "Ride ID: " << user.rideId << endl;
                userfound = true;
                break;
            }
        }
        if (!userfound)
            cout << "User not found please try again." << endl;
    }

}
void Admin::deleteUser( vector<User>& users)
{
    Admin::viewAllUsers(users);
    bool userfound = false;
    while (!userfound)
    {
        cout << "Enter the User ID you want to delete" << endl;
        int userID;
        cin >> userID;


        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->id == userID) {
                users.erase(it);
                cout << "User deleted successfully." << endl;
                userfound = true;
                break;
            }
        }
        if (!userfound)
            cout << "User not found." << endl;
    }

}
void Admin::viewAllUsers( vector<User>& users)
{
    for (const auto& user : users)
    {
        cout << "User Details:" << endl;
        cout << "ID: " << user.id << endl;
        cout << "Name: " << user.name << endl;
        cout << "Username: " << user.userName << endl;
        cout << "Email: " << user.email << endl;
        cout << "Password: " << user.password << endl;
        cout << "Balance: " << user.balance << endl;
        cout << "Subscription ID: " << user.subId << endl;
        cout << "Ride ID: " << user.rideId << endl;
    }
}
void Admin::editUser(vector<User>& users) {
    viewAllUsers(users);
    int userID;
    bool userFound = false;

    while (!userFound) {
        cout << "Enter the User ID you want to edit " << endl;
        cin >> userID;
        string newName, newEmail, newPassword, newUsername;
        int newBalance = 0;
        cout << "Enter the new name: ";
        cin >> newName;
        cout << "Enter the new Username: ";
        cin >> newUsername;
        cout << "Enter the new email: ";
        cin >> newEmail;
        cout << "Enter the new password: ";
        cin >> newPassword;
        cout << "Enter the new balance: ";
        cin >> newBalance;


        for (auto& user : users) {
            if (user.id == userID) {
                user.name = newName;
                user.userName = newUsername;
                user.email = newEmail;
                user.password = newPassword;
                user.balance = newBalance;

                cout << "User updated successfully." << endl;
                userFound = true;
                break;
            }
        }

        if (!userFound) {
            cout << "User not found. Please try again." << endl;
        }
    }
}

void Admin::FareManagement(vector<SubscriptionPlan>& plans) {


    cout << "--------------------Available programs To Adjust Fare--------------------" << endl;
    int count = 1;
    map<int, string> planTypeMap;
    set<int> uniqueTypes;

    for (const auto& plan : plans) {
        if (uniqueTypes.find(plan.getType()) == uniqueTypes.end()) {
            count++; cout << "- " << plan.getType() << "- " << plan.getplan_name() << endl;
            planTypeMap[count - 1] = plan.getplan_name();
            uniqueTypes.insert(plan.getType());
        }
    }

    int selectedType;
    bool validInput = false;
    while (!validInput) {
        cout << "Please Select Number of Desired Program Type: ";
        cin >> selectedType;

        if (uniqueTypes.find(selectedType) != uniqueTypes.end()) {
            validInput = true;
        }
        else {
            cout << "Invalid input. Please enter a valid program type number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "--------------------Stages for Selected Program Type " << selectedType << "--------------------" << endl;

    for (const auto& plan : plans) {
        if (plan.getType() == selectedType) {
            cout << "ID : " << plan.getplan_id() << "   ";
            cout << "Stage: " << plan.getstages() << "    ";
            cout << "Price: " << plan.getPrice() << endl;
            cout << "--------------------------------------------" << endl;

        }
    }


    int stageId;
    string typee;
    int durationn, remainingrides;
    bool validId = false;
    while (!validId) {
        cout << "Please Enter Stage ID to Adjust Fare :) \n";
        cin >> stageId;

        for (auto& plan : plans) {
            if (plan.getplan_id() == stageId && plan.getType() == selectedType) {
                validId = true;
                int fare;
                cout << "Enter the New Fare :)) \n";
                cin >> fare;
                plan.setPrice(fare);
                cout << "Fare Adjusted Successfully ! \n";
                break;
            }
        }

        if (!validId) {
            cout << "Invalid input. Please enter a valid plan ID for the selected program type." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Admin::StationManagement(vector <Station>& q, vector<Subscription>& w) {
    cout << "Here's the stations in the system :)\n";

    //auto maxStation = max_element(q.begin(), q.end(),
    //    [](const Station& a, const Station& b) {
    //         Split the line numbers by comma and find the maximum
    //        vector<int> lineNumsA, lineNumsB;

    //         Create stringstream from the line number string
    //        stringstream ssA(a.getLineNum());
    //        stringstream ssB(b.getLineNum());

    //         Temporary variable to hold each individual line number
    //        int num;

    //         Extract line numbers from stringstream
    //        while (ssA >> num) {
    //            lineNumsA.push_back(num);
    //            if (ssA.peek() == ',') ssA.ignore();
    //        }

    //        while (ssB >> num) {
    //            lineNumsB.push_back(num);
    //            if (ssB.peek() == ',') ssB.ignore();
    //        }

    //         Find the maximum line number
    //        int maxLineNumA = *max_element(lineNumsA.begin(), lineNumsA.end());
    //        int maxLineNumB = *max_element(lineNumsB.begin(), lineNumsB.end());

    //        return maxLineNumA < maxLineNumB;
    //    });

    //int maxLineNumber = stoi(maxStation->getLineNum());
    //cout << "Max Line Number: " << maxLineNumber << endl;

    //for (size_t i = 1; i <=maxLineNumber  ; i++)
    //{

    //    Station::printDetailed(to_string(i), q);
    //    
    //}
    //for (auto z: q)
    //{
    //    cout << z.getID() << "-> " << z.getName() << endl;
    //}

    //unordered_map<int, std::vector<Station>> stationsByMetroLine;

    //for (const auto& station : q) {
    //    stationsByMetroLine[station.getLineNum()].push_back(station);
    //}

    //// Print stations by metro line
    //for ( auto& pair : stationsByMetroLine) {
    //    int metroLine = pair.first;
    //    vector<Station>& stationsOnLine = pair.second;

    //    std::cout << "Metro Line " << metroLine << " Stations:" << std::endl;

    //    for ( auto& station : stationsOnLine) {
    //        cout << "Station ID: " << station.getID() << ", Name: " << station.getName() << std::endl;
    //       
    //    }

    //    cout << endl;
    //}
    cout << "How do you want to view the Stations data? \n ";



}

int getMaxType(vector<SubscriptionPlan>& subplans) {
    if (subplans.empty()) {

        return -1; // 
    }

    int maxType = subplans[0].getType();


    for (const auto& subplan : subplans) {
        if (subplan.getType() > maxType) {
            maxType = subplan.getType();
        }
    }
    return maxType;
}

void Admin::addSubscriptionPlan(vector<SubscriptionPlan>& SubscriptionPlans)
{
    int newPLanid = SubscriptionPlans.size() + 1;
    vector<SubscriptionPlan> subplans = SubscriptionPlan::RetrieveSubplansFromDatabase();
    cout << "1-Existing plan type\n2-New plan type" << endl;
    int  duration, price, trips, stages, type, numStations, choice, selectedType, count = 1;
    cin >> choice;
    string plan_name;
    map<int, string> planTypeMap;
    set<int> uniqueTypes;
    bool validInput = false;

    switch (choice)
    {
    case 1:
        cout << "--------------------Available programs--------------------" << endl;

        for (const auto& plan : subplans) {
            if (uniqueTypes.find(plan.getType()) == uniqueTypes.end()) {
                count++; cout << "- " << plan.getType() << "- " << plan.getplan_name() << endl;
                planTypeMap[count - 1] = plan.getplan_name();
                uniqueTypes.insert(plan.getType());
            }
        }

        while (!validInput) {
            cout << "Please Select Number of Desired Program Type: ";
            cin >> selectedType;

            if (uniqueTypes.find(selectedType) != uniqueTypes.end()) {
                validInput = true;
            }
            else {
                cout << "Invalid input. Please enter a valid program type number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cout << "Enter the Subscription Plan Duration: ";
        cin >> duration;

        cout << "Enter the Subscription Plan Price: ";
        cin >> price;

        cout << "Enter the Number of Trips: ";
        cin >> trips;

        cout << "Enter the Number of Stages: ";
        cin >> stages;


        cout << "Enter the Number of Stations: ";
        cin >> numStations;

        if (selectedType == 1)
        {
            type = 1;
            plan_name = "Student Card";
        }

        else if (selectedType == 2)
        {
            type = 2;
            plan_name = "Public Card";
        }
        else if (selectedType == 3)
        {
            type = 3;
            plan_name = "Cash Wallet Cards";
        }


        break;
    case 2:
        cout << "Enter the Subscription Plan Name: ";
        cin >> plan_name;

        cout << "Enter the Subscription Plan Duration: ";
        cin >> duration;

        cout << "Enter the Subscription Plan Price: ";
        cin >> price;

        cout << "Enter the Number of Trips: ";
        cin >> trips;

        cout << "Enter the Number of Stages: ";
        cin >> stages;

        cout << "Enter the Number of Stations: ";
        cin >> numStations;

        type = getMaxType(subplans) + 1;

        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }

    SubscriptionPlan as(newPLanid, plan_name, duration, price, trips, stages, type, numStations);

    SubscriptionPlans.push_back(as);

    cout << "Subscription Plan added successfully." << std::endl;
}

void Admin::deleteSubscriptionPlan(vector<SubscriptionPlan>& subscriptionPlan)
{

    bool subplanFound = false;
    while (!subplanFound)
    {
        cout << "Enter the SubscriptionPlan ID you want to delete" << endl;
        int subID;
        cin >> subID;


        for (auto it = subscriptionPlan.begin(); it != subscriptionPlan.end(); ++it)
        {
            if (it->plan_id == subID)
            {
                subscriptionPlan.erase(it);
                cout << "SubscriptionPlan deleted successfully." << endl;
                subplanFound = true;
                break;
            }
        }
        if (!subplanFound)
            cout << "SubscriptionPlan not found." << endl;
    }

}

void Admin::editSubscriptionPlan(vector<SubscriptionPlan>& SubscriptionPlan) {
    int subID;
    bool subplanFound = false;

    while (!subplanFound) {
        cout << "Enter the Subscribtion ID you want to edit " << endl;
        cin >> subID;
        int newPrice, newDuration, newNumstations, newTrips;
        cout << "Enter the new price: ";
        cin >> newPrice;
        cout << "Enter the new duration: ";
        cin >> newDuration;
        cout << "Enter the new numStations: ";
        cin >> newNumstations;
        cout << "Enter the new trips: ";
        cin >> newTrips;


        for (auto& subplans : SubscriptionPlan) {
            if (subplans.plan_id == subID) {
                subplans.price = newPrice;
                subplans.duration = newDuration;
                subplans.numStations = newNumstations;
                subplans.trips = newTrips;

                cout << "User updated successfully." << endl;
                subplanFound = true;
                break;
            }
        }

        if (!subplanFound) {
            cout << "User not found. Please try again." << endl;
        }
    }
}

void Admin::viewAllSubscriptionPlans(vector<SubscriptionPlan>& SubscriptionPlan)
{
    for (auto& subscriptionPlan : SubscriptionPlan)
    {
        cout << "SubscriptionPlan Details:" << endl;
        cout << "Type: " << subscriptionPlan.type << endl;
        cout << "Price: " << subscriptionPlan.price << endl;
        cout << "Duration: " << subscriptionPlan.duration << endl;
        cout << "NumStations: " << subscriptionPlan.numStations << endl;
        cout << "Plan_name: " << subscriptionPlan.plan_name << endl;
        cout << "Trips: " << subscriptionPlan.trips << endl;
        cout << "Stages: " << subscriptionPlan.stages << endl;
        cout << "Plan_id: " << subscriptionPlan.plan_id << endl;
    }

}

void Admin::AddStation(string station)
{
    Station stations;
    stations.addStation(station);
}

void Admin::deleteStation(string station)
{
    Station stations;
    stations.removeStation(station);
}

void Admin::editStation(vector<Station>& stations)
{
    int stationID;
    bool stationfound = false;
    long newtotalIncome, newnumOfSoldTickets, newnumOfSubscriptions;
    long long newnumOfPassengers;



    while (!stationfound) {
        cout << "Enter the Station ID you want to edit " << endl;
        cin >> stationID;

        for (auto& Station : stations)
        {
            if (Station.id == stationID)
            {
                cout << "Station Details:" << endl;
                cout << "ID: " << Station.id << endl;
                cout << "totalIncome: " << Station.totalIncome << endl;
                cout << "numOfSoldTickets: " << Station.numOfSoldTickets << endl;
                cout << "numOfSubscriptions: " << Station.numOfSubscriptions << endl;
                cout << "numOfPassengers: " << Station.numOfPassengers << endl;
                stationfound = true;
                break;
            }
        }


        cout << "Enter the new total income: ";
        cin >> newtotalIncome;

        cout << "Enter the new number of sold tickets : ";
        cin >> newnumOfSoldTickets;


        cout << "Enter the new number of subscriptions: ";
        cin >> newnumOfSubscriptions;


        cout << "Enter the new number of passengers: ";
        cin >> newnumOfPassengers;

        for (auto& Station : stations) {
            if (Station.id == stationID) {
                Station.totalIncome = newtotalIncome;
                Station.numOfSoldTickets = newnumOfSoldTickets;
                Station.numOfSubscriptions = newnumOfSubscriptions;
                Station.numOfPassengers = newnumOfPassengers;

                cout << "Station updated successfully." << endl;
                stationfound = true;
                break;
            }
        }

        if (!stationfound) {
            cout << "Station ID not found. Please try again." << endl;
        }
    }
}


//int main() {
//    Station station;
//    Admin admin;
//    User user;
//    SubscriptionPlan subs;
//    vector<User> users= User::RetrieveUsersFromDatabase();
//    vector<Station>stations = station.RetrieveStationsFromDatabase();
//    vector<SubscriptionPlan> subplans = subs.RetrieveSubplansFromDatabase();
//    bool infoUpdated = true;
//
//    admin.FareManagement(subplans);
//    admin.viewAllSubscriptionPlans(subplans);
//    subs.saveSubplanToDatabase(subplans);
//}
