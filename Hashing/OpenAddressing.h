#include <iostream>
// OPEN-ADDRESSING HASHING WITH LINEAR PROBING

class HashEntry_del {
private:
	int key;
	//value - additional information for the certain key
	int value;
	bool isDeleted;
public:
	HashEntry_del(int key, int value) {
		this->key = key;
		this->value = value;
		this->isDeleted = false;
	}
	int getKey() { return key; }
	int getValue() { return value; }
	bool getIsDeleted() { return isDeleted; }
	void setIsDeleted(bool deleted) { this->isDeleted = true; }
};

class HashMap {
private:
	HashEntry_del** table;
	const int TABLE_SIZE = 128;
public:
	HashMap();
	int search(int key);
	void insert(int key, int value);
	void deleteKey(int key);
	~HashMap();
};


