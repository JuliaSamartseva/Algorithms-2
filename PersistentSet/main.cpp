// PersistentSet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PersistentSet.h"
#pragma warning(disable : 4996)

void test1() {
	RedBlackTree x;
	x.insert(5);

	PersistentSet* set = new PersistentSet(&x);
	set->insert(1);
	set->insert(3);
	set->insert(4);
	set->insert(6);
	set->insert(12);

	std::vector<RedBlackTree*> roots = set->getRoots();
	FILE* f = fopen("output.txt", "w+b");
	roots[4]->drawTree(f);
	fclose(f);
}

void test2() {
	RedBlackTree x;
	x.insert(5);
	x.insert(1);
	x.insert(3);
	x.insert(4);
	x.insert(6);
	x.insert(12);
	PersistentSet* set = new PersistentSet(&x);
	set->insert(6);
	set->insert(7);
	set->insert(2);
	set->insert(15);
	set->insert(25);

	std::vector<RedBlackTree*> roots = set->getRoots();
	FILE* f = fopen("output.txt", "w+b");
	roots[4]->drawTree(f);
	fclose(f);
}

void test3() {
	RedBlackTree x;
	for (int i = 1; i < 20; i++)
		x.insert(i);
	PersistentSet* set = new PersistentSet(&x);
	for (int i = 20; i < 40; i++)
		set->insert(i);

	std::vector<RedBlackTree*> roots = set->getRoots();
	FILE* f = fopen("output.txt", "w+b");
	roots[roots.size()-1]->drawTree(f);
	fclose(f);
}

int main()
{
	test3();
}

