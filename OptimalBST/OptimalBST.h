#pragma once
#include <cstddef>
#include <vector>


struct Node {
	int data;
	static int idU;
	int id;
	Node *left;
	Node *right;
	Node(int data) { this->data = data; left = NULL; right = NULL; id = idU++; }
};
class OptimalBST
{
private:
	Node* head;
	std::vector<std::vector<float>> cost;
	std::vector<std::vector<float>> root;
	std::vector<std::vector<float>> weight;
	std::vector<int> nodes;
	int keysNumber;
	Node* findHead(int i, int j);
public: 
	OptimalBST(std::vector<float> p, std::vector<float> q, std::vector<int> nodes);
	Node* getHead() { return head; };
};

