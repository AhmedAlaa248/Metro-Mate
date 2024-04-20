#pragma once
#include<iostream>
#include <string>
#include <cctype>
#include <regex>
#include "User.h"

using namespace std;

class Validator
{
public:
	Validator();
	//bool notUsedUserName(string& userName, List users);
	bool isStrongPassword(string password);
	bool isTheCorrectPassword(User user,string password);
	bool isValidEmailAddress(string& email);
};
