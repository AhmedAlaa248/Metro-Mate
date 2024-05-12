#include"SubscriptionPlan.h"

#include "set"
#include "unordered_set"


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
void SubscriptionPlan::setplan_name(string newplan_name)
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
	if (num_station >= 1 && num_station <= 9)
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
vector<SubscriptionPlan> SubscriptionPlan::RetrieveSubplansFromDatabase()
{
	vector<SubscriptionPlan> subplanList;
	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK)
	{
		// Error opening the database
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return subplanList;
	}

	//const char* sql = "SELECT [plan_id], [plan_name], duration, price, trips, stages FROM subplan";
	const char* sql = "SELECT * FROM subplan";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK)
	{
		cout << "Error preparing the SQL statement" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return subplanList;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int plan_id = sqlite3_column_int(stmt, 0);
		const char* plan_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		int duration = sqlite3_column_int(stmt, 2);
		int price = sqlite3_column_int(stmt, 3);
		int trips = sqlite3_column_int(stmt, 4);
		int stages = sqlite3_column_int(stmt, 5);
		int type = sqlite3_column_int(stmt, 6);
		int numofstations = sqlite3_column_int(stmt, 7);
		

		SubscriptionPlan plan(plan_id, plan_name, duration, price, trips, stages, type,numofstations);
		subplanList.push_back(plan);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return subplanList;
}
void SubscriptionPlan::DisplayAllPlans() const {
	vector<SubscriptionPlan> subplans;
	subplans = RetrieveSubplansFromDatabase();
	cout << "Available Subscription Plans:\n";
	for (const auto& plan : subplans) {
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

		// Determine number of stations based on stages
		int stages = plan.getstages();
		int numStations;
		if (stages == 1)
			numStations = 9;
		else if (stages == 2)
			numStations = 16;
		else if (stages == 3)
			numStations = 23;
		else
			numStations = 50;

		cout << "Number of Stations: " << numStations << endl;
		cout << "Number of trips: " << plan.gettrips() << endl;
		cout << endl;

	}
}

void SubscriptionPlan::saveSubplanToDatabase(vector<SubscriptionPlan>& subplans)
{
	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK) {
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// Delete all existing records from the Subplan table
	const char* delete_sql = "DELETE FROM Subplan";
	rc = sqlite3_exec(db, delete_sql, nullptr, nullptr, nullptr);

	if (rc != SQLITE_OK) {
		cout << "Error deleting records from the Subplan table: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// SQL query to insert a new record
	const char* insert_sql = "INSERT INTO Subplan ([plan_id], [plan_name], duration, price, trips, stages, type, [N.Stations]) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

	for (const auto& subplan : subplans) {
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);

		if (rc != SQLITE_OK) {
			cout << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}

		// Bind parameters to the prepared statement
		sqlite3_bind_int(stmt, 1, subplan.plan_id);
		sqlite3_bind_text(stmt, 2, subplan.plan_name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, subplan.duration);
		sqlite3_bind_int(stmt, 4, subplan.price);
		sqlite3_bind_int(stmt, 5, subplan.trips);
		sqlite3_bind_int(stmt, 6, subplan.stages);
		sqlite3_bind_int(stmt, 7, subplan.type);
		sqlite3_bind_int(stmt, 8, subplan.numStations);

		// Execute the SQL statement
		rc = sqlite3_step(stmt);

		if (rc != SQLITE_DONE) {
			cout << "Error executing the SQL statement: " << sqlite3_errmsg(db) << endl;
		}

		// Finalize the statement
		sqlite3_finalize(stmt);
	}

	sqlite3_close(db);
}










