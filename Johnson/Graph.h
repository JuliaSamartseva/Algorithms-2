#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

typedef std::pair<int, int> edge;


class Graph
{
private:
	vector<vector<edge>> adjList;
	int N;
	int E;

	bool Bellman_Ford(std::vector<std::pair<int, edge>>& edges, std::vector<int>& cost, int src);

	void Dijkstra(std::vector<std::vector<int>>& cost, int src);

	void outputCost(std::vector<std::vector<int>> cost);

	void initialiseCostTable(std::vector<std::vector<int>>& cost);

	std::vector<std::pair<int, edge>> getEdges();

public:

	Graph(vector<vector<int>> input, int N);
	Graph(std::fstream& file);

	void Johnson();

};




