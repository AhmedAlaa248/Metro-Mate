#pragma once
#include<iostream>

using namespace std;

class Menu
{
	string userName, password;
public:
	Menu();
	bool login();
	int adminMenu();
	int userMenu();
};

