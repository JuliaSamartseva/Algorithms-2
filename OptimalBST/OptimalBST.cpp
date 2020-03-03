#include "OptimalBST.h"
#include <vector>
#include <iostream>

int Node::idU = 0;

Node* OptimalBST::findHead(int i, int j)
{
	Node* x;
	if (i == j) x = NULL;
	else {
		x = new Node(nodes[root[i][j]]);
		x->left = findHead(i, root[i][j] - 1);
		x->right = findHead(root[i][j], j);
	}
	return x;
}

OptimalBST::OptimalBST(std::vector<float> p, std::vector<float> q, std::vector<int> nodes)
{
	//initialising varibles
	keysNumber = nodes.size();
	keysNumber;
	cost.resize(keysNumber);
	root.resize(keysNumber);
	weight.resize(keysNumber);
	this->nodes = nodes;
	for (int i = 0; i < keysNumber; i++) {
		cost[i].resize(keysNumber);
		root[i].resize(keysNumber);
		weight[i].resize(keysNumber);
	}
	//construct weight matrix
	for (int i = 0; i < keysNumber; i++) {
		weight[i][i] = q[i];
		for (int j = i + 1; j < keysNumber; j++)
			weight[i][j] = weight[i][j - 1] + p[j] + q[j];
	}

	// part of the cost matrix
	for (int i = 0; i < keysNumber; i++) cost[i][i] = weight[i][i];

	for (int i = 0; i < keysNumber - 1; i++) {
		int j = i + 1;
		cost[i][j] = cost[i][i] + cost[j][j] + weight[i][j];
		root[i][j] = j;
	}

	for (int h = 2; h < keysNumber; h++) 
		for (int i = 0; i < keysNumber - h; i++) {
			int j = i + h;
			int m = root[i][j - 1];
			int min = cost[i][m - 1] + cost[m][j];
			for (int k = m + 1; k <= root[i + 1][j]; k++) {
				int x = cost[i][k - 1] + cost[k][j];
				if (x < min) {
					m = k;
					min = x;
				}
			}
			cost[i][j] = weight[i][j] + min;
			root[i][j] = m;
		}
	

	for (int i = 0; i < keysNumber; i++) {
		for (int j = 0; j < keysNumber; j++)
			std::cout << weight[i][j] << " ";
		std::cout << "\n";
	}

	std::cout << "\n\n";
	for (int i = 0; i < keysNumber; i++) {
		for (int j = 0; j < keysNumber; j++)
			std::cout << cost[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n\n";
	for (int i = 0; i < keysNumber; i++) {
		for (int j = 0; j < keysNumber; j++)
			std::cout << root[i][j] << " ";
		std::cout << "\n";
	}
	head = findHead(0, nodes.size()-1);
}

