#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef std::pair<int, int> edge;


class Graph
{
private:
	vector<vector<edge>> adjList;
	int N;
	int E;

	bool Bellman_Ford(std::vector<std::pair<int, edge>>& edges, std::vector<int>& cost, int src) {
		cost[src] = 0;
		for (int i = 1; i <= cost.size() - 1; ++i)
		{
			for (int j = 0; j < edges.size(); j++)
			{
				int u = edges[j].first;
				int v = edges[j].second.first;
				int weight = edges[j].second.second;

				if (cost[u] != INT_MAX && cost[u] + weight < cost[v])
					cost[v] = cost[u] + weight;
			}
		}

		for (int i = 0; i < edges.size(); i++) {
			int u = edges[i].first;
			int v = edges[i].second.first;
			int weight = edges[i].second.second;
			if (cost[v] > cost[u] + weight) return false;
		}

		return true;
	}

	void Dijkstra(std::vector<std::vector<int>>& cost, int src) {
		vector<int> dist;
		dist.resize(cost.size() + 1);

		vector<bool> visited;
		visited.resize(cost.size() + 1);
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
		
		for (int i = 0; i < cost.size(); i++) {
			dist[i] = INT_MAX;
			visited[i] = false;
		}

		dist[src] = 0;

		pq.push(make_pair(0, src));

		while (!pq.empty()) {
			pair<int, int> temp = pq.top();
			pq.pop();
			int node = temp.second;
			int d = temp.first;

			if (!visited[node]) {
				visited[node] = true;
				for (int v = 0; v < cost.size(); v++) {
					if (cost[node][v] != INT_MAX && dist[node] != INT_MAX
						&& dist[node] + cost[node][v] < dist[v]) {
						dist[v] = dist[node] + cost[node][v];
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}

		for (int i = 0; i < cost.size(); ++i) {
			cost[src][i] = dist[i];
		}

	}

	void outputCost(std::vector<std::vector<int>> cost) {
		cout << "\nCost table: \n";
		for (int i = 0; i < cost.size(); i++)
		{
			for (int j = 0; j < cost[i].size(); j++) {
				if (cost[i][j] != INT_MAX)
					cout << cost[i][j] << " ";
				else cout << "inf ";
			}
			cout << "\n";
		}
	}

	void initialiseCostTable(std::vector<std::vector<int>>& cost) {
		for (int i = 0; i < adjList.size(); ++i) {
			std::vector<int> help;
			for (int k = 0; k < adjList.size(); ++k) {
				help.push_back(INT_MAX);
			}
			help[i] = 0;
			for (int j = 0; j < adjList[i].size(); ++j) {
				help[adjList[i][j].first] = adjList[i][j].second;
			}
			cost.push_back(help);
		}
	}

	std::vector<std::pair<int, edge>> getEdges() {
		std::vector<std::pair<int, edge>> edges;
		for (int i = 0; i < adjList.size(); ++i) {
			for (int j = 0; j < adjList[i].size(); ++j) {
				edges.push_back(std::make_pair(i, adjList[i][j]));
			}
		}
		return edges;
	}

public:

	Graph(vector<vector<int>> input, int N)
	{
		this->N = N;
		this->E = input.size();

		adjList.resize(N);

		for (int i = 0; i < E; i++) {
			int source = input[i][0];
			int destination = input[i][1];
			int weight = input[i][2];
			edge e = std::make_pair(destination - 1, weight);
			adjList[source - 1].push_back(e);
		}
	}

	void Johnson() {
		std::vector<std::vector<int>> cost;
		/*
		cost[i][j] = 0 if i = j
				   = e[i][j] if i->j
				   = +infinity if i != j || i!->j
		*/
		initialiseCostTable(cost);

		std::vector<std::pair<int, edge>> edges = getEdges();

		//add new vertex to the graph (that is connected to all other, but with the cost 0)
		for (int i = 0; i < adjList.size(); ++i) {
			edges.push_back(std::make_pair(adjList.size(), std::make_pair(i, 0)));
		}

		std::vector<int> h;
		for (int j = 0; j <= adjList.size(); ++j) {
			h.push_back(INT_MAX);
		}

		if (!Bellman_Ford(edges, h, adjList.size())) std::cout << "\nThere is a negative cycle\n";
		else {
			//reweighting the graph using the bellman-ford calculations
			for (int i = 0; i < cost.size(); ++i) {
				for (int j = 0; j < cost[i].size(); ++j) {
					if (cost[i][j] != INT_MAX)
						cost[i][j] = cost[i][j] + h[i] - h[j];
				}
			}

			for (int i = 0; i < adjList.size(); ++i) {
				Dijkstra(cost, i);
			}

			for (int i = 0; i < cost.size(); ++i) {
				for (int j = 0; j < cost[i].size(); ++j) {
					if (cost[i][j] != INT_MAX)
						cost[i][j] = cost[i][j] + h[j] - h[i];
				}
			}
			outputCost(cost);
		}
		

	}

};




