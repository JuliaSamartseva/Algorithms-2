#include "BinomialMinHeap.h"

void BinomialMinHeap::swap(Node* x, Node* y)
{
	Node temp = *x;
	*x = *y;
	*y = temp;
}

Node* BinomialMinHeap::mergeTree(Node* x, Node* y) { //merging binomial trees
	if (x->data > y->data)
		swap(x, y);
	y->parent = x;
	y->sibling = x->child;
	x->child = y;
	x->degree++;
	return x;
}

void BinomialMinHeap::rearrangeHeap() {
	if (size <= 1) return;
	BinomialMinHeap result;
	list<Node*>::iterator iterator1, iterator2, iterator3;
	iterator1 = iterator2 = iterator3 = head.begin();

	if (size == 2) {
		iterator2 = iterator1;
		iterator2++;
		iterator3 = head.end();
	}
	else {
		iterator2++;
		iterator3 = iterator2;
		iterator3++;
	}

	while (iterator1 != head.end()) {
		if (iterator2 == head.end()) iterator1++;
		else if ((*iterator1)->degree < (*iterator2)->degree) {
			iterator1++;
			iterator2++;
			if (iterator3 != head.end()) iterator3++;
		}
		else if (iterator3 != head.end() &&
			(*iterator1)->degree == (*iterator2)->degree &&
			(*iterator3)->degree == (*iterator1)->degree) {
			iterator1++;
			iterator2++;
			iterator3++;
		}
		else if ((*iterator1)->degree == (*iterator2)->degree) {
			*iterator1 = mergeTree(*iterator1, *iterator2);
			iterator2 = head.erase(iterator2);
			size--;
			if (iterator3 != head.end()) iterator3++;
		}
	}
}

list<Node*> BinomialMinHeap::unionHeap(list<Node*> H1, list<Node*> H2) {
	list<Node*>::iterator iterator_H1 = H1.begin();
	list<Node*>::iterator iterator_H2 = H2.begin();
	list<Node*> result;
	while (iterator_H1 != H1.end() && iterator_H2 != H2.end()) {
		if ((*iterator_H1)->degree <= (*iterator_H2)->degree) {
			result.push_back(*iterator_H1);
			iterator_H1++;
		}
		else {
			result.push_back(*iterator_H2);
			iterator_H2++;
		}
	}

	while (iterator_H1 != H1.end()) {
		result.push_back(*iterator_H1);
		iterator_H1++;
	}
	while (iterator_H2 != H2.end()) {
		result.push_back(*iterator_H2);
		iterator_H2++;
	}
	return result;
}

Node* BinomialMinHeap::reverseLinkedList(Node* x) {
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

void BinomialMinHeap::swapKeys(Node* x, Node* y) {
	int temp = x->data;
	x->data = y->data;
	y->data = temp;
}

list<Node*> BinomialMinHeap::remove(Node* tree) {
	list<Node*> heap;
	Node* temp = tree->child;
	Node* lo;

	// making a binomial heap from Binomial Tree 
	while (temp)
	{
		lo = temp;
		temp = temp->sibling;
		lo->sibling = NULL;
		heap.push_front(lo);
	}
	return heap;
}

void BinomialMinHeap::insert(int key) {
	BinomialMinHeap H1;
	Node* x = new Node(key, 0);
	list<Node*> temp;
	temp.push_back(x);
	head = unionHeap(head, temp);
	rearrangeHeap();
}

Node* BinomialMinHeap::getMin() {
	list<Node*>::iterator it = head.begin();
	Node* temp = *it;
	int min = INT_MAX;
	while (it != head.end()) {
		if ((*it)->data < temp->data) temp = *it;
		it++;
	}
	return temp;
}

int BinomialMinHeap::extractMin() {
	size--;
	Node* x = getMin();
	list<Node*>::iterator it;
	list<Node*> result;
	Node* temp = getMin();
	int min = temp->data;
	it = head.begin();
	while (it != head.end()) {
		if (*it != temp) result.push_back(*it);
		it++;
	}
	list<Node*> lo = remove(temp);
	head = unionHeap(result, lo);
	rearrangeHeap();
	return min;
}

void BinomialMinHeap::decreaseKey(Node* x, int k) {
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

void BinomialMinHeap::deleteKey(Node* x) {
	decreaseKey(x, INT_MIN);
	extractMin();
}
