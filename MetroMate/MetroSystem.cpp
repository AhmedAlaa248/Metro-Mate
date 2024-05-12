#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

class MetroSystem {
private:


    unordered_map<string, unordered_set<string>> adjacencyList;
    vector<vector<string>> allPaths;



public:
    void addConnection(string station1, string station2) {
        adjacencyList[station1].insert(station2);
        adjacencyList[station2].insert(station1);
    }

    void removeConnection(string station1, string station2) {
        if (adjacencyList.find(station1) != adjacencyList.end()) {
            adjacencyList[station1].erase(station2);
        }
        if (adjacencyList.find(station2) != adjacencyList.end()) {
            adjacencyList[station2].erase(station1);
        }
    }

    void addStation(string station) {
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

        for (string neighbor : neighbors) {
            addConnection(station, neighbor);
        }
    }

    void removeStation(string station) {
        adjacencyList[station].clear();

        for (auto& i : adjacencyList) {
            if (i.second.find(station) != i.second.end()) {
                i.second.erase(station);
            }
        }
    }

    void dfs(string source, string destination, vector<string>& path, map<string, bool>& visited) {
        visited[source] = true;
        path.push_back(source);

        if (source == destination) {
            allPaths.push_back(path);
        }
        else {
            for (const string& neighbor : adjacencyList[source]) {
                if (!visited[neighbor]) {
                    dfs(neighbor, destination, path, visited);
                }
            }
        }

        visited[source] = false;
        path.pop_back();
    }

    vector<vector<string>> findAllPaths(string source, string destination) {
        map<string, bool> visited;
        vector<string> path;
        dfs(source, destination, path, visited);

        sort(allPaths.begin(), allPaths.end(), [](const vector<string>& a, const vector<string>& b) {
            return a.size() < b.size();
            });

        return allPaths;
    }
};

//int main() {
//    MetroSystem metro;
//
//    metro.addConnection("1", "2");
//    metro.addConnection("2", "3");
//    metro.addConnection("2", "5");
//    metro.addConnection("2", "6");
//    metro.addConnection("5", "4");
//    metro.addConnection("1", "4");
//    metro.addConnection("1", "6");
//    metro.addConnection("4", "6");
//    metro.addStation("7");
//    metro.removeStation("4");
//    string source = "3";
//    string destination = "6";
//
//    vector<vector<string>> allPaths = metro.findAllPaths(source, destination);
//    if (!allPaths.empty()) {
//        cout << "Shortest path between stations " << source << " and " << destination << ":" << endl;
//        for (const string& station : allPaths.front()) {
//            cout << station << " ";
//        }
//        cout << endl;
//
//        cout << "All paths between stations " << source << " and " << destination << ":" << endl;
//        for (size_t i = 0; i < allPaths.size(); ++i) {
//            cout << "Path " << i + 1 << ": ";
//            for (const string& station : allPaths[i]) {
//                cout << station << " ";
//            }
//            cout << endl;
//        }
//    }
//    else {
//        cout << "No path found between stations " << source << " and " << destination << endl;
//    }
//
//    return 0;
//}
