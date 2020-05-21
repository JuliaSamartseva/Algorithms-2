#include "Visualisation.h"
#include "RedBlackTree.h"

void Visualisation::bst_print_dot_null(Node* key, int nullcount, FILE* stream)
{
	fprintf(stream, "    null%d [shape=point];\n", nullcount);
	fprintf(stream, "    %d -> null%d;\n", key->data, nullcount);
}

void Visualisation::bst_print_dot_aux(Node* node, FILE* stream)
{
	static int nullcount = 0;
	static int dotcount = 0;
	if (node->left)
	{
		if (node->color == Color::RED)
			fprintf(stream, "    node%d [style=filled, fillcolor=red, shape=record, label=\"{%d}\"]", node->id, node->data);
		else fprintf(stream, "    node%d [style=filled, fillcolor=grey, shape=record, label=\"{%d}\"]", node->id, node->data);

		if (node->left->color == Color::RED)
			fprintf(stream, "    node%d [style=filled, fillcolor=red, shape=record, label=\"{%d}\"]", node->left->id, node->left->data);
		else fprintf(stream, "    node%d [style=filled, fillcolor=grey, shape=record, label=\"{%d}\"]", node->left->id, node->left->data);

		fprintf(stream, "    node%d -> node%d;\n", node->id, node->left->id);
		bst_print_dot_aux(node->left, stream);
	}
	if (node->right)
	{
		if (node->color == Color::RED)
			fprintf(stream, "    node%d [style=filled, fillcolor=red, shape=record, label=\"{%d}\"]", node->id, node->data);
		else fprintf(stream, "    node%d [style=filled, fillcolor=grey, shape=record, label=\"{%d}\"]", node->id, node->data);

		if (node->right->color == Color::RED)
			fprintf(stream, "    node%d [style=filled, fillcolor=red, shape=record, label=\"{%d}\"]", node->right->id, node->right->data);
		else fprintf(stream, "    node%d [style=filled, fillcolor=grey, shape=record, label=\"{%d}\"]", node->right->id, node->right->data);

		fprintf(stream, "    node%d -> node%d;\n", node->id, node->right->id);
		bst_print_dot_aux(node->right, stream);
	}
}

void Visualisation::bst_print_dot(Node* tree, FILE* stream)
{
	fprintf(stream, "digraph BST {\n");
	fprintf(stream, "    node [fontname=\"Arial\"];\n");

	if (!tree)
		fprintf(stream, "\n");
	else if (!tree->right && !tree->left) {
		fprintf(stream, "    %d;\n", tree->data);
		//fprintf(stream, "    \"%s\";\n", tree->info.c_str());
	}
	else
		bst_print_dot_aux(tree, stream);
	fprintf(stream, "}\n");
}
