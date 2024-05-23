#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <vector>
#include <ctime>
#include <iomanip>
#include "User.h"
#include"Station.h"
#include <chrono>

class Admin {

public:
    Admin();
    bool login(const std::string& name, const std::string& pass);
    void viewUser(vector<User>& users);
    void deleteUser(vector<User>& users);
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

    void saveStationToDatabase(vector<Station>&);

    void viewAllRideLogs(vector<Ride>& rides);

    void viewStation(vector<Station>& stations);



    // Other functions
    int getIntervalCode(const string& interval);
    int compareDates(const tm& date1, const tm& date2);
    tm convertStringToDate(const string& dateString);
    tm addMonthsToDate(const tm& date, int monthsToAdd);
    tm addYearsToDate(const tm& date, int yearsToAdd);

    void displayDetailsForDay(const vector<Ride>& rides, const string& stationName, const tm& date);
    void displayDetailsForWeek(const vector<Ride>& rides, const string& stationName, const tm& startDateOfWeek, const tm& endDateOfWeek);
    void displayDetailsForMonth(const vector<Ride>& rides, const string& stationName, const tm& startDateOfMonth, const tm& endDateOfMonth);
    void displayDetailsForYear(const vector<Ride>& rides, const string& stationName, const tm& startDateOfYear, const tm& endDateOfYear);
    void viewStationByInterval(vector<Station>& stations, vector<Ride>& rides);

};