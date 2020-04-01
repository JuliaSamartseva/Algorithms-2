#pragma once
#include <cstddef>
#include <climits>
//Similar to Binomial Min Heap
// union only when extract min is called

struct ListNode {
	int data;
	int degree;
	bool marked;
	ListNode* next;
	ListNode* prev;
	ListNode* parent;
	ListNode* child;

	ListNode(int data, int degree) {
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
	ListNode* head;

	void swap(ListNode* x, ListNode* y) {
		ListNode temp = *x;
		*x = *y;
		*y = temp;
	}

	// O(1)
	//just merge two doubly linked lists together
	ListNode* unionHeap(ListNode* heap1, ListNode* heap2) { 
		if (heap1 == NULL) return heap2;
		if (heap2 == NULL) return heap1;
		if (heap1->data > heap2->data) {
			//swap(heap1, heap2);
			ListNode* temp = heap1;
			heap1 = heap2;
			heap2 = temp;
		}
		ListNode* an = heap1->next;
		ListNode* bp = heap2->prev;
		heap1->next = heap2;
		heap2->prev = heap1;
		an->prev = bp;
		bp->next = an;
		return heap1;
	}

	void addChild(ListNode* parent, ListNode* child) {
		child->prev = child->next = child;
		child->parent = parent;
		parent->degree++;
		parent->child = unionHeap(parent->child, child);
	}

	ListNode* cut(ListNode* heap, ListNode* n) {
		if (n->next == n) {
			n->parent->child = NULL;
		}
		else {
			n->next->prev = n->prev;
			n->prev->next = n->next;
			n->parent->child = n->next;
		}
		n->next = n->prev = n;
		n->marked = false;
		return unionHeap(heap, n);
	}
public:
	void insert(int key) {
		ListNode* x = new ListNode(key, 0);
		head = unionHeap(head, x);
	}

	ListNode* getMin() {
		return head;
	}

	int extractMin() {
		ListNode* x = head->child; 
		do {
			x->marked = false;
			x->parent = NULL;
			x = x->next;
		} while (x != head); // because it's a circular linked list

		x = head; //minimum 

		if (x->next == x) { //if the size is 1
			x = x->child;
		}
		else { //removing element from the list of the nodes
			x->next->prev = x->prev;
			x->prev->next = x->next;
			x = unionHeap(x->next, x->child); //add children to the root list
		}

		ListNode* trees[64] = { NULL };

		while (true) {
			if (trees[x->degree] != NULL) {
				ListNode* t = trees[x->degree];
				if (t == x) break;
				trees[x->degree] = NULL;
				if (x->data < t->data) {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					addChild(x, t);
				}
				else {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					if (x->next == x) {
						t->next = t->prev = t;
						addChild(t, x);
						x = t;
					}
					else {
						x->prev->next = t;
						x->next->prev = t;
						t->next = x->next;
						t->prev = x->prev;
						addChild(t, x);
						x = t;
					}
				}
				continue;
			}
			else {
				trees[x->degree] = x;
			}
			x = x->next;
		}
		ListNode* min = x;
		ListNode* start = x;
		do {
			if (x->data < min->data) min = x;
			x = x->next;
		} while (x != start);
		return min->data;
	}

	void decreaseKey(ListNode* x, int k) {
		if (x->data < k) return;
		x->data = k;
		if (x->parent) {
			if (x->data < x->parent->data) {
				head = cut(head, x);
				ListNode* parent = x->parent;
				x->parent = NULL;
				while (parent != NULL && parent->marked) {
					head = cut(head, parent);
					x = parent;
					parent = x->parent;
					x->parent = NULL;
				}
				if (parent != NULL && parent->parent != NULL) parent->marked = true;
			}
		}
		else {
			if (x->data < head->data) {
				head = x;
			}
		}
	}

	void deleteKey(ListNode* x) {
		decreaseKey(x, INT_MIN);
		extractMin();
	}
};

