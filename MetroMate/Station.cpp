
#include "Station.h"
Station::Station()
{
	id = nextId++;
	totalIncome = 0;
	numOfSoldTickets = 0;
	numOfSubscriptions = 0;
	numOfPassengers = 0;
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

int Station::getLineNum() const
{
	return lineNum;
}

pair<bool, Station> Station::findStationByName(string name, unordered_map<int,Station> stations)
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
				cout << "There is no " + connection + "station in our databse.";
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
