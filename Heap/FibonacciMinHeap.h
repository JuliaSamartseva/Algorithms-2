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

	ListNode(int data, int degree);
};

class FibonacciMinHeap
{
private:
	ListNode* head = NULL;

	void swap(ListNode* x, ListNode* y);

	// O(1)
	//just merge two doubly linked lists together
	ListNode* unionHeap(ListNode* heap1, ListNode* heap2);

	void addChild(ListNode* parent, ListNode* child);

	ListNode* cut(ListNode* heap, ListNode* n);
public:
	void insert(int key);

	ListNode* getMin();

	int extractMin();

	void decreaseKey(ListNode* x, int k);

	void deleteKey(ListNode* x);
};

