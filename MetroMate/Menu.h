#pragma once
#include<iostream>
#include "User.h"
#include "Validator.h"

using namespace std;

class Menu
{
	string userName, password;
public:
	Validator validator;

	Menu();
	bool login();
	void signUp();
	int adminMenu();
	int userMenu();
};

