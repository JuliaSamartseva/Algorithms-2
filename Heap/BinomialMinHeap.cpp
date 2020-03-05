#include "BinomialMinHeap.h"

BinomialMinHeap merge_sameOrder(BinomialMinHeap &x, BinomialMinHeap &y)
{
	if (x.head->data <= y.head->data) {
		x.addSubtree(y);
		return x;
	}
	else {
		y.addSubtree(x);
		return y;
	}
}
