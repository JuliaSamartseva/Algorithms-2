#pragma once
#include <cstddef>
#include <climits>
#include <list>
using std::list;


struct Node {
	Node* parent;
	int data;
	int degree;
	Node* child;
	Node* sibling;

	Node(int data, int degree) {
		this->data = data;
		this->degree = degree;
		parent = NULL;
		child = NULL;
		sibling = NULL;
	}

	void insertTree(Node* x) {
		sibling = x;
	}
};


class BinomialMinHeap
{
private:
	std::list<Node*> head;
	int size = 0;

	void swap(Node* x, Node* y);

	Node* mergeTree(Node* x, Node* y);

	void rearrangeHeap();

	list<Node*>unionHeap(list<Node*> H1, list<Node*> H2);

	Node* reverseLinkedList(Node* x);

	void swapKeys(Node* x, Node* y);

	list<Node*> remove(Node* tree);


public:

	void insert(int key);

	Node* getMin();

	int extractMin();

	void decreaseKey(Node* x, int k);

	void deleteKey(Node* x);
};

