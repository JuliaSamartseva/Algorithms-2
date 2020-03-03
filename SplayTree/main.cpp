// SplayTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SplayTree.h"
#include "database.h"
#pragma warning(disable : 4996)

int main()
{
	database db;
	db.create();
	db.add("Google Drive", 50);
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
	db.add("Matlab", 60);
	db.close();
	db.connect();
	std::vector<std::pair<std::string, int>> result = db.get_records();
	db.close();
	SplayTree x;
	for (int i = 0; i < result.size(); i++)
		x.insert(result[i].second);
	x.find(10);
	FILE* f = fopen("output.txt", "w+b");
	x.drawTree(f);
	fclose(f);
}
