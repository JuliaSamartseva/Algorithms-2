// OrderStatistics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RedBlackTree.h"
#pragma warning(disable : 4996)

int main()
{
	RedBlackTree x;
	x.insert(26);
	x.insert(17);
	x.insert(41);
	x.insert(47);
	x.insert(30);
	x.insert(38);
	x.insert(28);
	x.insert(35);
	x.insert(39);
	x.insert(10);
	x.insert(7);
	x.insert(7);
	x.insert(12);
	x.insert(3);
	x.insert(16);
	x.insert(14);
	x.insert(21);
	x.insert(19);
	x.insert(21);
	x.insert(20);
	for (int i = 1; i < 11; i++) {
		Node* y = x.osSelect(i);
		std::cout << y->data << " ";
		std::cout << x.osRank(y) << "\n";
	}

	FILE* f = fopen("output.txt", "w+b");
	x.drawTree(f);
	fclose(f);
}

