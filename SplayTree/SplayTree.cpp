// SplayTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SplayTree.h"
#include "Visualisation.h"

void SplayTree::rotateLeft(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != NULL) y->left->parent = x; //betta-s new parent is x
	y->parent = x->parent;
	if (x->parent == NULL) root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void SplayTree::rotateRight(Node* y)
{
	Node* x = y->left;
	y->left = x->right;
	if (x->right != NULL) x->right->parent = y; //betta-s new parent is y
	x->parent = y->parent;
	if (y->parent == NULL) root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	x->right = y;
	y->parent = x;
}

void SplayTree::splay(Node* x)
{
	while (x->parent) {
		if (!x->parent->parent) {//zig
			if (x->parent->left == x) rotateRight(x->parent);
			else rotateLeft(x->parent);
		}
		else if (x->parent->left == x && x->parent->parent->left == x->parent) {//zig-zig
			rotateRight(x->parent->parent);
			rotateRight(x->parent);
		}
		else if (x->parent->right == x && x->parent->parent->right == x->parent) {//zig-zig
			rotateLeft(x->parent->parent);
			rotateLeft(x->parent);
		}
		else if (x->parent->left == x && x->parent->parent->right == x->parent) {//zig-zag
			rotateRight(x->parent);
			rotateLeft(x->parent);
		}
		else {//zig-zag
			rotateLeft(x->parent);
			rotateRight(x->parent);
		}
	}
}

SplayTree::SplayTree()
{
	root = NULL;
	id = 0;
	size = 0;
}

void SplayTree::insert(int data)
{
	Node* parent = NULL;
	Node* temp = root;
	id++;
	Node* new_node = new Node(data, id);
	while (temp != NULL) {
		parent = temp;
		if (new_node->data < temp->data) {
			temp = temp->left;
		}
		else { // temp->data >= new_node->data
			temp = temp->right;
		}
	}
	new_node->parent = parent;
	if (parent == NULL) root = new_node;
	else {
		if (new_node->data < parent->data)
			parent->left = new_node;
		else parent->right = new_node;
	}
	new_node->left = NULL;
	new_node->right = NULL;
	size++;
	splay(new_node);
}

Node* SplayTree::find(int data)
{
	Node* temp = root;
	while (temp != NULL) {
		if (temp->data < data) temp = temp->right;
		else if (temp->data > data) temp = temp->left;
		else {
			splay(temp);
			return temp;
		}
	}
	return NULL; //no node with data was found
}

Node* SplayTree::subtreeMin(Node* x)
{
	while (x->left) x = x->left;
	return x;
}

Node* SplayTree::subtreeMax(Node* x)
{
	while (x->right) x = x->right;
	return x;
}

void SplayTree::erase(int data)
{
	Node* x = find(data);
	if (x == NULL) return;
	splay(x);
	if (x->left == NULL) replace(x, x->right);
	else if (x->right == NULL) replace(x, x->left);
	else { //x has 2 children
		Node *y = subtreeMin(x->right);
		if (y->parent != x) {
			replace(y, y->right);
			y->right = x->right;
			y->right->parent = y;
		}
		replace(x, y);
		y->left = x->left;
		y->left->parent = y;
	}
	delete x;
	size--;
}
//replace x node with y
void SplayTree::replace(Node* x, Node* y)
{
	if (!x->parent) root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	if (y != NULL) y->parent = x->parent;
}

void SplayTree::drawTree(FILE* f)
{
	Visualisation y;
	y.bst_print_dot(root, f);
}
