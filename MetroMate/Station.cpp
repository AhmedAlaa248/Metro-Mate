
#include "Station.h"
#include "sqlite/sqlite3.h"
#include <winsqlite/winsqlite3.h>

Station::Station()
{

	totalIncome = 0;
	numOfSoldTickets = 0;
	numOfSubscriptions = 0;
	numOfPassengers = 0;
}

Station::Station(string n, int line)
{

	name = n;
	lineNum = line;
	totalIncome = 0;
	numOfSoldTickets = 0;
	numOfSubscriptions = 0;
	numOfPassengers = 0;

}
Station::Station(int idd, string namee, int inc, int tix, int passengers, string line, int subscriptions) {
	id = idd;
	name = namee;
	totalIncome = inc;
	numOfSoldTickets = tix;
	numOfPassengers = passengers;
	linenum2 = line;
	numOfSubscriptions = subscriptions;
}

int Station::getID() const
{
	return id;
}

string Station::getName() const
{
	return name;
}

int Station::getLineNum() const
{
	return lineNum;
}

pair<bool, Station> Station::findStationByName(string name, unordered_map<int, Station> stations)
{
	Station station;
	bool found = false;
	for (auto it = stations.begin(); it != stations.end(); it++)
	{
		if ((*it).second.name == name)
		{
			station = (*it).second;
			found = true;
			break;
		}
	}
	return pair<bool, Station>(found, station);
}

void Station::rideStarted(string type)
{
	if (type == "Cash Wallet")
		numOfSoldTickets++;

	numOfPassengers++;
}


void Station::addConnection(int station1, int station2) {
	adjacencyList[station1].insert(station2);
	adjacencyList[station2].insert(station1);
}

void Station::removeConnection(int station1, int station2) {
	adjacencyList[station1].erase(station2);
	adjacencyList[station2].erase(station1);
}

void Station::removeStation(int station) {
	adjacencyList.erase(station);
	for (auto& pair : adjacencyList) {
		pair.second.erase(station);
	}
}
void Station::addConnectionToStation(Station& station, unordered_map<int, Station> stations) {
	cout << "Enter connections for station " << station.name;
	string connection;
	int choice = 1;
	bool first = true;
	do {
		if (!first)
		{
			cout << "1. To add another connection.\n0. To stop.";
			cin >> choice;
		}
		else first = false;
		pair<bool, Station> response;

		switch (choice)
		{
		case 0:
			break;
		case 1:
			cout << "Enter the station you want connect with: ";
			cin >> connection;
			response = findStationByName(connection, stations);

			if (response.first)
				addConnection(station.id, response.second.id);
			else
				cout << "There is no station named " + connection + " in our databse.";
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (choice != 0);
}

void Station::addStation(unordered_map<int, Station> stations)
{
	string name;
	int line;
	cout << "Enter station name: ";
	cin >> name;
	cout << "Enter station line number: ";
	cin >> line;

	Station station(name, line);
	addConnectionToStation(station, stations);

	//Add it to the list
	stations[id] = station;
}

void Station::displayDetails(string type)
{
	cout << "Station details:\n";
	cout << "name: " + name;
	cout << "\tline number: " + lineNum;
	if (type == "admin")
	{
		cout << "\ttotal income: " + totalIncome;
		cout << "\nnumber of sold tickets: " + numOfSoldTickets;
		cout << "\tnumber of subscriptions: " + numOfSubscriptions;
		cout << "\tnumber of passengers: " + numOfPassengers;
	}
}
vector<Station> Station::RetrieveStationsFromDatabase()
{
	vector<Station> Stations;
	sqlite3* db;
	int rc = sqlite3_open("mydb_1 (1).db", &db);

	if (rc != SQLITE_OK)
	{
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return Stations;
	}


	const char* sql = "SELECT * FROM Stations";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK)
	{
		cout << "Error preparing the SQL statement" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return Stations;
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


		// Creating SubscriptionPlan objects and adding them to the vector
		Station s(station_id, station_name, income, tickets, n_passengers, metroline, n_subscribtions);
		Stations.push_back(s);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return Stations;
}
void Station::printDetails() {
	cout << "Station ID: " << id << endl;
	cout << "Station Name: " << name << endl;
	cout << "Income: " << totalIncome << endl;
	cout << "Tickets: " << numOfSoldTickets << endl;
	cout << "Number of Passengers: " << numOfPassengers << endl;
	cout << "Metro Line: " << linenum2 << endl;
	cout << "Number of Subscriptions: " << numOfSubscriptions << endl;
	cout << endl;
}
//int main() {
//	Station w;
//	vector <Station> q = w.RetrieveStationsFromDatabase();
//	for (auto z : q) {
//		z.printDetails();
//	}
//}