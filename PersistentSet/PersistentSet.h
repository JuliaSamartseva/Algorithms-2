#pragma once
#include <vector>
#include "RedBlackTree.h"



class PersistentSet
{
private:
	std::vector<RedBlackTree*> roots;
	Node* nil;
	Node* getParent(Node* x);
	Node* getGrandParent(Node* x);
	Node* getSibling(Node* x);
	Node* getUncle(Node* x);
	void rotateLeft(Node* x, Node* current_root);
	void rotateRight(Node* y, Node* current_root);
	void fixViolation(Node* x);
	Node* copy(Node* x);
	int id;
public:
	PersistentSet(RedBlackTree* tree) {
		roots.push_back(tree);
		nil = NULL;
		nil = tree->getNil();
		this->id = tree->getId() + 1;
	}
	void insert(int data);
	std::vector<RedBlackTree*> getRoots() { return roots; }
};

