#include "Admin.h"
#include "Validator.h"
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

//user functions
/**
 * veiwUser:view user details by ID.
 * @param users Vector of User objects.
 * The function prompts for a user ID, searches for the user in the vector,
 * and prints their details if found
 * If the user ID is not found, it prompts to try again.
 */
void Admin::viewUser(vector<User>& users)
{
    bool userfound = false;

    // Empty Users Vector
    if (users.empty()) {
        cout << "No users available to view." << endl;
        return;
    }
    while (!userfound)
    {
        cout << "Enter the User ID you want to view it's details" << endl;
        int userID;
        cin >> userID;

        //Non-Numeric Input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric ID." << endl;
            continue;
        }

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

/**
 * deleteuser:Deletes a user by ID from a vector of User objects.
 * Prompts for user ID, removes if found, and displays status.
 */
void Admin::deleteUser(vector<User>& users) {
    // Display all users before deletion
    Admin::viewAllUsers(users);

    bool userFound = false;

    // Check if users vector is empty
    if (users.empty()) {
        cout << "No users available to delete." << endl;
        return;
    }

    while (!userFound) {
        cout << "Enter the User ID you want to delete: ";
        int userID;
        cin >> userID;

        // Handle non-numeric input for user ID
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric ID." << endl;
            continue;
        }

        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->id == userID) {
                // Delete user if ID is found
                users.erase(it);
                cout << "User deleted successfully." << endl;
                userFound = true;
                break;
            }
        }

        // Display message if user ID is not found
        if (!userFound) {
            cout << "User not found. Please try again." << endl;
        }
    }
}

/*
* viewall users through vector
*/
void Admin::viewAllUsers(vector<User>& users)
{
    //Empty Users Vector
    if (users.empty()) {
        cout << "No users available." << endl;
        return;
    }
    //non empty
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

/**
 * editUser: Function to edit user details by ID.
 * @param: user vector
 * Updates the user's information if the ID is found in the users vector.
 */
void Admin::editUser(vector<User>& users) {
    // Display all users before editing
    viewAllUsers(users);

    int userID, newBalance = 0;
    bool userFound = false, goodPassword = false;
    Validator validator;
    string newName, newEmail, newPassword, newUsername;

    while (true) {
        cout << "Enter the User ID you want to edit: ";
        cin >> userID;

        // Handle non-numeric input for user ID
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric ID." << endl;
            continue;
        }

        // Check if the user ID exists
        userFound = false;
        for (const auto& user : users) {
            if (user.id == userID) {
                userFound = true;
                break;
            }
        }

        // If user ID doesn't exist, prompt to re-enter
        if (!userFound) {
            cout << "User not found. Please try again." << endl;
            continue;
        }

        // If user ID exists, proceed with editing
        cout << "Enter the new name: ";
        cin >> newName;

        // Validate new username
        while (true) {
            cout << "Enter your username: ";
            cin >> newUsername;

            if (!validator.UsedUserName(newUsername)) {
                break;
            }
            else {
                cout << "Username already taken, please try again\n";
            }
        }

        // Validate new email
        while (true) {
            cout << "Enter your email: ";
            cin >> newEmail;

            if (validator.isValidEmailAddress(newEmail)) {
                break;
            }
            else {
                cout << "Invalid email, please try again\n";
            }
        }

        // Validate new password
        while (true) {
            cout << "Enter new password: ";
            cin >> newPassword;

            cout << "Confirm password: ";
            string confirmPassword;
            cin >> confirmPassword;

            if (newPassword != confirmPassword) {
                cout << "Passwords do not match!\n";
                continue;
            }

            if (!validator.isStrongPassword(newPassword)) {
                cout << "Password is weak. Please choose a stronger one.\n";
                continue;
            }

            goodPassword = true;
            break;
        }

        cout << "Enter the new balance: ";
        cin >> newBalance;

        // Update user information if ID is found
        for (auto& user : users) {
            if (user.id == userID) {
                user.name = newName;
                user.userName = newUsername;
                user.email = newEmail;
                user.password = newPassword;
                user.balance = newBalance;

                cout << "User updated successfully." << endl;
                break;
            }
        }

        // Prompt to continue or exit editing
        char choice;
        cout << "Do you want to edit another user? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
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


void Admin::addStation(vector<Station>& allStations) {
    string name;
    string metroLine;
    string linkedStations;
    Station s;
    int newStationID = allStations.size() + 1;

    // Get input from admin for name and metro line
    cout << "Enter station name: ";
    cin >> name;
    cout << "Enter metro line: ";
    cin >> metroLine;


    vector<string> neighbors;
    char choice;
    do {
        string neighbor;
        cout << "Enter neighboring station: ";
        cin >> neighbor;
        neighbors.push_back(neighbor);
        cout << "Do you want to add another neighboring station? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    for (const string& neighborName : neighbors) {
        for (auto& station : allStations) {
            if (station.name == neighborName) {
                linkedStations += to_string(station.id) + ",";
                station.link += to_string(newStationID) + ",";
                break;
            }
        }
    }
    for (const string& neighbor : neighbors) {
        s.addConnection(name, neighbor);
    }
    Station newStation(newStationID, name, 0, 0, 0, metroLine, 0, linkedStations);
    allStations.push_back(newStation);

    cout << "Station Successfully added\n";

}

void Admin::deleteStation(vector<Station>& stations)
{
    Admin::viewAllStations(stations);
    bool stationFound = false;
    while (!stationFound)
    {
        cout << "Enter the Station ID you want to delete" << endl;
        int stId;
        cin >> stId;

        auto it = find_if(stations.begin(), stations.end(), [stId](const Station& s) {
            return s.id == stId;
            });

        if (it != stations.end()) {
            string deletedStationId = to_string(stId);
            for (auto& station : stations) {
                if (station.id != stId) {
                    size_t pos = station.link.find(deletedStationId);
                    if (pos != string::npos) {
                        station.link.erase(pos, deletedStationId.length() + 1); 
                    }
                }
            }

            // Erase the station from the list
            stations.erase(it);

            cout << "Station deleted successfully." << endl;
            stationFound = true;
        }
        else {
            cout << "Station not found." << endl;
        }
    }
}

void Admin::viewAllStations(vector<Station> stations)
{
    for (auto& station : stations)
    {
        cout << "Station Details:" << endl;
        cout << "ID: " << station.id << endl;
        cout << "Name: " << station.name << endl;
        cout << "income: " << station.totalIncome << endl;
        cout << "Tickets: " << station.numOfSoldTickets << endl;
        cout << "Number Of Passengers: " << station.numOfPassengers << endl;
        cout << "Metro Line: " << station.lineNum << endl;
        cout << "Subscriptions Number: " << station.numOfSubscriptions << endl;
        cout << "connected Stations ID: " << station.link << endl;
        cout << "----------------------------------------------------------------------\n";
    }
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

void Admin::viewAllRideLogs(vector<Ride>& rides)
{


    for (const auto& ride : rides) {
        cout << "Ride Details:" << endl;
        cout << "ID: " << ride.id << endl;
        cout << "Source: " << ride.source << endl;
        cout << "Destination: " << ride.destination << endl;
        cout << "Station ID: " << ride.stationId << endl;
        cout << "Date: " << ride.ridedate << endl;
        cout << "User ID: " << ride.user_id << endl;
        cout << "----------------------------------------------";
        cout << endl; 
    }

    
}

void Admin::viewStation(vector<Station>& stations) {
    bool stationFound = false;

    if (stations.empty()) {
        cout << "No stations available to view." << endl;
        return;
    }

    while (!stationFound) {
        cout << "Enter the Station ID you want to view its details: ";
        int stationID;
        cin >> stationID;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric ID." << endl;
            continue;
        }

        for (const auto& station : stations) {
            if (station.id == stationID) {
                cout << "Station Details:" << endl;
                cout << "ID: " << station.id << endl;
                cout << "Name: " << station.name << endl;
                cout << "Line Number: " << station.lineNum << endl;
                cout << "Link: " << station.link << endl;
                cout << "Total Income: " << station.totalIncome << endl;
                cout << "Number of Sold Tickets: " << station.numOfSoldTickets << endl;
                cout << "Number of Subscriptions: " << station.numOfSubscriptions << endl;
                cout << "Number of Passengers: " << station.numOfPassengers << endl;
                stationFound = true;
                break;
            }
        }

        if (!stationFound)
            cout << "Station not found. Please try again." << endl;
    }
}


