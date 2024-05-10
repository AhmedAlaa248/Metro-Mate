#pragma once
#include <unordered_map>
#include <winsqlite/winsqlite3.h>

#include "Station.h"
#include "Station.h"
#include "sqlite/sqlite3.h"

class GlobalData
{
public:
	static unordered_map <int, Station> stations;
	static unordered_map<int, unordered_set<int>> adjacencyList;

	void static RetrieveStationsFromDatabase();
};

