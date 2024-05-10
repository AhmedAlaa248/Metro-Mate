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
    void deleteUser( vector<User>& users, bool& infoUpdated);
    void viewAllUsers(vector<User>& users);
    void editUser(vector<User>& users);

    // Station management
    void addStation();
    void deleteStation();
    //void editStation(int stationID, Station updatedStation);
    void viewAllStations();
    void viewStationDetails();

};
