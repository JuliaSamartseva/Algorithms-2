#include "HashTable.h"

HashEntry::HashEntry(std::string key, std::string value)
{
	this->key = key;
	this->value = value;
}

std::vector<std::vector<HashEntry*>> HashTable::findInitialTable(std::vector<HashEntry*> data)
{
	std::vector<std::vector<HashEntry*>> result;
	result.resize(TABLE_SIZE);
	for (HashEntry* entry : data) {
		int hash = computeHash(entry->getKey(), TABLE_SIZE, default_a, default_b);
		result[hash].push_back(entry);
	}
	return result;
}

int HashTable::computeHash(std::string data, int m, int a, int b)
{
	//find hash for a string
	int k = 0;
	int hash = 0;
	for (int i = 0; i < data.size(); i++) {
		int x = (int)data[i];
		hash = ((hash + a*x + b) % p) % m;
	}
	return hash;
}

std::vector<HashEntry*> HashTable::findSecondaryHashTable(std::vector<HashEntry*> initial_table, int& a, int& b)
{ 
	int new_size = pow(initial_table.size(), 2);
	std::vector<HashEntry*> result;
	result.resize(new_size);
	a = (rand() % (p-1)) + 1; 
	b = (rand() % (p-1)) + 1;
	for (int j = 0; j < initial_table.size(); j++) {
		int new_hash = computeHash(initial_table[j]->getKey(), new_size, a, b);
		if (result[new_hash] == NULL) //if there're no collisions
			result[new_hash] = initial_table[j];
		else { //there was a collision -> need to recompute/change values of a and b
			result = findSecondaryHashTable(initial_table, a, b);
		}
	}
	return result;
}

HashTable::HashTable(int table_size, std::vector<HashEntry*> data)
{
	default_a = rand() % (p-1) + 1;
	default_b = rand() % (p-1) + 1;
	this->TABLE_SIZE = table_size;
	rows.resize(TABLE_SIZE);
	std::vector<std::vector<HashEntry*>> initial_table = findInitialTable(data);
	for (int i = 0; i < TABLE_SIZE; i++) {
		//no data for this hash
		if (initial_table[i].size() == 0) rows[i].m = 0; else
			if (initial_table.size() == 1) { //only one piece of data in the initial hash table, no need to make secondary hash
				rows[i].m = 1;
				rows[i].a = 0;
				rows[i].b = 0;
				rows[i].second_hash.push_back(initial_table[i][0]);
			} else { // more than one entry in the initial hash table, make secondary hash for this row
				int a;
				int b;
				rows[i].second_hash = findSecondaryHashTable(initial_table[i], a, b); //rows[i].m = ...
				rows[i].a = a;
				rows[i].b = b;
				rows[i].m = pow(initial_table[i].size(), 2);
			}
	}
}

std::string HashTable::search(std::string key)
{
	int hash = computeHash(key, TABLE_SIZE, default_a, default_b);
	//key wasn't found
	if (rows[hash].m == 0) return "";
	else if (rows[hash].m == 1) return rows[hash].second_hash[0]->getValue(); //only one record is in table
	else {
		int second_hash = computeHash(key, rows[hash].m, rows[hash].a, rows[hash].b);
		if (rows[hash].second_hash[second_hash] != NULL) {
			if (key == rows[hash].second_hash[second_hash]->getKey())
			return rows[hash].second_hash[second_hash]->getValue();
		}
		else return "";
	}
	return "";
}

HashTable::~HashTable()
{
	rows.clear();
	rows.shrink_to_fit();
}
