#include"SubscriptionPlan.h"


SubscriptionPlan::SubscriptionPlan()
{
}

//setters
	void SubscriptionPlan::setType(int newtype)
	{
		type = newtype;
	}
	void SubscriptionPlan::setPrice(int newPrice)
	{
		price = newPrice;
	}
	void SubscriptionPlan::setDuration(int newDuration)
	{
		duration = newDuration;
	}
	void SubscriptionPlan::setNumStations(int newNumStations)
	{
		numStations = newNumStations;
	}
	void SubscriptionPlan:: setplan_name(string newplan_name)
	{
		plan_name = newplan_name;
	}
	void SubscriptionPlan::settrips(int newtrips)
	{
		trips = newtrips;
	}
	void SubscriptionPlan::setstages(int newstages)
	{
		stages = newstages;
	}
	void SubscriptionPlan::setplan_id(int newplan_id)
	{
		plan_id = newplan_id;
	}

	// Getters
	int SubscriptionPlan::getType() const {
		return type;
	}
	int SubscriptionPlan::getPrice() const {
		return price;
	}
	int SubscriptionPlan::getDuration() const {
		return duration;
	}
	int SubscriptionPlan::getNumStations() const
	{
		return numStations;
	}
	int SubscriptionPlan::getplan_id() const
	{
		return plan_id;
	}
	int SubscriptionPlan::getstages() const
	{
		return stages;
	}
	int SubscriptionPlan::gettrips() const
	{
		return trips;
	}
	string SubscriptionPlan::getplan_name() const
	{
		return plan_name;
	}



	// calculate the fare for each subscription

	int SubscriptionPlan::calcFare(int subscriptionType, int num_station) {
		int fare = 0;
		switch (subscriptionType) {
		case 1: // Student Card
			fare = calculateStudentFare(num_station);
			break;
		case 2: // Public Card
			if (duration == 1) // Monthly
				fare = calculateMonthlyPublicFare(num_station);
			else if (duration == 12) // Yearly
				fare = calculateYearlyPublicFare(num_station);
			break;
		case 3: // Cash Wallet Card
			fare = calculateCashWalletFare(num_station);
			break;
		}
		return fare;
	}
	int SubscriptionPlan::calculateStudentFare(int num_station) const {
		if (num_station >= 1 && num_station <= 9 )
			return 33;
		else if (num_station >= 9 && num_station <= 16)
			return 41;
		else if (num_station >= 16 && num_station <= 23)
			return 50;
		else
			return 65;
	}
	int SubscriptionPlan::calculateMonthlyPublicFare(int num_station) const {
		int fare = 0;
		if (num_station >= 1 && num_station <= 9)
			fare = 230;
		else if (num_station >= 9 && num_station <= 16)
			fare = 290;
		else if (num_station >= 16 && num_station <= 23)
			fare = 340;
		else
			fare = 450;
		return fare;
	}
	int SubscriptionPlan::calculateYearlyPublicFare(int num_station) const {
		if (num_station >= 1 && num_station <= 9)
			return 1500;
		else if (num_station >= 9 && num_station <= 16)
			return 2500;
		else if (num_station >= 16 && num_station <= 23)
			return 3500;
		else
			return 4500;
	}
	int SubscriptionPlan::calculateCashWalletFare(int numStations) const {
		if (numStations >= 1 && numStations <= 9)
			return 6 * numStations;
		else if (numStations >= 10 && numStations <= 16)
			return 8 * numStations;
		else if (numStations >= 17 && numStations <= 23)
			return 12 * numStations;
		else
			return 15 * numStations;
	}


	void SubscriptionPlan::DisplayAllPlans() const{
		vector<SubscriptionPlan> plans = {
			SubscriptionPlan(1, 33, 3, 9),   // Student Card - Stage 1
			SubscriptionPlan(1, 41, 3, 16),  // Student Card - Stage 2
			SubscriptionPlan(1, 50, 3, 23),  // Student Card - Stage 3
			SubscriptionPlan(1, 65, 3, 50),  // Student Card - Stage 4 (no limit)
			SubscriptionPlan(2, 230, 1, 9),  // Public Card - 1 month - Stage 1
			SubscriptionPlan(2, 290, 1, 16), // Public Card - 1 month - Stage 2
			SubscriptionPlan(2, 340, 1, 23), // Public Card - 1 month - Stage 3
			SubscriptionPlan(2, 450, 1, 50), // Public Card - 1 month - Stage 4 (no limit)
			SubscriptionPlan(2, 1500, 12, 9),    // Public Card - 1 year - Stage 1
			SubscriptionPlan(2, 2500, 12, 16),   // Public Card - 1 year - Stage 2
			SubscriptionPlan(2, 3500, 12, 23),   // Public Card - 1 year - Stage 3
			SubscriptionPlan(2, 4500, 12, 50),   // Public Card - 1 year - Stage 4 (no limit)
			SubscriptionPlan(3, 0, 24, 50)   // Cash Wallet Card (no limit)
		};

		cout << "Available Subscription Plans:\n";
		for (const auto& plan : plans) {
			switch (plan.getType()) {
			case 1:
				cout << "Type: Student Card" << endl;
				break;
			case 2:
				cout << "Type: Public Card" << endl;
				break;
			case 3:
				cout << "Type: Cash Wallet Card" << endl;
				break;
			default:
				cout << "Invalid choice, please try again\n";
				break;
			}
			cout << "Price: " << plan.getPrice() << " L.E" << endl;
			cout << "Duration: " << plan.getDuration() << " Months" << endl;
			cout << "Number of Stations: " << plan.getNumStations() << endl;
			cout << endl;
		}
	}
	void SubscriptionPlan::DisplayPlanInfo() const
	{
		cout << "Subscription Plan Information:\n";
		cout << "-----------------------------\n";

		cout << "Type: ";
		switch (getType()) {
		case 1:
			cout << "Student Card";
			break;
		case 2:
			cout << "Public Card";
			break;
		case 3:
			cout << "Cash Wallet Card";
			break;
		default:
			cout << "Invalid";
		}
		cout << "\nPrice: " << getPrice() << " LE" << endl;
		cout << "Duration: " << getDuration() << " Months" << endl;
		cout << "Number of Stations: " << getNumStations() << endl;
		cout << endl;
	}


	// call back function to store the table's data in variables
	static int callback(void* data, int argc, char** argv, char**)
	{
		vector<SubscriptionPlan>* subPlan = static_cast<vector<SubscriptionPlan>*>(data);

		int plan_id = atoi(argv[0] ? argv[0] : "0");
		string plan_name = argv[1] ? argv[1] : "";
		int duration = atoi(argv[2] ? argv[2] : "0");
		int price = atoi(argv[3] ? argv[3] : "0");
		int trips = atoi(argv[4] ? argv[4] : "0");
		int stages = atoi(argv[5] ? argv[5] : "0");


		

		subPlan->push_back(SubscriptionPlan{ plan_id, plan_name, duration, price, trips, stages });

		return 0;
	}
	
	//Load all data retrieved in Vector list of Subscriptions
	static vector<SubscriptionPlan> loadAllSubplanFromDatabase(sqlite3* db)
	{
		vector<SubscriptionPlan> subPlan;


		const char* sql = "SELECT * from subplan";

		char* errMsg = nullptr;


		int rc = sqlite3_exec(db, sql, callback, &subPlan, &errMsg);
		if (rc != SQLITE_OK)
		{
			cerr << "SQL error: " << errMsg << endl;
			sqlite3_free(errMsg);
		}

		return subPlan;

	}


	/*int main() {
		sqlite3* db;
		int rc = sqlite3_open("mydb.db", &db);
		if (rc)
		{
			cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
			return 1;
		}
	//store the data from database into vector of Object subscription  

		vector<SubscriptionPlan> subPlans = loadAllSubplanFromDatabase(db);

		// Display the retrieved subscription plans
		for (const auto& plan : subPlans)
		{
			cout << "Plan ID: " << plan.getplan_id() << ", Name: " << plan.getplan_name() << ", Duration: " << plan.getDuration() << ", Price: " << plan.getPrice() << ", Trips: " << plan.gettrips() << ", Stages: " << plan.getstages() << endl;
		}

		sqlite3_close(db);

		return 0;
	}

*/


