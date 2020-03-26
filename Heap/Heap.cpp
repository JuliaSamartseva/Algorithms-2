// Heap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BinomialMinHeap.h"
#include "database.h"


int main()
{
	database db;
	db.create();
	/*db.add("Google Drive", 50);
	db.add("Google Forms", 31);
	db.add("Google Docs", 35);
	db.add("Android", 10);
	db.add("Adobe Photoshop", 20);
	db.add("Adobe Illustrator", 230);
	db.add("Adobe Design", 3);
	db.add("Adobe InDesign", 21);
	db.add("Slack Technologies", 22);
	db.add("Skype", 25);
	db.add("Windows 10", 35);
	db.add("Matlab", 60);*/
	db.close();
	db.connect();

	std::vector<std::pair<std::string, int>> result = db.get_records();
	BinomialMinHeap heap;

	std::cout << "\nInserted \n";
	for (int i = 0; i < result.size(); i++) {
		std::pair<std::string, int> record = result[i];
		heap.insert(record.second);
		std::cout << record.second << " "; 
	}

	std::cout << "\nResult in increasing order \n";
	for (int i = 0; i < result.size(); i++) {
		std::cout << heap.extractMin() << " ";
	}
}
