#include "Ride.h"
#include <iomanip>
#include <chrono>
#include <sstream>
#include <ctime>
#include <string>
#include "winsqlite/winsqlite3.h"


Ride::Ride()
{
}

Ride::Ride(int rideId, string src, string dest, int stationId, string date, int usr_id, int faree)
{
	id = rideId;
	source = src;
	destination = dest;
	this->stationId = stationId;
	ridedate = date;
	user_id = usr_id;
	fare = faree;

}
vector<Ride> Ride::RetrieveRidesFromDatabase() {
	vector<Ride> rides;

	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK)
	{
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return rides;
	}

	const char* sql = "SELECT * FROM Rides";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK)
	{
		cout << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return rides;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int ride_id = sqlite3_column_int(stmt, 0);
		const char* source = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		int station_id = sqlite3_column_int(stmt, 3);
		const char* datee = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		int user_id = sqlite3_column_int(stmt, 5);
		int fare = sqlite3_column_int(stmt, 6);
		Ride ride(ride_id, source, destination, station_id, datee, user_id, fare);
		rides.push_back(ride);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return rides;
}
void Ride::saveRideToDatabase(vector<Ride>& rides)
{


	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK) {
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// Delete all existing records from the User table
	const char* delete_sql = "DELETE FROM Rides";
	rc = sqlite3_exec(db, delete_sql, nullptr, nullptr, nullptr);

	if (rc != SQLITE_OK) {
		cout << "Error deleting records from the Rides table: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	// SQL query to insert a new record
	const char* insert_sql = "INSERT INTO Rides (Ride_Id, source, destination, station_id, ride_date, User_id, Fare) VALUES (?, ?, ?, ?, ?, ?, ?)";

	for (const auto& ride : rides) {
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);

		if (rc != SQLITE_OK) {
			cout << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}

		// Bind parameters to the prepared statement
		sqlite3_bind_int(stmt, 1, ride.id);
		sqlite3_bind_text(stmt, 2, ride.source.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, ride.destination.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 4, ride.stationId);
		sqlite3_bind_text(stmt, 5, ride.ridedate.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 6, ride.user_id);
		sqlite3_bind_int(stmt, 7, ride.fare);


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
vector<Ride> Ride::GetRidesForUser(int user_id) {
	std::vector<Ride> user_rides;

	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK) {
		std::cerr << "Error opening the database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return user_rides;
	}

	const char* sql = "SELECT * FROM Rides WHERE User_id = ?";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK) {
		std::cerr << "Error preparing the SQL statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return user_rides;
	}


	rc = sqlite3_bind_int(stmt, 1, user_id);
	if (rc != SQLITE_OK) {
		std::cerr << "Error binding parameter: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return user_rides;
	}


	while (sqlite3_step(stmt) == SQLITE_ROW) {
		Ride ride;
		ride.id = sqlite3_column_int(stmt, 0);
		ride.source = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		ride.destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		ride.stationId = sqlite3_column_int(stmt, 3);
		ride.ridedate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		ride.user_id = sqlite3_column_int(stmt, 5);
		ride.fare = sqlite3_column_int(stmt, 6);
		user_rides.push_back(ride);
	}


	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return user_rides;
}
