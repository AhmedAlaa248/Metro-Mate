#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <vector>

#include "User.h"
#include"Station.h"

class Admin {
public:
    Admin();

    // Login function
    bool login(const std::string& name, const std::string& pass);

    // User management
    void viewUser( vector<User>& users);
    void deleteUser( vector<User>& users);
    void viewAllUsers(vector<User>& users);
    void editUser(vector<User>& users);
    void FareManagement(vector<SubscriptionPlan>&);
    void StationManagement(vector <Station>&, vector<Subscription>&);

    // Station management
    void addStation(vector<Station>& allStations);

    void addSubscriptionPlan(vector<SubscriptionPlan>& SubscriptionPlans);

    void deleteSubscriptionPlan(vector<SubscriptionPlan>& subscriptionPlan);
    
    void editSubscriptionPlan(vector<SubscriptionPlan>& SubscriptionPlan);

    void viewAllSubscriptionPlans(vector<SubscriptionPlan>& SubscriptionPlan);

    void deleteStation(vector<Station>& stations);
    void editStation(vector<Station>& stations);
    void viewAllStations(vector<Station> stations);

    static void saveStationToDatabase(vector<Station>& Stations);

    void viewAllRideLogs(vector<Ride>& rides);

};
