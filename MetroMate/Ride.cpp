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

/*void Ride::dfs(int source, int destination, vector<int>& path, vector<bool>& visited)
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

vector<vector<Station>> Ride::findAllPaths(int source, int destination)
{
    vector<bool> visited(adjacencyList.size() + 1, false);
    vector<int> path;
    dfs(source, destination, path, visited);


    sort(allPaths.begin(), allPaths.end(), [](const vector<int>& a, const vector<int>& b) {
        return a.size() < b.size();
        });

    return allPaths;
}

void Ride::addRide()
{
	cout << "Enter pick up station: ";
	cin >> source;
	cout << "Enter destination station: ";
	cin >> destination;
    

    for (int i = 0; i < stations.size(); i++)
    {
        if (source == stations[i].name)
            sourceStation = stations[i];

        if (destination == stations[i].name)
            destinationStation = stations[i];

    }

    vector<vector<Station>> allPaths = findAllPaths(sourceStation.id, destinationStation.id);
    if (!allPaths.empty()) {
        cout << "Shortest path between stations " << source << " and " << destination << ":" << endl;
        for (Station station : allPaths.front()) {
            cout << station.name << " ";
        }
        cout << endl;

        cout << "All paths between stations " << source << " and " << destination << ":" << endl;
        for (size_t i = 0; i < allPaths.size(); ++i) {
            cout << "Path " << i + 1 << ": ";
            for (Station station : allPaths[i]) {
                cout << station.name << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "No path found between stations " << source << " and " << destination << endl;
    }

}
*/