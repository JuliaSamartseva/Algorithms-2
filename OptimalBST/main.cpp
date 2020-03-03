// OptimalBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include "OptimalBST.h"
#include "Visualisation.h"
#include <conio.h>

int main()
{
	//input data
	std::vector<float> p{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
	std::vector<float> q{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; 
	std::vector<int> nodes{0, 1, 2, 3, 4, 5, 6, 7, 8 , 9, 10, 11};
	OptimalBST x(p, q, nodes);
	Node* head = x.getHead();
	Visualisation y;
	FILE* f = fopen("output.txt", "w+b");
	y.bst_print_dot(head, f);
	fclose(f);
}