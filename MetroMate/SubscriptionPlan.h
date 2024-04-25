#include <iostream>
#include <string>
#include<vector>
#include"sqlite/sqlite3.h"
using namespace std;
class SubscriptionPlan {
private:
	int type;
	int price;
	int duration;
	int numStations;
	string plan_name;
	int trips;
	int stages;
	int plan_id;


	// constructor
public:
	SubscriptionPlan();
	SubscriptionPlan(int type, int price, int duration, int numStations)
		: type(type), price(price), duration(duration), numStations(numStations) {}

	SubscriptionPlan(int plan_id, string plan_name, int duration,int price,int trips, int stages, int type)
		: plan_id(plan_id), plan_name(plan_name), duration(duration), price(price), trips(trips), stages(stages), type(type){}


    // Setters
    void setType(int newtype);
    void setPrice(int newPrice);
    void setDuration(int newDuration);
    void setNumStations(int newNumStations);
	void setplan_name(string newplan_name);
	void setplan_id(int newplan_id);
	void settrips(int newtrips);
	void setstages(int newstages);

    // Getters
    int getType() const;
    int getPrice() const;
    int getDuration() const;
    int getNumStations() const;
	int getplan_id() const;
	int getstages() const;
	int gettrips() const;
	string getplan_name() const;

	int calcFare(int subscriptionType, int stage);
	int calculateStudentFare(int stage) const;
	int calculateMonthlyPublicFare(int stage) const;
	int calculateYearlyPublicFare(int stage) const;
	int calculateCashWalletFare(int numStations) const;
	void DisplayAllPlans() const;	

	static vector<SubscriptionPlan>RetrieveSubplansFromDatabase();

};
