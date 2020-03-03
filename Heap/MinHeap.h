#pragma once
#include <vector>

struct MinHeap {
private:
	std::vector<int> items;
	int items_number = 0;

	//get indexes
	int getLeftChildIndex(int parentIndex) { return 2 * parentIndex + 1; }
	int getRightChildIndex(int parentIndex) { return 2 * parentIndex + 2; }
	int getParentIndex(int childIndex) { return (childIndex - 1) / 2; }
	//check if they exist
	bool hasLeftChild(int index) { return getLeftChildIndex(index) < items.size(); }
	bool hasRightChild(int index) { return getRightChildIndex(index) < items.size(); }
	bool hasParent(int index) { return getParentIndex(index) >= 0; }
	//check their values
	int leftChild(int index) { return items[getLeftChildIndex(index)]; }
	int rightChild(int index) { return items[getRightChildIndex(index)]; }
	int parent(int index) { return items[getParentIndex(index)]; }

	void swap(int indexLeft, int indexRight);

	void heapifyUp();

	void heapifyDown();

public:
	int peek();

	int poll();

	void push(int item);
};
