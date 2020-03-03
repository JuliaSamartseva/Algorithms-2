#pragma once
#include <vector>


enum class Color {
	RED,
	BLACK
};

struct Node {
	int data;
	Node* left, * right, * parent;
	Color color;
	int size;
	int id;
	Node(int data, int size, int id) {
		this->data = data;
		this->size = size;
		this->id = id;
		left = NULL;
		right = NULL;
		parent = NULL;
		color = Color::RED;
	}
};

class PersistentSet
{
private:
	Node* root;
	Node* nil;
	int id = 0;
	Node* getParent(Node* x);
	Node* getGrandParent(Node* x);
	Node* getSibling(Node* x);
	Node* getUncle(Node* x);
	void rotateLeft(Node* x);
	void rotateRight(Node* y);
	void fixViolation(Node* x);
public:
};

