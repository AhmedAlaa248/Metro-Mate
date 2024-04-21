
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
void Station::addStationWithConnections(int stationId) {
	cout << "Enter connections for station " << stationId << " (Enter -1 to stop):" << endl;
	int connection;
	while (true) {
		cout << "Enter connection: ";
		cin >> connection;
		if (connection == -1) break;
		addConnection(stationId, connection);
	}
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
