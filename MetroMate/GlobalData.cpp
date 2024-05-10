#include "GlobalData.h"

void GlobalData::RetrieveStationsFromDatabase()
{
	sqlite3* db;
	int rc = sqlite3_open("mydb_1_1.db", &db);

	if (rc != SQLITE_OK)
	{
		cout << "Error opening the database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
	}

	const char* sql = "SELECT * FROM Stations";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK)
	{
		cout << "Error preparing the SQL statement" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int station_id = sqlite3_column_int(stmt, 0);
		const char* station_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		int income = sqlite3_column_int(stmt, 2);
		int tickets = sqlite3_column_int(stmt, 3);
		int n_passengers = sqlite3_column_int(stmt, 4);
		const char* metroline = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		int n_subscribtions = sqlite3_column_int(stmt, 6);
		const char* linkk = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

		// Creating SubscriptionPlan objects and adding them to the vector
		Station s(station_id, station_name, income, tickets, n_passengers, metroline, n_subscribtions, linkk);
		stations[station_id] = s;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
