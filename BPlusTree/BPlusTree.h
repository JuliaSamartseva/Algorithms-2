#pragma once
#include <vector>

enum class node_type { INNER, LEAF };

struct Node {
	node_type type;
	std::vector<int> keys;
	std::vector<Node*> ptr; //pointers to down nodes
	int size;
	Node(int N) {
		keys.resize(N);
		ptr.resize(N + 1); 
	}
};

class BPlusTree
{
private:
	int N; //children number
	Node* root;

	void insertInternal(int value, Node* cursor, Node* child) {
		if (cursor->size < N)
		{
			int i = 0;
			while (value > cursor->keys[i] && i < cursor->size)
				i++;
			for (int j = cursor->size; j > i; j--)
			{
				cursor->keys[j] = cursor->keys[j - 1];
			}
			for (int j = cursor->size + 1; j > i + 1; j--)
			{
				cursor->ptr[j] = cursor->ptr[j - 1];
			}
			cursor->keys[i] = value;
			cursor->size++;
			cursor->ptr[i + 1] = child;
		}
		else
		{
			Node* newInternal = new Node(N);
			
			std::vector<int> virtualKey;
			virtualKey.resize(N + 1);
			std::vector<Node*> virtualPtr;
			virtualPtr.resize(N + 2);
			for (int i = 0; i < N; i++)
			{
				virtualKey[i] = cursor->keys[i];
			}
			for (int i = 0; i < N + 1; i++)
			{
				virtualPtr[i] = cursor->ptr[i];
			}
			int i = 0, j;
			while (value > virtualKey[i] && i < N)
				i++;
			for (int j = N + 1; j > i; j--)
			{
				virtualKey[j] = virtualKey[j - 1];
			}
			virtualKey[i] = value;
			for (int j = N + 2; j > i + 1; j--)
			{
				virtualPtr[j] = virtualPtr[j - 1];
			}
			virtualPtr[i + 1] = child;
			newInternal->type = node_type::INNER;
			cursor->size = (N + 1) / 2;
			newInternal->size = N - (N + 1) / 2;
			for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
			{
				newInternal->keys[i] = virtualKey[j];
			}
			for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
			{
				newInternal->ptr[i] = virtualPtr[j];
			}
			if (cursor == root)
			{
				Node* newRoot = new Node(N);
				newRoot->keys[0] = cursor->keys[cursor->size];
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newInternal;
				newRoot->type = node_type::INNER;
				newRoot->size = 1;
				root = newRoot;
			}
			else
			{
				insertInternal(cursor->keys[cursor->size], findParent(root, cursor), newInternal);
			}
		}
	}

	Node* findParent(Node* cursor, Node* child) {
		Node* parent = NULL;
		if (cursor->type == node_type::LEAF || (cursor->ptr[0])->type == node_type::LEAF)
		{
			return NULL;
		}
		for (int i = 0; i < cursor->size + 1; i++)
		{
			if (cursor->ptr[i] == child)
			{
				parent = cursor;
				return parent;
			}
			else
			{
				parent = findParent(cursor->ptr[i], child);
				if (parent != NULL)
					return parent;
			}
		}
		return parent;
	}
public:
	BPlusTree(int N) {
		this->N = N;
		root = NULL;
	}
	void insert(int value) {
		if (root == NULL) {
			root = new Node(N);
			root->keys[0] = value;
			root->size = 1;
			root->type = node_type::LEAF;
		}
		else {
			Node* temp = root;
			Node* parent = NULL;
			//searching for a place to insert
			while (temp->type == node_type::LEAF)
			{
				parent = temp;
				for (int i = 0; i < temp->size; i++)
				{
					if (value < temp->keys[i])
					{
						temp = temp->ptr[i];
						break;
					}
					else if (i == temp->size - 1) {
						temp = temp->ptr[i + 1]; //last pointer
						break;
					}
				}
			}
			if (temp->size < N) { //insert with no split
				int i = 0;
				//find a place in the inner node
				while (value > temp->keys[i] && i < temp->size) i++;
				//right shift
				for (int j = temp->size; j > i; j--) 
					temp->keys[j] = temp->keys[j - 1];
				
				temp->keys[i] = value;
				temp->size++;
				temp->ptr[temp->size] = temp->ptr[temp->size - 1];
				temp->ptr[temp->size - 1] = NULL;
			} else { //after finding a place to insert - the size is more
				Node* new_leaf = new Node(N);
				new_leaf->type = node_type::LEAF;
				temp->size = (N + 1) / 2; 
				new_leaf->size = N + 1 - temp->size;
				std::vector<int> arr;
				arr.resize(N + 1);
				for (int i = 0; i < N; i++)
					arr[i] = temp->keys[i];

				int i = 0;
				int j;
				while (value > arr[i] && i < N) i++;
				for (int j = N + 1; j > i; j--)
					arr[j] = arr[j - 1];
				arr[i] = value;
				temp->ptr[temp->size] = new_leaf;
				new_leaf->ptr[new_leaf->size] = temp->ptr[N];
				temp->ptr[N] = NULL;

				for (i = 0; i < temp->size; i++)
					temp->keys[i] = arr[i];
				for (i = 0, j = temp->size; i < temp->size; i++, j++)
					temp->keys[i] = arr[j];
				if (temp == root) {
					Node* new_root = new Node(N);
					new_root->keys[0] = new_leaf->keys[0];
					new_root->ptr[0] = temp;
					new_root->ptr[1] = new_leaf;
					new_root->type = node_type::INNER;
					new_root->size = 1;
					root = new_root;
				} else {
					insertInternal(temp->keys[temp->size], parent, new_leaf);
				}
				
			}
		}
	}
	void search(int value);
	Node* getRoot();
};
