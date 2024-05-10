#include"GlobalData.h"
#include"Ride.h"

#define map GlobalData::stations

Station::Station()
{
}

Station::Station(int idd, string namee, int inc, int tix, int passengers, string line, int subscriptions, string link) {
	id = idd;
	name = namee;
	totalIncome = inc;
	numOfSoldTickets = tix;
	numOfPassengers = passengers;
	lineNum = line;
	numOfSubscriptions = subscriptions;

	string n = "";

	for (int i = 0; i < link.size(); i++)
	{
		if (link[i] != ',')
			n.push_back(link[i]);
		else
		{
			this->connections.insert(stoi(n));
			n = "";
		}
	}
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

pair<bool, Station> Station::findStationByName(string name)
{

	Station station;

	bool found = false;
	for (auto it = map.begin(); it != map.end(); it++)
	{
		if ((*it).second.name == name)
		{
			found = true;
			return pair<bool, Station>(found, (*it).second);
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

void Station::addConnection(int con) {
	connections.insert(con);
	map[this->id].connections = this->connections;
	if (map.find(con) != map.end())
	{
		map[con].connections.insert(this->id);
		cout << this->name << " is connected successfully with " << map[con].getName() << endl;
	}
	else
		cout << "Not connected try again";

}

void Station::removeConnection(int con) {
	connections.erase(con);
	map[con].connections.erase(this->id);
}

void Station::addConnectionToStation() {
	cout << "Enter connections for station " << this->name << '\n';
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
			response = findStationByName(connection);

			if (findStationByName(connection).first)
				addConnection(findStationByName(connection).second.getID());
			else
				cout << "There is no station named " + connection + " in our databse.\n";
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (choice != 0);
}

void Station::removeStation() {
	int choice;
	do
	{
		string name;
		cout << "Enter station name to delete: ";
		cin >> name;
		pair<bool, Station> response = Station::findStationByName(name);
		if (response.first)
		{
			if (map.erase(response.second.getID()))
			{
				cout << "Station " << name << " deleted successfully from the database\n";
				cout << "Press:\n0.To exit\n1.To delete another station.";
				cin >> choice;
			}
		}
		else
		{
			cout << "There is no station named " + name + " in our databse.\n";
			cout << "Press:\n0.To exit\n1.To try again.";
			cin >> choice;
		}
	} while (choice);

	Ride::startTheAdjacency();
}

void Station::addStation()
{
	string name;
	int line;
	cout << "Enter station name: ";
	cin >> name;
	cout << "Enter station line number: ";
	cin >> line;

	Station s(name, line);
	map[s.getID()] = s;

	s.addConnectionToStation();
	Ride::startTheAdjacency();
}

void Station::displayDetails(string type)
{
	cout << "Station details:\n";
	cout << "name: " + this->name << "\n";
	cout << "Line number: " + this->getLineNum() << endl;
	cout << "connected with: ";

	for (auto it = connections.begin(); it != connections.end(); it++)
	{
		if (it == connections.begin())
			cout << map[*it].getName();
		else
			cout << ", " << map[*it].getName();
	}
	cout << endl;

	if (type == "admin")
	{
		cout << "\ttotal income: " + this->totalIncome;
		cout << "\nnumber of sold tickets: " + this->numOfSoldTickets;
		cout << "\tnumber of subscriptions: " + this->numOfSubscriptions;
		cout << "\tnumber of passengers: " + this->numOfPassengers << endl;
	}
}