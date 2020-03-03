#pragma once
#include "RedBlackTree.h"


class Visualisation
{
private:
	void bst_print_dot_null(Node* key, int nullcount, FILE* stream);
	void bst_print_dot_aux(Node* node, FILE* stream);
public:
	void bst_print_dot(Node* tree, FILE* stream);
};

