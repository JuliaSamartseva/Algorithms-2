// Heap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BinomialMinHeap.h"
#include "FibonacciMinHeap.h"
#include "database.h"


int main()
{
	database db;
	db.create();

	// uncomment to add the queries into the SQLite database

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
	/*BinomialMinHeap heap;

	std::cout << "\n\n~~~First test~~~ Adding queries from the database";
	std::cout << "\nInserted: \n";
	for (int i = 0; i < result.size(); i++) {
		std::pair<std::string, int> record = result[i];
		heap.insert(record.second);
		std::cout << record.second << " "; 
	}

	std::cout << "\nResult in increasing order \n";
	for (int i = 0; i < result.size(); i++) {
		std::cout << heap.extractMin() << " ";
	}

	std::cout << "\n\n~~~Second test~~~ Adding 200 random integers";
	BinomialMinHeap heap2;
	std::cout << "\nInserted: \n";
	for (int i = 0; i < 200; i++) {
		int j = rand() % 200;
		heap2.insert(j);
		std::cout << j << " ";
	}
	std::cout << "\nResult in increasing order \n";
	for (int i = 0; i < 200; i++) {
		std::cout << heap2.extractMin() << " ";
	}*/

	/* You can also delete/decrease keys by passing the Node to the functions */

	std::cout << "\n\n~~~First test Fibonacci~~~ Adding queries from the database";

	FibonacciMinHeap heap3;
	std::cout << "\nInserted: \n";
	for (int i = 0; i < result.size(); i++) {
		std::pair<std::string, int> record = result[i];
		heap3.insert(record.second);
		std::cout << record.second << " ";
	}

	std::cout << "\nResult in increasing order \n";
	for (int i = 0; i < result.size(); i++) {
		std::cout << heap3.extractMin() << " ";
	}
}
