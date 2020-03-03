//DATABASE USING SQLITE

#include "database.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <sqlite3.h>


int database::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void database::connect()
{
	sqlite3* db;
	char* zErrMsg = 0;
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
}

void database::close()
{
	sqlite3* db;
	rc = sqlite3_open("test.db", &db);
	sqlite3_close(db);
}

void database::create()
{
	sqlite3* db;
	char* zErrMsg = 0;
	const char* sql;
	//Open database
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	sql = "CREATE TABLE SOFTWARE_POPULARITY(" \
		"ID INT PRIMARY KEY     NOT NULL," \
		"PRODUCT           TEXT    NOT NULL," \
		"POPULARITY            INT     NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}
	sqlite3_close(db);
}

void database::delete_records()
{
	sqlite3* db;
	rc = sqlite3_open("test.db", &db);
	char* zErrMsg = 0;
	const char* sql = "DELETE from SOFTWARE_POPULARITY;";
	const char* data = "Callback function called";

	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

std::vector<std::pair<std::string, int>> database::get_records()
{
	std::vector<std::pair<std::string, int>> result;
	sqlite3* db;
	sqlite3_open("test.db", &db);
	std::string sql_str = "SELECT * from SOFTWARE_POPULARITY";
	const char* sql = sql_str.c_str();
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc == SQLITE_OK) {
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
		{
			const char* product_str = (char*)sqlite3_column_text(stmt, 1);
			std::string product = product_str;
			const char* popularity_str = (char*)sqlite3_column_text(stmt, 2);
			int popularity = atoi(popularity_str);
			result.push_back(std::make_pair(product, popularity));
		}
	}
	else {
		std::cout << sqlite3_errmsg(db);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return result;
}


void database::add(std::string product, int popularity)
{
	sqlite3* db;
	rc = sqlite3_open("test.db", &db);
	char* zErrMsg = 0;
	std::string sql_str = "INSERT INTO SOFTWARE_POPULARITY (ID,PRODUCT,POPULARITY) "  \
		"VALUES ('" + std::to_string(id) + "','" + product + "','" + std::to_string(popularity) + "');";
	const char* sql = sql_str.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Record added successfully\n");
	}
	id++;
}

void database::print_data()
{
	sqlite3* db;
	rc = sqlite3_open("test.db", &db);
	const char* sql = "SELECT * from SOFTWARE";
	char* zErrMsg = 0;
	const char* data = "Callback function called";
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}
	return;
}
