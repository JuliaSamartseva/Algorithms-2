#pragma once
#include <iostream>

struct Node {
	int data;
	Node *left, *right, *parent;
	int id;
	Node(int data, int id) {
		this->data = data;
		this->id = id;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
};


class SplayTree
{
private:
	Node* root;
	int id;
	int size;
	void rotateLeft(Node* x);
	void rotateRight(Node* y);
	void splay(Node* x);
public:
	SplayTree();
	Node* getRoot() { return root; }
	void insert(int data); //usual BST insertion with splay operation in the end
	Node* find(int data); //usual BST find
	Node* subtreeMin(Node* x); //the leftmost node
	Node* subtreeMax(Node* x); // the rightmost node
	void erase(int data);
	void replace(Node* x, Node* y);
	void drawTree(FILE* f);
};

