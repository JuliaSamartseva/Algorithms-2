#pragma once
#include <string>
#include <vector>

class HashEntry
{
private:
	std::string key;
	//value - additional information for the certain key
	std::string value;
public:
	HashEntry(std::string key, std::string value);
	std::string getKey() { return key; };
	std::string getValue() { return value; };
};

struct hash_row {
	int m = 0;
	int a = 0;
	int b = 0;
	std::vector<HashEntry*> second_hash;
};

class HashTable
{
private:
	std::vector<hash_row> rows;
	int TABLE_SIZE;
	const int p = 101;
	int default_a, default_b;
	std::vector<std::vector<HashEntry*>> findInitialTable(std::vector<HashEntry*> data);
	int computeHash(std::string data, int m, int a, int b);
	std::vector<HashEntry*> findSecondaryHashTable(std::vector<HashEntry*> initial_table, int& a, int& b);
public:
	HashTable(int table_size, std::vector<HashEntry*> data);
	std::string search(std::string key);
	~HashTable();
};

