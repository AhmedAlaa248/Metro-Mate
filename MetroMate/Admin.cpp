#include "Admin.h"
#include<iostream>
#include"sqlite/sqlite3.h"
#include "GlobalData.h"

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
void Admin::deleteUser( vector<User>& users, bool& infoUpdated)
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
                infoUpdated = true;
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

void Admin::addStation()
{
    Station::addStation();
}

void Admin::deleteStation()
{
    Station::removeStation();
}
void Admin::viewAllStations()
{
    for (auto it = GlobalData::stations.begin(); it != GlobalData::stations.end(); it++) {
        if (it->second.getName() == "")
        {
            GlobalData::stations.erase(it->second.getID());
            continue;
        }

        it->second.displayDetails("admin");

    }
}
void Admin::viewStationDetails()
{
    cout << "Enter station name:\n";
    string name;
    cin >> name;
    pair<bool, Station> response = Station::findStationByName(name);
    if (response.first)
        response.second.displayDetails("admin");
    
}
//int main() {
//    vector<User> users= User::RetrieveUsersFromDatabase();
//    Admin admin;
//
//    // Test deleteUser function
//    admin.viewAllUsers(users);
//    cout << "Before deleting a user:" << endl;
//    admin.editUser(users);
//    cout << "After editing a user:" << endl;
//    admin.viewAllUsers(users);
//
//    return 0;
//}
