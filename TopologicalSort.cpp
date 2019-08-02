#include <iostream>
#include <vector>
#include <queue>

// QUESTION: https://www.techiedelight.com/topological-sorting-dag/

struct Edge
{
	int src;
	int dest;
};

struct Node
{
	int number;
	int departure_time;

	bool operator()(const Node& left, const Node& right) const
	{
		return left.departure_time < right.departure_time;
	}
};

class DirectedGraph
{
private:
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
	std::vector<Node> departure;
	int nodes;

public:
	DirectedGraph(int num, const std::vector<Edge> & edges)
		: nodes(num)
	{
		adj.resize(nodes);
		visited = std::vector<bool>(nodes, false);
		departure = std::vector<Node>(nodes, { 0, -1 });

		for (const auto& iter : edges)
		{
			adj[iter.src].push_back(iter.dest);
		}
	}

	void topological()
	{
		int time = 0;
		for (int i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{
				topologicalHelper(time, i);
			}
		}
		
		// Create a max heap
		std::priority_queue<Node, std::vector<Node>, Node> pq;

		for (int i = 0; i < nodes; ++i)
		{
			pq.push(departure[i]);
		}

		std::cout << "The topological sort is " << std::endl;

		while (!pq.empty())
		{
			Node top = pq.top();
			pq.pop();
			std::cout << top.number << "  ";
		}

		std::cout << std::endl;
	}

private:
	void topologicalHelper(int& time, int start)
	{
		visited[start] = true;
		++time;

		for (const auto j : adj[start])
		{
			if (!visited[j])
			{
				topologicalHelper(time, j);
			}
		}

		departure[start] = { start, ++time };
	}
};

int main()
{
	std::vector<Edge> edges{ {0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1} };
	int nodes = 8;
	DirectedGraph obj(nodes, edges);
	obj.topological();
	return 0;
}