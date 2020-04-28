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

	//merging binomial trees, the root is the smallest element
	Node* mergeTree(Node* x, Node* y);

	//if two binomial heaps have the same degree -> they should be merged by using function mergeTree
	//if when iterating three trees have the same degrees -> we should move them
	void rearrangeHeap();

	//just adding all of the trees to the result heap in the increasing order of the degrees
	list<Node*>unionHeap(list<Node*> H1, list<Node*> H2);

	Node* reverseLinkedList(Node* x);

	void swapKeys(Node* x, Node* y);

	list<Node*> remove(Node* tree);


public:

	//make new heap out of new key
	//then union these two heaps
	void insert(int key);

	//O(log N) (because at most log N trees)
	//just iterate through the original list of the Nodes
	Node* getMin();

	//O(log N)
	//deleting the node in the binomial heap that has the minimum key
	//this makes original heap divide into another 2 heaps, so they're merged by union function
	int extractMin();

	//O(log N)
	void decreaseKey(Node* x, int k);

	//O(log N)
	//Decrease Key to minus infinity then extract min
	void deleteKey(Node* x);
};

