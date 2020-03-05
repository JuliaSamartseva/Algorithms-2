#pragma once
#include <climits>


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
};

class BinomialMinHeap
{
private: 
	Node* head;

	friend BinomialMinHeap merge_sameOrder(BinomialMinHeap &x, BinomialMinHeap &y);

	void addSubtree(BinomialMinHeap& x) {
		head->parent = x.head;
		head->sibling = x.head->child;
		x.head->child = head;
		x.head->degree++;
	}

public:

	Node* getMin() {
		Node* y = NULL;
		Node* x = head;
		int min = INT_MAX;
		while (x != NULL) {
			if (x->data < min) {
				min = x->data;
				y = x;
			}
			x = x->sibling;
		}
		return y;
	}

	int extractMin(BinomialMinHeap &H) {
		Node* x = H.getMin();
		//TODO extract min
	}

	void decreaseKey(Node* x, int k) {
		//TODO decrease key
	}

	void deleteKey(Node* x) {
		decreaseKey(x, INT_MIN);
		extractMin(*this);
	}

	friend BinomialMinHeap insert(BinomialMinHeap &H, int data) {
		BinomialMinHeap H1;
		Node* x = new Node(data, 0);
		x->parent = NULL;
		x->child = NULL;
		H1.head = x;
		BinomialMinHeap result = merge(H, H1);
		H = result;
	}

	friend BinomialMinHeap merge(BinomialMinHeap &x, BinomialMinHeap &y) {
		if (x.head->degree == y.head->degree) return merge_sameOrder(x, y);
		//TODO different order
	}
};



