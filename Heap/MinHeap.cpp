#include "MinHeap.h"
void MinHeap::swap(int indexLeft, int indexRight) {
	int temp = items[indexLeft];
	items[indexLeft] = items[indexRight];
	items[indexRight] = temp;
}

void MinHeap::heapifyUp() {
	int index = items.size() - 1;
	while (hasParent(index) && parent(index) > items[index]) {
		swap(getParentIndex(index), index);
		index = getParentIndex(index);
	}
}

void MinHeap::heapifyDown() {
	int index = 0;
	while (hasLeftChild(index)) {
		int smallerChildIndex = getLeftChildIndex(index);
		if (hasRightChild(index) && leftChild(index) > rightChild(index))
			smallerChildIndex = getRightChildIndex(index); //smaller of the left and the right child
		if (items[index] < items[smallerChildIndex]) break; else {
			swap(index, smallerChildIndex);
			index = smallerChildIndex;
		}
	}
}

int MinHeap::peek() {
	return items[0];
}

int MinHeap::poll() { // remove the first element (min element) from the Heap
	int item = items[0];
	items[0] = items[items.size() - 1];
	heapifyDown();
	return item;
}

void MinHeap::push(int item) {
	items.push_back(item);
	heapifyUp();
}
