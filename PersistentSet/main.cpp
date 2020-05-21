// PersistentSet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PersistentSet.h"
#pragma warning(disable : 4996)

int main()
{
	RedBlackTree x;
	x.insert(5);
	x.insert(2);
	x.insert(7);
	x.insert(5);
	x.insert(5);
	x.insert(10);
	PersistentSet* set = new PersistentSet(&x);
	set->insert(12);
	std::vector<RedBlackTree*> roots = set->getRoots();
	FILE* f = fopen("output.txt", "w+b");
	roots[roots.size() - 1]->drawTree(f);
	fclose(f);
}

