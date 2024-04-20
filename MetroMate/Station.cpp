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

void Station::addConnection()
{
	int choice;
	do
	{
		string station;
		cout << "1. To add connection.\n0. To exit.";
		cin >> choice;
		switch (choice)
		{
		case 0:
			break;
		case 1:
			cout << "Enter the name of the other staion: ";
			cin >> station;
			/*for (int i = 0; i < stations.length(); i++)
			{
				if(stations[i].name == station)
					//call the function and give it (id, stations[i].id);
			}*/
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
	} while (choice);
}

void Station::displaYDetails(string type)
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

