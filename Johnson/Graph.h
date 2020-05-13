#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

enum class graphType { undirected, directed };

struct Node {
	int vertex;
	int weight;
	Node* next;
	Node(int x) {
		this->vertex = x;
	}
};


class Graph
{
private:
	void insertToList(int source, int destination, int weight) {
		Node* p = adjList[source];

		while (p->vertex != destination && p->next != NULL)
			p = p->next;

		Node* new_node = new Node(destination);
		new_node->weight = weight;
		new_node->next = NULL;
		p->next = new_node;
		E++;
	}

public:
	vector<Node*> adjList;
    int N;
	int E;
	graphType type;

	Graph(int N, graphType type)
	{
		adjList.resize(N);
		this->type = type;
        this->N = N;
		this->E = 0;
	}

	void insert(int source, int destination, int weight) {
		if (source > N || source < 0 || destination > N || destination < 0)
			return;
		if (type == graphType::undirected) insertToList(destination, source, weight);

		insertToList(source, destination, weight);
	}

};



