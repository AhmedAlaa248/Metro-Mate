#pragma once
#include<iostream>
#include "Subscription.h"

using namespace std;
class User
{
public:
	int id;
	string name;
	string password;
	string email;
	Subscription subscription;
};

