#include "RedBlackTree.h"
#include "Visualisation.h"

#pragma warning(disable : 4996)

Node* RedBlackTree::getParent(Node* x)
{
	if (x == NULL) return NULL; else
	return x->parent;
}

Node* RedBlackTree::getGrandParent(Node* x)
{
	return getParent(getParent(x));
}

Node* RedBlackTree::getSibling(Node* x)
{
	Node* p = getParent(x);
	if (p != NULL) {
		if (p->left == x) return p->right;
		else return p->left;
	}
}

Node* RedBlackTree::getUncle(Node* x)
{
	Node* p = getParent(x);
	return getSibling(p);
}

void RedBlackTree::rotateLeft(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != nil) y->left->parent = x; //betta-s new parent is x
	y->parent = x->parent;
	if (x->parent == nil) root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

void RedBlackTree::rotateRight(Node* y)
{
	Node* x = y->left;
	y->left = x->right;
	if (x->right != nil) x->right->parent = y; //betta-s new parent is y
	x->parent = y->parent;
	if (y->parent == nil) root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	x->right = y;
	y->parent = x;
	x->size = y->size;
	y->size = y->left->size + y->right->size + 1;
}

void RedBlackTree::fixViolation(Node* x)
{
	if (getParent(x) == nil) {
		x->color = Color::BLACK;
	}
	else if (getParent(x)->color == Color::BLACK) {
		return; //the properties are valid
	}
	else if (getUncle(x) != nil && getUncle(x)->color == Color::RED) {
		getParent(x)->color = Color::BLACK;
		getUncle(x)->color = Color::BLACK;
		getGrandParent(x)->color = Color::RED;
		fixViolation(getGrandParent(x));
	}
	else {
		Node* p = getParent(x);
		Node* g = getGrandParent(x);
		if (x == p->right && p == g->left) {
			rotateLeft(p);
			x = x->left;
		}
		else if (x == p->left && p == g->right) {
			rotateRight(p);
			x = x->right;
		}

		p = getParent(x);
		g = getGrandParent(x);
		if (x == p->left) rotateRight(g);
		else rotateLeft(g);
		p->color = Color::BLACK;
		g->color = Color::RED;
	}
}

Node* RedBlackTree::osSelect_random(Node* x, int i)
{
	int r = x->left->size + 1;
	if (i == r) return x;
	else if (i < r) return osSelect_random(x->left, i);
	else return osSelect_random(x->right, i - r);
}

RedBlackTree::RedBlackTree()
{
	nil = new Node(0, 0, 0);
	root = nil;
	nil->color = Color::BLACK;
}

Node* RedBlackTree::osSelect(int i)
{
	return osSelect_random(root, i);
}

int RedBlackTree::osRank(Node* x)
{
	int r = x->left->size + 1;
	Node* y = x;
	while (y != root) {
		if (y == y->parent->right) r = r + y->parent->left->size + 1;
		y = y->parent;
	}
	return r;
}

void RedBlackTree::insert(int data)
{
	Node* parent = nil;
	Node* temp = root;
	id++;
	Node* new_node = new Node(data, 1, id);
	while (temp != nil) {
		parent = temp;
		parent->size++;
		if (new_node->data < temp->data) {
			temp = temp->left;
		} else { // temp->data > new_node->data
			temp = temp->right;
		}
	}
	new_node->parent = parent;
	if (parent == nil) root = new_node;
	else {
		if (new_node->data < parent->data)
			parent->left = new_node;
		else parent->right = new_node;
	}
	new_node->left = nil;
	new_node->right = nil;
	fixViolation(new_node);
}

void RedBlackTree::drawTree(FILE* f)
{
	Visualisation y;
	y.bst_print_dot(root, f);
}
