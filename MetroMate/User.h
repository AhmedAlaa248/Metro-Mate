#pragma once
#include<iostream>
#include "Subscription.h"
#include "Ride.h"
using namespace std;
class User
{
public:
	int id, balance;
	string name;
	string userName;
	string password;
	string email;
	Subscription subscription;
	Ride ride;

	User();
};

