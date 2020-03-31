#pragma once
#include <cstddef>
//Similar to Binomial Min Heap
// union only when extract min is called

struct Node {
	int data;
	int degree;
	bool marked;
	Node* next;
	Node* prev;
	Node* parent;
	Node* child;

	Node(int data, int degree) {
		this->data = data;
		this->degree = degree;
		parent = NULL;
		child = NULL;
		next = this;
		prev = this;
		marked = false;
	}
};

class FibonacciMinHeap
{
private:
	Node* head;

	void swap(Node* x, Node* y) {
		Node temp = *x;
		*x = *y;
		*y = temp;
	}

	void rearrangeHeap();

	Node* unionHeap(Node* heap1, Node* heap2) {
		if (heap1 == NULL) return heap2;
		if (heap2 == NULL) return heap1;
		if (heap1->data > heap2->data) swap(heap1, heap2);
		Node* an = heap1->next;
		Node* bp = heap2->prev;
		heap1->next = heap2;
		heap2->prev = heap1;
		an->prev = bp;
		bp->next = an;
		return heap1;
	}


public:
	void insert(int key) {
		Node* x = new Node(key, 0);
		head = unionHeap(head, x);
	}

	int extractMin();

	void decreaseKey(Node* x, int k);

	void deleteKey(Node* x);
};

