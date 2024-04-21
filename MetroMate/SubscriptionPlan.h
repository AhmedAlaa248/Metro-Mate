#include <iostream>
#include <string>
#include<vector>
#include"sqlite/sqlite3.h"
using namespace std;
class SubscriptionPlan {
private:
	int type = 1;
	int price = 33;
	int duration = 3;
	int numStations = 9;
	string plan_name;
	int trips=0;
	int stages=1;
	int plan_id=1;


	// constructor
public:
	SubscriptionPlan(int type, int price, int duration, int numStations)
		: type(type), price(price), duration(duration), numStations(numStations) {}

	SubscriptionPlan(int plan_id, string plan_name, int duration,int price,int trips, int stages)
		: plan_id(plan_id), plan_name(plan_name), duration(duration), price(price), trips(trips), stages(stages){}


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
	void DisplayPlanInfo() const;

};
