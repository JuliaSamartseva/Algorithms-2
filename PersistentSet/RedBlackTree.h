#pragma once
#include <string>

enum class Color {
	RED,
	BLACK
};

struct Node {
	int data;
	Node *left, *right, * parent;
	Color color;
	int id;
	Node(int data, int id, Color color) {
		this->data = data;
		this->id = id;
		left = NULL;
		right = NULL;
		parent = NULL;
		this->color = color;
	}
	Node(int data, int id) {
		this->data = data;
		this->id = id;
		left = NULL;
		right = NULL;
		parent = NULL;
		color = Color::RED;
	}
};


class RedBlackTree
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
	RedBlackTree();
	RedBlackTree(Node* x, Node* nil);
	void insert(int data);
	Node* getNil();
	Node* getRoot();
	void drawTree(FILE* f);
	int getId() { return id; };
};

