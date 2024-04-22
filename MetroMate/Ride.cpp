#include "Ride.h"

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

void Ride::showPaths(unordered_map<int, Station> stations, Station& sourceStation, Station& destinationStation)
{
    findAllPaths(sourceStation.getID(),destinationStation.getID());

    if (!allPaths.empty()) {
        cout << "Shortest path between stations " << sourceStation.getName() << " and " << destinationStation.getName() << ":" << endl;
        for (int s : allPaths.front()) {
            if (stations.find(s) != stations.end())
                cout << stations[s].getName() << " ";
            
        }
        cout << endl;

        cout << "All paths between stations " << sourceStation.getName() << " and " << destinationStation.getName() << ":" << endl;
        for (size_t i = 0; i < allPaths.size(); ++i) {
            cout << "Path " << i + 1 << ": ";
            for (int s : allPaths[i]) {
                if (stations.find(s) != stations.end())
                    cout << stations[s].getName() << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "No path found between stations " << sourceStation.getName() << " and " << destinationStation.getName() << endl;
    }
}

void Ride::addRide(unordered_map<int, Station> stations)
{
    cout << "Enter pick up station: ";
    cin >> source;
    cout << "Enter destination station: ";
    cin >> destination;

    pair <int, Station> srcResponse = Station::findStationByName(source, stations);
    pair <int, Station> destResponse = Station::findStationByName(destination, stations);

    if (srcResponse.first && destResponse.first)
        showPaths(stations, srcResponse.second, destResponse.second);
    else if (!srcResponse.first)
        cout << "There is no station named " + source + " in our databse.";
    else if (!destResponse.first)
        cout << "There is no station named " + destination + " in our databse.";
    else
        cout << "There is no station named " + source + " or " + destination + " in our databse.";

}



