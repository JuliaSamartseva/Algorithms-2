#pragma once
#include <string>
#include "HashTable.h"

class database
{
private:
	int rc;
	int id = 1;
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
public:
	void connect();
	void close();
	void create();
	void delete_records();
	HashEntry *get_record(int id);
	void add(std::string company, std::string product);
	void print_data();
};

