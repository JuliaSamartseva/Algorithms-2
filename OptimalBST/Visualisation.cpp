#include "Visualisation.h"
#include "OptimalBST.h"

void Visualisation::bst_print_dot_null(Node* key, int nullcount, FILE* stream)
{
	fprintf(stream, "    null%d [shape=point];\n", nullcount);
	fprintf(stream, "    node%d [label=\"%d\"];\n", key->id, key->data);
	fprintf(stream, "    node%d -> null%d;\n", key->id, nullcount);
}

void Visualisation::bst_print_dot_aux(Node* node, FILE* stream)
{
	static int nullcount = 0;
	static int dotcount = 0;
	if (node->left)
	{
		fprintf(stream, "    node%d [label=\"%d\"];\n", node->id, node->data);
		fprintf(stream, "    node%d [label=\"%d\"];\n", node->left->id, node->left->data);
		fprintf(stream, "    node%d -> node%d ;\n", node->id, node->left->id);
		bst_print_dot_aux(node->left, stream);
	}
	else
		bst_print_dot_null(node, nullcount++, stream);

	if (node->right)
	{
		fprintf(stream, "    node%d [label=\"%d\"];\n", node->id, node->data);
		fprintf(stream, "    node%d [label=\"%d\"];\n", node->right->id, node->right->data);
		fprintf(stream, "    node%d  -> node%d;\n", node->id, node->right->id);
		bst_print_dot_aux(node->right, stream);
	}
	else
		bst_print_dot_null(node, nullcount++, stream);
}

void Visualisation::bst_print_dot(Node* tree, FILE* stream)
{
	fprintf(stream, "digraph BST {\n");
	fprintf(stream, "    node [fontname=\"Arial\"];\n");

	if (!tree)
		fprintf(stream, "\n");
	else if (!tree->right && !tree->left) {
		fprintf(stream, "    %d;\n", tree->data);
	}
	else
		bst_print_dot_aux(tree, stream);

	fprintf(stream, "}\n");
}