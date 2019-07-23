#include <iostream>
#include <vector>
#include <queue>

class HeapNode
{
public:
	int vertex;
	int weight;

	bool operator()(const HeapNode& a, const HeapNode& b) const
	{
		return a.weight > b.weight;
	}
};

class Edge
{
public:
	int src;
	int dest;
	int weight;
};

class DirectedGraph
{
private:
	std::vector<std::vector<Edge>> adj;
	int nodes;

private:
	void print(int curr, const std::vector<int>& parent)
	{
		if (curr == -1)
		{
			return;
		}

		print(parent[curr], parent);
		std::cout << curr << "  -> ";
	}

public:
	DirectedGraph(int num, const std::vector<Edge>& edges)
		: nodes(num)
	{
		adj.resize(nodes);

		for (auto iter : edges)
		{
			adj[iter.src].push_back(iter);
		}
	}

	void dijkstra(int src)
	{
		std::vector<bool> visited(nodes, false);
		std::vector<int> dist(nodes, std::numeric_limits<int>::max());
		std::vector<int> parent(nodes, -1);
		std::priority_queue<HeapNode, std::vector<HeapNode>, HeapNode> pq;
		pq.push({0, 0});
		visited[0] = true;
		parent[0] = -1;

		while (!pq.empty())
		{
			HeapNode top = pq.top();
			int dist_from_start = top.weight;
			pq.pop();

			for (const auto& iter : adj[top.vertex])
			{
				int neighb = iter.dest;
				int distance = iter.weight;

				if (!visited[neighb] && ((dist_from_start + distance) < dist[neighb]))
				{					
					dist[neighb] = dist_from_start + distance;
					parent[neighb] = top.vertex;
					pq.push({neighb, dist[neighb]});
				}
			}

			visited[top.vertex] = true;
		}

		for (int i = 1; i < nodes; ++i) {
			std::cout << "Path from 0 to " << i << " has a cost of " << dist[i] << " and the route is ";
			print(i, parent);
			std::cout << std::endl;
		}
	}
};

int main()
{
	std::vector<Edge> edges{ {0, 1, 10}, {0, 4, 3}, {1, 2, 2}, {1, 4, 4}, {2, 3, 9}, {3, 2, 7}, {4, 1, 1}, {4, 2, 8}, {4, 3, 2} };
	int N = 5;
	DirectedGraph obj(N, edges);
	obj.dijkstra(0);
	return 0;
}