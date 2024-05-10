#include "Ride.h"

#define adjacencyList GlobalData::adjacencyList
#define map GlobalData::stations

Ride::Ride()
{
}

Ride::Ride(int rideId, string src, string dest, int station_id)
{
    id = rideId;
    source = src;
    destination = dest;
    stationId = station_id;

}

void Ride::dfs(int source, int destination, vector<int>& path, vector<bool>& visited)
{
    visited[source] = true;
    path.push_back(source);

    if (source == destination) {
        allPaths.push_back(path);
    }
    else {
        for (int neighbor : adjacencyList[source]) {
            if (!visited[neighbor]) {
                dfs(neighbor, destination, path, visited);
            }
        }
    }

    visited[source] = false;
    path.pop_back();
}

vector<vector<int>> Ride::findAllPaths(int source, int destination)
{
    vector<bool> visited(adjacencyList.size() + 1, false);
    vector<int> path;
    dfs(source, destination, path, visited);


    sort(allPaths.begin(), allPaths.end(), [](const vector<int>& a, const vector<int>& b) {
        return a.size() < b.size();
        });

    return allPaths;
}

void Ride::showPaths(Station& sourceStation, Station& destinationStation)
{
    findAllPaths(sourceStation.getID(), destinationStation.getID());

    if (!allPaths.empty()) {
        cout << "Shortest path between stations " << sourceStation.getName() << " and " << destinationStation.getName() << ":" << endl;
        for (int s : allPaths.front()) {
            if (map.find(s) != map.end())
                cout << map[s].getName() << " -> ";

        }
        cout << endl;

        cout << "All paths between stations " << sourceStation.getName() << " and " << destinationStation.getName() << ":" << endl;
        for (int i = 0; i < allPaths.size(); ++i) {
            cout << "Path " << i + 1 << ": ";
            for (int s : allPaths[i]) {
                if (map.find(s) != map.end())
                    cout << map[s].getName() << " -> ";
            }
            cout << endl;
        }
    }
    else {
        cout << "No path found between stations " << sourceStation.getName() << " and " << destinationStation.getName() << endl;
    }
}

void Ride::startTheAdjacency()
{
    for (auto it = map.begin(); it != map.end(); it++)
    {
        adjacencyList[it->first] = it->second.connections;
    }
}

void Ride::addRide()
{
    cout << "Enter pick up station: ";
    cin >> source;
    cout << "Enter destination station: ";
    cin >> destination;

    pair <int, Station> srcResponse = Station::findStationByName(source);
    pair <int, Station> destResponse = Station::findStationByName(destination);


    if (srcResponse.first && destResponse.first)
        showPaths(srcResponse.second, destResponse.second);
    else if (!srcResponse.first)
        cout << "There is no station named " + source + " in our databse.";
    else if (!destResponse.first)
        cout << "There is no station named " + destination + " in our databse.";
    else
        cout << "There is no station named " + source + " or " + destination + " in our databse.";
}

/*vector <Ride> Ride::retrieveRides() {
    vector<Ride> rides;
    sqlite3* db;
    int rc = sqlite3_open("mydb_1 (1).db", &db);

    if (rc != SQLITE_OK) {
        cerr << "Error opening the database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return rides;
    }

    const char* sql = "SELECT * FROM Rides";

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return rides;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* src = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* dest = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int station_id = sqlite3_column_int(stmt, 3);
        Ride ride(id, string(src), string(dest), station_id);
        rides.push_back(ride);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return rides;

}*/


