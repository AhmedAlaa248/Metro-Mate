#include "Subscription.h"

Subscription::Subscription() {}

Subscription::Subscription(int id, std::string type, std::string subDate, std::string endDate, int remainingRides, int userId, int subId) {
    ID = id;
    Type = type;
    Sub_datee = subDate;
    End_datee = endDate;
    remaining_rides = remainingRides;
    user_idd = userId;
    sub_idd = subId;
}
Subscription::Subscription(int id, std::string type, std::string subDate, std::string endDate, int remainingRides, int userId, int subId, string sourceStation, string finalStation) {
    ID = id;
    Type = type;
    Sub_datee = subDate;
    End_datee = endDate;
    remaining_rides = remainingRides;
    user_idd = userId;
    sub_idd = subId;
    source_station = sourceStation; // Assign the value to the new attribute
    final_station = finalStation; // Assign the value to the new attribute
}
void Subscription::saveSubscriptionToDatabase() {
    sqlite3* db;
    char* errorMessage = nullptr;

    // Open the database
    int rc = sqlite3_open("mydb_1 (1).db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // SQL statement to insert subscription data
    string sql = "INSERT INTO Subscription (Type, Sub_date, End_date, remaining_rides, user_idd, sub_idd, [SourceStation ], FinalStation) "
        "VALUES ('" + Type + "', '" + Sub_datee + "', '" + End_datee + "', " + to_string(remaining_rides) + ", " + to_string(user_idd) + ", " + to_string(sub_idd) + ", '" + source_station + "', '" + final_station + "')";

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
    else {
        cout << "Subscription data saved to the database." << endl;
    }

    // Close the database
    sqlite3_close(db);
}

vector<Subscription> Subscription::Subscriptions()
{
    vector<Subscription> subscriptionList;
    sqlite3* db;
    int rc = sqlite3_open("mydb_1_1.db", &db);

    if (rc != SQLITE_OK)
    {
        // Error opening the database
        cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return subscriptionList;
    }

    const char* sql = "SELECT * FROM subscription";

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cout << "Error preparing the SQL statement" << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return subscriptionList;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int ID = sqlite3_column_int(stmt, 0);
        const char* Type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* Sub_datee = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* End_datee = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int remaining_rides = sqlite3_column_int(stmt, 4);
        int user_idd = sqlite3_column_int(stmt, 5);
        int sub_idd = sqlite3_column_int(stmt, 6);
        const char* source_station = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)); // Assuming source station is at column 7
        const char* final_station = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)); // Assuming final station is at column 8

        // Creating Subscription objects and adding them to the vector
        Subscription subscription(ID, Type, Sub_datee, End_datee, remaining_rides, user_idd, sub_idd, string(source_station), string(final_station));
        subscriptionList.push_back(subscription);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return subscriptionList;
}

Subscription Subscription::getSubscriptionForUser(int userId) {
    Subscription subscription;

    // Your database connection code here
    sqlite3* db;
    int rc = sqlite3_open("mydb_1_1.db", &db);

    if (rc != SQLITE_OK) {
        cerr << "Error opening the database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return subscription;
    }

    // Prepare SQL statement
    string sql = "SELECT * FROM Subscription WHERE user_idd = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return subscription;
    }

    // Bind the user ID parameter
    sqlite3_bind_int(stmt, 1, userId);

    // Execute the statement and retrieve data
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        subscription.ID = sqlite3_column_int(stmt, 0);
        subscription.Type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        subscription.Sub_datee = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        subscription.End_datee = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        subscription.remaining_rides = sqlite3_column_int(stmt, 4);
        subscription.user_idd = sqlite3_column_int(stmt, 5);
        subscription.sub_idd = sqlite3_column_int(stmt, 6);
        subscription.source_station = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        subscription.final_station = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
    }

    // Finalize statement and close database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return subscription;
}

int Subscription::stages()
{
    int numOfStations = subPlan.getNumStations();
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

void Subscription::printDetails()
{
    switch (subPlan.getType())
    {
    case 1:
        switch (stages())
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
        switch (subPlan.getDuration())
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

void Subscription::printsubdetails(Subscription& z) {
    cout << "Subscription ID: " << z.ID << endl;
    cout << "User ID: " << z.user_idd << endl;
    cout << "Type: " << z.Type << endl;
    cout << "Subscription Date: " << z.Sub_datee << endl;
    cout << "End Date: " << z.End_datee << endl;
    cout << "Remaining Rides: " << z.remaining_rides << endl;
    cout << "Source Station: " << z.source_station << endl;
    cout << "Final Station: " << z.final_station << endl;


}
//int main()
//{
//
//    Subscription sub;
//    sub.printDetails();
//}