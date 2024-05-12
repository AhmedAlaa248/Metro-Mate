
#include"Ride.h"
#include <string>
#include <unordered_set>
#include <optional>
#include <utility>


Station::Station()
{

}
string Station::GetStationNameFromID(vector<Station>& stations, int id)
{
	for (const auto& station : stations)
	{
		if (station.id == id)
		{
			return station.name;
		}
	}
	return "";
}

void Station:: addToAdjacency(vector<Station>& stations) {
	
	for (const auto& station : stations)
	{
		string y = "";
		for (int i = 0; i < station.link.size();i++) {
			
			if (station.link[i] != ',') {
				y += station.link[i];
			}
			else {
				int x = stoi(y);
					
				y = "";
			string w=GetStationNameFromID(stations, x);
			addConnection(station.name, w);
				
			}
		
		}
		
	}



}

Station::Station(int idd, string namee, int inc, int tix, int passengers, string line, int subscriptions, string link) {
	id = idd;
	name = namee;
	totalIncome = inc;
	numOfSoldTickets = tix;
	numOfPassengers = passengers;
	lineNum = line;
	numOfSubscriptions = subscriptions;
	this->link = link;
	string n = "";

	//for (int i = 0; i < link.size(); i++)
	//{
	//	if (link[i] != ',')
	//		n.push_back(link[i]);
	//	else
	//	{
	//		this->connections.insert(stoi(n));
	//		n = "";
	//	}
	//}
}

Station::Station(string n, int line)
{
	id = nextId++;
	name = n;
	lineNum = line;
	totalIncome = 0;
	numOfSoldTickets = 0;
	numOfSubscriptions = 0;
	numOfPassengers = 0;
}

int Station::getID() const
{
	return id;
}

string Station::getName() const
{
	return name;
}

string Station::getLineNum() const
{
	return lineNum;
}

int Station::GetStationIdFromName(vector<Station> stations, string name) {
	for (const auto& station : stations) {
		if (station.getName() == name) {
			return station.getID();
		}
	}
	return -1;
}

void Station:: addConnection(string station1, string station2) {
	adjacencyList[station1].insert(station2);
	adjacencyList[station2].insert(station1);
}

void Station:: removeConnection(string station1, string station2) {
	if (adjacencyList.find(station1) != adjacencyList.end()) {
		adjacencyList[station1].erase(station2);
	}
	if (adjacencyList.find(station2) != adjacencyList.end()) {
		adjacencyList[station2].erase(station1);
	}
}

void Station :: addStation(string station) {
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

void Station::removeStation(string station) {
	adjacencyList[station].clear();

	for (auto& i : adjacencyList) {
		if (i.second.find(station) != i.second.end()) {
			i.second.erase(station);
		}
	}
}

void Station::dfs(string source, string destination, vector<string> &path, map<string,bool> &visited) {
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

vector<vector<string>> Station:: findAllPaths(string source, string destination) {
	map<string, bool> visited;
	vector<string> path;
	dfs(source, destination, path, visited);

	sort(allPaths.begin(), allPaths.end(), [](const vector<string>& a, const vector<string>& b) {
		return a.size() < b.size();
		});

	return allPaths;
}

vector<Station> Station ::RetrieveStationsFromDatabase()
{
	vector <Station> stations;

	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK)
	{
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return stations; // Return an empty vector if there's an error
	}

	const char* sql = "SELECT * FROM Stations";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK)
	{
		cout << "Error preparing the SQL statement" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return stations; // Return an empty vector if there's an error
	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int station_id = sqlite3_column_int(stmt, 0);
		const char* station_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		int income = sqlite3_column_int(stmt, 2);
		int tickets = sqlite3_column_int(stmt, 3);
		int n_passengers = sqlite3_column_int(stmt, 4);
		const char* metroline = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		int n_subscribtions = sqlite3_column_int(stmt, 6);
		const char* linkk = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
		Station s(station_id, station_name, income, tickets, n_passengers, metroline, n_subscribtions, linkk);
		stations.push_back(s);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return stations;
}

void Station::saveStationToDatabase(vector<Station>& stations)
{


	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK) {
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// Delete all existing records from the User table
	const char* delete_sql = "DELETE FROM Stations";
	rc = sqlite3_exec(db, delete_sql, nullptr, nullptr, nullptr);

	if (rc != SQLITE_OK) {
		cout << "Error deleting records from the Stations table: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// SQL query to insert a new record
	const char* insert_sql = "INSERT INTO Stations (station_id, name, income, Tickets, [N.Passengers], MetroLine, numOfSubscriptions, link) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

	for (const auto& station : stations) {
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);

		if (rc != SQLITE_OK) {
			cout << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}

		// Bind parameters to the prepared statement
		sqlite3_bind_int(stmt, 1, station.id);
		sqlite3_bind_text(stmt, 2, station.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, station.totalIncome);
		sqlite3_bind_int(stmt, 4, station.numOfSoldTickets);
		sqlite3_bind_int(stmt, 5, station.numOfPassengers);
		sqlite3_bind_text(stmt, 6, station.lineNum.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 7, station.numOfSubscriptions);
		sqlite3_bind_text(stmt, 8, station.link.c_str(), -1, SQLITE_STATIC);

		// Execute the SQL statement
		rc = sqlite3_step(stmt);

		if (rc != SQLITE_DONE) {
			cout << "Error executing the SQL statement: " << sqlite3_errmsg(db) << endl;
		}

		// Finalize the statement
		sqlite3_finalize(stmt);
	}

	sqlite3_close(db);
}


int Station::FindLengthOfSpecificPath(int index) {
	if (index >= 0 && index < allPaths.size()) {
		return allPaths[index].size();
	}
	else {
		return - 1;
	}

}

//int main() {
//	Station station;
//	vector<Station> stations;
//	stations = station.RetrieveStationsFromDatabase();
//
//	cout << "All Stations:\n";
//	for (const auto& station : stations) {
//		cout << "Station ID: " << station.id << endl;
//		cout << "Name: " << station.name << endl;
//		cout << "Income: " << station.totalIncome << endl;
//		cout << "Tickets: " << station.numOfSoldTickets << endl;
//		cout << "Number of Passengers: " << station.numOfPassengers << endl;
//		cout << "Metro Line: " << station.lineNum << endl;
//		cout << "Number of Subscriptions: " << station.numOfSubscriptions << endl;
//		cout << "Link: " << station.link << endl;
//		cout << "-----------------------------------\n";
//	}
//
//}