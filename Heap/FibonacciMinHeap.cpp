#include "FibonacciMinHeap.h"

ListNode::ListNode(int data, int degree) {
	this->data = data;
	this->degree = degree;
	parent = NULL;
	child = NULL;
	//as it is a circular linked list
	next = this;
	prev = this;
	marked = false;
}

void FibonacciMinHeap::swap(ListNode* x, ListNode* y) {
	ListNode temp = *x;
	*x = *y;
	*y = temp;
}

// O(1)
//just merge two doubly linked lists together

ListNode* FibonacciMinHeap::unionHeap(ListNode* heap1, ListNode* heap2) {
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

void FibonacciMinHeap::addChild(ListNode* parent, ListNode* child) {
	child->prev = child->next = child;
	child->parent = parent;
	parent->degree++;
	parent->child = unionHeap(parent->child, child);
}

ListNode* FibonacciMinHeap::cut(ListNode* heap, ListNode* n) {
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

void FibonacciMinHeap::insert(int key) {
	ListNode* x = new ListNode(key, 0);
	head = unionHeap(head, x);
}

ListNode* FibonacciMinHeap::getMin() {
	return head;
}

int FibonacciMinHeap::extractMin() {
	ListNode* x = head->child;
	if (x) {
		do {
			x->marked = false;
			x->parent = NULL;
			x = x->next;
		} while (x != head->child); // because it's a circular linked list
	}

	ListNode* minimum = head; //minimum 
	int min_value = head->data;

	x = head;

	if (x->next == x) { //if the size is 1
		x = x->child;
	}
	else { //removing element from the list of the nodes
		x->next->prev = x->prev;
		x->prev->next = x->next;
		x = unionHeap(x->next, x->child); //add children to the root list
	}

	ListNode* trees[64] = { NULL };
	if (x != NULL) {
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

	}

	head = x;
	delete minimum; //deleting the node
	return min_value;
}

void FibonacciMinHeap::decreaseKey(ListNode* x, int k) {
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

void FibonacciMinHeap::deleteKey(ListNode* x) {
	decreaseKey(x, INT_MIN);
	extractMin();
}
