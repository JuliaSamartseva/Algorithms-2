#include "OpenAddressing.h"

HashMap::HashMap()
{
	table = new HashEntry_del* [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = NULL;
}

int HashMap::search(int key)
{
	int hash = key % TABLE_SIZE;
	while ((table[hash]->getIsDeleted() == true) ||
		(table[hash] != NULL && table[hash]->getKey() != key)) hash = (hash + 1) % TABLE_SIZE;
	if (table[hash] == NULL) return -1;
	else return table[hash]->getValue();
}

void HashMap::insert(int key, int value)
{
	int hash = key % TABLE_SIZE;
	while (table[hash] != NULL) hash = (hash + 1) % TABLE_SIZE;
	table[hash] = new HashEntry_del(key, value);
}

void HashMap::deleteKey(int key)
{
	int hash = key % TABLE_SIZE;
	while ((table[hash]->getIsDeleted() == true) ||
		(table[hash] != NULL && table[hash]->getKey() != key)) hash = (hash + 1) % TABLE_SIZE;
	if (table[hash] != NULL) table[hash]->setIsDeleted(true); //if the key is found - set isDeleted flag to true
}

HashMap::~HashMap()
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i] != NULL) delete table[i];
	}
	delete[] table;
}
