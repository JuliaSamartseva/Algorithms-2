#include "PersistentSet.h"

Node* PersistentSet::getParent(Node* x)
{
	if (x == NULL) return NULL; else
		return x->parent;
}

Node* PersistentSet::getGrandParent(Node* x)
{
	return getParent(getParent(x));
}

Node* PersistentSet::getSibling(Node* x)
{
	Node* p = getParent(x);
	if (p != NULL) {
		if (p->left == x) return p->right;
		else return p->left;
	}
}

Node* PersistentSet::getUncle(Node* x)
{
	Node* p = getParent(x);
	return getSibling(p);
}

void PersistentSet::rotateLeft(Node* x, Node* current_root)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != nil) y->left->parent = x; //betta-s new parent is x
	y->parent = x->parent;
	if (x->parent == nil) current_root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void PersistentSet::rotateRight(Node* y, Node* current_root)
{
	Node* x = y->left;
	y->left = x->right;
	if (x->right != nil) x->right->parent = y; //betta-s new parent is y
	x->parent = y->parent;
	if (y->parent == nil) current_root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	x->right = y;
	y->parent = x;
}

void PersistentSet::fixViolation(Node* x)
{
	//if (getParent(x) == nil) {
	//	x->color = Color::BLACK;
	//}
	//else if (getParent(x)->color == Color::BLACK) {
	//	return; 
	//	//the properties are valid
	//}
	//else if (getUncle(x) != nil && getUncle(x)->color == Color::RED) {

	//	getParent(x)->color = Color::BLACK;
	//	getUncle(x)->color = Color::BLACK;
	//	getGrandParent(x)->color = Color::RED;
	//	fixViolation(getGrandParent(x));
	//}
	//else {
	//	Node* p = getParent(x);
	//	Node* g = getGrandParent(x);
	//	if (x == p->right && p == g->left) {
	//		rotateLeft(p);
	//		x = x->left;
	//	}
	//	else if (x == p->left && p == g->right) {
	//		rotateRight(p);
	//		x = x->right;
	//	}

	//	p = getParent(x);
	//	g = getGrandParent(x);
	//	if (x == p->left) rotateRight(g);
	//	else rotateLeft(g);
	//	p->color = Color::BLACK;
	//	g->color = Color::RED;
	//}
}

Node* PersistentSet::copy(Node* x)
{
	Node* new_node = new Node(x->data, x->id, x->color);
	new_node->left = x->left;
	new_node->right = x->right;
	new_node->id = id++;
	return new_node;
}

void PersistentSet::insert(int data)
{
	Node* parent = nil;
	Node* temp = roots[roots.size() - 1]->getRoot();
	Node* new_head = copy(temp);
	//id++; TODO change

	int id = 5;
	Node* new_node = new Node(data, id);
	roots.push_back(new RedBlackTree(new_head, nil));

	Node* new_parent = nil;
	while (temp != nil) {
		parent = temp;
		new_parent = new_head;
		if (new_node->data < temp->data) {
			temp = temp->left;
			Node* new_left = copy(temp);
			new_head->left = new_left;
			new_left->parent = new_head;
			new_head = new_head->left;
		}
		else { // temp->data > new_node->data
			temp = temp->right;
			Node* new_right = copy(temp);
			new_head->right = new_right;
			new_right->parent = new_head;
			new_head = new_head->right;
		}
	}

	new_node->parent = new_parent;


	if (new_node->data < parent->data) {
		new_parent->left = new_node;
	} else {
		new_parent->right = new_node;
	}

	new_node->left = nil;
	new_node->right = nil;

	//fixViolation(new_node);
}
