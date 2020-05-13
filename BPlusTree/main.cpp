// BPlusTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BPlusTree.h"

int main()
{
	std::cout << "Hello World!\n";
	BPlusTree tree(3);
	tree.insert(5);
	tree.insert(12);
	tree.insert(23);
	tree.insert(3);
	tree.insert(4);
	tree.insert(223);
	tree.insert(52);
	tree.insert(522);
}