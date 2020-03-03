#pragma once
#include <string>
#include <vector>

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
	std::vector<std::pair<std::string, int>> get_records();
	void add(std::string product, int popularity);
	void print_data();
};

