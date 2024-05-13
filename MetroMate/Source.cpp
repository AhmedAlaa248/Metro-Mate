//#include <unordered_map>
//
//
//#include "Station.h"
//
//#include "Admin.h"
//#include "Ride.h"
//
//using namespace std;
//
//unordered_map <int, Station> s;
//unordered_map <int, unordered_set<int>> a;
//unordered_map <int, unordered_set<int>> GlobalData::adjacencyList = a;
//unordered_map <int, Station> GlobalData::stations = s;
//
//int Station::nextId = 1;
//
////int main() {
////
////	GlobalData::RetrieveStationsFromDatabase();
////	Ride::startTheAdjacency();
////
////	Admin admin;
////	for (auto it = GlobalData::stations.begin(); it != GlobalData::stations.end(); it++) {
////		if (it->second.getName() == "")
////		{
////			GlobalData::stations.erase(it->second.getID());
////			continue;
////		}
////
////		it->second.displayDetails("user");
////	}
////	Station o;
////	admin.addStation(o);
////
////	for (auto it = GlobalData::stations.begin(); it != GlobalData::stations.end(); it++) {
////		if (it->second.getName() == "")
////		{
////			GlobalData::stations.erase(it->second.getID());
////			continue;
////		}
////
////		it->second.displayDetails("user");
////	}
////
////	return 1;
////}
//
//
////void main() {
////
////	Menu menu;
////
////	int choice;
////	do
////	{
////		cout << "Press:\n1. To login.\n2. To register.\n0. To exit.\n";
////		cin >> choice;
////
////		switch (choice)
////		{
////		case 0:
////			break;
////		case 1:
////			while (!menu.login())
////				cout << "wrong username or password.\n";
////			break;
////		case 2:
////			menu.signUp();
////			break;
////		default:
////			cout << "Invalid choice\n";
////			break;
////		}
////	} while (choice);
////	
////	
////
////	cout << "This is the fucking best project";
////
////}
