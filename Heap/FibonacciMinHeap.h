#pragma once
#include <cstddef>
#include <climits>
//Similar to Binomial Min Heap
//union only when extract min is called

struct ListNode {
	int data;
	int degree;
	//it has lost a single child and a node is unmarked if it loses no children (in the decrease key/cutting)
	bool marked;
	ListNode* next;
	ListNode* prev;
	ListNode* parent;
	ListNode* child;
	const int SIZE = 64;

	ListNode(int data, int degree);
};

class FibonacciMinHeap
{
private:
	ListNode* head = NULL;
		
	// O(1)
	//just merge two doubly linked lists together
	ListNode* unionHeap(ListNode* heap1, ListNode* heap2);

	void addChild(ListNode* parent, ListNode* child);

	//used in decrease key
	//add n from tbhe child list, add it to the heap list
	ListNode* cut(ListNode* heap, ListNode* n);
public:
	// O(1)
	void insert(int key);

	//O(1)
	ListNode* getMin();

	//O(log n)
	int extractMin();

	//O(1)
	void decreaseKey(ListNode* x, int k);

	//O(log n)
	void deleteKey(ListNode* x);
};

