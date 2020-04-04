// Heap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BinomialMinHeap.h"
#include "FibonacciMinHeap.h"
#include "database.h"

void firstTestBinomial(std::vector<std::pair<std::string, int>>& result);
void secondTestBinomial(std::vector<std::pair<std::string, int>>& result);
void firstTestFibonacci(std::vector<std::pair<std::string, int>>& result);
void secondTestFibonacci(std::vector<std::pair<std::string, int>>& result);


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
	firstTestBinomial(result);
	secondTestBinomial(result);
	firstTestFibonacci(result);
	secondTestBinomial(result);
}

void firstTestBinomial(std::vector<std::pair<std::string, int>>& result) {
	std::cout << "\n\n~~~First test Binomial Heap~~~ Adding queries from the database";

	BinomialMinHeap heap;
	std::cout << "\nInserted: \n";
	for (int i = 0; i < result.size(); i++) {
		std::pair<std::string, int> record = result[i];
		heap.insert(record.second);
		std::cout << record.second << " ";
	}

	std::cout << "\nResult in increasing order: \n";
	for (int i = 0; i < result.size(); i++) {
		std::cout << heap.extractMin() << " ";
	}
}

void secondTestBinomial(std::vector<std::pair<std::string, int>>& result) {
	std::cout << "\n\n~~~Second test Binomial Heap~~~ Adding 200 random integers";

	BinomialMinHeap heap;
	std::cout << "\nInserted: \n";
	for (int i = 0; i < 200; i++) {
		int j = rand() % 200;
		heap.insert(j);
		std::cout << j << " ";
	}
	std::cout << "\nResult in increasing order: \n";
	for (int i = 0; i < 200; i++) {
		std::cout << heap.extractMin() << " ";
	}
}


void firstTestFibonacci(std::vector<std::pair<std::string, int>>& result) {
	std::cout << "\n\n~~~First test Fibonacci Heap~~~ Adding queries from the database";

	FibonacciMinHeap heap;
	std::cout << "\nInserted: \n";
	for (int i = 0; i < result.size(); i++) {
		std::pair<std::string, int> record = result[i];
		heap.insert(record.second);
		std::cout << record.second << " ";
	}
	std::cout << "\nResult in increasing order: \n";
	for (int i = 0; i < result.size(); i++) {
		std::cout << heap.extractMin() << " ";
	}
}

void secondTestFibonacci(std::vector<std::pair<std::string, int>>&result) {
	std::cout << "\n\n~~~Second test Fibonacci Heap~~~ Adding 200 random integers";

	FibonacciMinHeap heap;
	std::cout << "\nInserted: \n";
	for (int i = 0; i < 200; i++) {
		int j = rand() % 200;
		heap.insert(j);
		std::cout << j << " ";
	}
	std::cout << "\nResult in increasing order: \n";
	for (int i = 0; i < 200; i++) {
		std::cout << heap.extractMin() << " ";
	}
}

