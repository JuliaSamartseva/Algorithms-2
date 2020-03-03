#pragma once
#include <vector>

enum class node_type {INNER, LEAF};

struct Node {
	int keys_number;
	node_type type;
	std::vector<int> keys;
	std::vector<int> values;
};

struct LeafNode :  Node {

};

struct InnerNode : Node {

};

class BPlusTree
{
	int N; //children number
	Node* root;
	
	BPlusTree (int N) {
		this->N = N;
	}
};

