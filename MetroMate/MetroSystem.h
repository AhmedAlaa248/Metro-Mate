#pragma once
#include <unordered_map>

#include"Station.h"

class MetroSystem
{
public:
	unordered_map<int, Station> stations;
};

