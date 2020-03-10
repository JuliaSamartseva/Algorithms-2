#pragma once
#include <cstddef>
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
	Node* head = NULL;
	int size = 0;

	void swap(Node* x, Node* y) {
		Node* temp = x;
		x = y;
		y = temp;
	}

	Node* mergeTree(Node* x, Node* y) { //merging binomial trees
		if (x->data > y->data)
			swap(x, y);
		y->parent = x;
		y->sibling = x->child;
		x->child = y;
		x->degree++;
		return x;
	}

	void insertTree(Node* x, Node* y) {
		if (x != NULL) {
			x->sibling = y;
			x = x->sibling;
		}
		else x = y;
	}

	void rearrangeHeap() {
		if (size <= 1) return;
		BinomialMinHeap result;
		Node* iterator1 = head;
		Node* iterator2 = head;
		Node* iterator3 = head;

		if (size == 2) {
			if (head->degree < head->sibling->degree) return;
			else if (head->degree == head->sibling->degree) {
				head = mergeTree(head, head->sibling);
				head->sibling = NULL;
				size = 1;
			}
			else {
				Node* temp = head;
				head = head->sibling;
				head->sibling = temp;
			}
			return;
		}
		else {
			iterator2 = iterator1->sibling;
			iterator3 = iterator2->sibling;
		}
		while (iterator1->sibling != NULL) {
			if (iterator2->sibling == NULL) iterator1 = iterator1->sibling;
			else if (iterator1->degree < iterator2->degree) {
				iterator1 = iterator1->sibling;
				iterator2 = iterator2->sibling;
				if (iterator3->sibling != NULL) iterator3 = iterator3->sibling;
			}
			else if (iterator3->sibling != NULL && iterator1->degree == iterator2->degree && iterator3->degree == iterator1->degree) {
				iterator1 = iterator1->sibling;
				iterator2 = iterator2->sibling;
				iterator3 = iterator3->sibling;
			}
			else if (iterator1->degree == iterator2->degree) {
				iterator1 = mergeTree(iterator1, iterator2);
				Node* temp = iterator2;
				iterator2 = iterator2->sibling;
				delete temp;
				size--;
				if (iterator3->sibling != NULL) iterator3 = iterator3->sibling;
			}
		}
	}

	BinomialMinHeap unionHeap(BinomialMinHeap& H1, BinomialMinHeap& H2) {
		BinomialMinHeap result;
		Node* iterator_H1 = H1.head;
		Node* iterator_H2 = H2.head;
		Node* iterator_result = result.head;
		while (iterator_H1 != NULL && iterator_H2 != NULL) {
			if (iterator_H1->degree <= iterator_H2->degree) {
				insertTree(iterator_result, iterator_H1);
				iterator_H1 = iterator_H1->sibling;
			}
			else {
				insertTree(iterator_result, iterator_H2);
				iterator_H2 = iterator_H2->sibling;
			}
		}

		while (iterator_H1 != NULL) {
			insertTree(iterator_result, iterator_H1);
			iterator_H1 = iterator_H1->sibling;
		}
		while (iterator_H2 != NULL) {
			insertTree(iterator_result, iterator_H2);
			iterator_H2 = iterator_H2->sibling;
		}
		return result;
	}

	Node* reverseLinkedList(Node* x) {
		Node* current = x;
		Node* next;
		Node* prev = NULL;
		while (current != NULL) {
			next = current->sibling;
			current->sibling = prev;
			prev = current;
			current = next;
		}
		Node* result = prev;
		return result;
	}

	void swapKeys(Node* x, Node* y) {
		int temp = x->data;
		x->data = y->data;
		y->data = temp;
	}


public:
	void insert(int key) {
		BinomialMinHeap H1;
		size++;
		Node* x = new Node(key, 0);
		x->parent = NULL;
		x->child = NULL;
		H1.head = x;
		BinomialMinHeap result = unionHeap(*this, H1);
		rearrangeHeap();
	}

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

	int extractMin() {
		size--;
		Node* x = getMin();
		Node* temp = x->child;
		BinomialMinHeap H1;
		H1.head = reverseLinkedList(temp);
		unionHeap(*this, H1); //maybe mistake
		return x->data;
		delete[] x;
	}

	void decreaseKey(Node* x, int k) {
		if (k > x->data) return;
		x->data = k;
		Node* y = x;
		Node* z = y->parent;
		while (z != NULL && y->data < z->data) {
			swapKeys(y, z);
			y = z;
			z = y->parent;
		}
	}

	void deleteKey(Node* x) {
		decreaseKey(x, INT_MIN);
		extractMin();
	}
};

