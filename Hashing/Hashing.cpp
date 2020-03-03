// Hashing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "database.h"
#include "OpenAddressing.h"


int main(int argc, char* argv[]) {
	const int records_number = 31;
	database h;
	h.connect();
	//creating the database and adding records to it

	/*h.delete_records();
	h.create();
	h.connect();
	h.add("Google", "Google Drive");
	h.add("Google", "Google Forms");
	h.add("Google", "Google Docs");
	h.add("Google", "Google Analytics");
	h.add("Google", "Android");
	h.add("Adobe", "Adobe Photoshop");
	h.add("Adobe", "Adobe Illustrator");
	h.add("Adobe", "Adobe Design");
	h.add("Adobe", "Adobe InDesign");
	h.add("Slack", "Slack Technologies");
	h.add("Microsoft", "Skype");
	h.add("Microsoft", "Windows 10");
	h.add("SurveyMonkies", "Wufoo");
	h.add("Mathworks", "Matlab");
	h.add("Mathworks", "Simulink");
	h.add("Hubspot", "Hubspot CRM");
	h.add("Wix", "Wix Answers");
	h.add("Wix", "Wix Bookings");
	h.add("PayPal", "PayPal");
	h.add("Freshworks", "Freshdesk");
	h.add("Freshworks", "Freshservice");
	h.add("Box", "Box Zones");
	h.add("Box", "Box Skills");
	h.add("Jet Brains", "IntelliJ IDEA");
	h.add("Atlassian", "Trello");
	h.add("Atlassian", "Jira");
	h.add("Amazon", "Amazon lambda");
	h.add("Amazon", "Amazon Elastic File System, Amazon EFS");
	h.add("Instructure", "Canvas");
	h.add("Instructure", "Bridge");*/
	h.print_data();
	h.close();

	//adding records to the hash table
	std::cout << "\n\n\n Ideal hashing:";

	std::vector<HashEntry*> data;
	for (int i = 1; i < records_number; i++) {
		data.push_back(h.get_record(i));
	}

	HashTable test(records_number, data);
	for (int i = 1; i < records_number; i++) {
		HashEntry* entry = h.get_record(i);
		std::cout << "\n Searched for " << entry->getKey();
		std::cout << " found company " << test.search(entry->getKey());
	}

	std::cout << "\n\n\n Open adressing:";

	HashMap test2;
	test2.insert(100, 50);
	test2.insert(39, 40);
	test2.insert(322, 400);
	test2.insert(21, 64);

	std::cout << "\n" << test2.search(100);
	std::cout << "\n" << test2.search(322);
	std::cout << "\n" << test2.search(39);
	std::cout << "\n" << test2.search(21);
}