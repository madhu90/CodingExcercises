#include <iostream>
#include <vector>
#include <queue>

// QUESTION: https://www.techiedelight.com/kahn-topological-sort-algorithm/
// Explanation: https://medium.com/insider-inc-engineering/the-wrath-of-kahns-algorithm-68081cf2fc55

/**
 * This is a BFS approach to getting a topological sort. We try to get vertices with
 * indegree 0. Then we remove it from the graph and push it into our output list. This
 * requires updating the indegree of the nodes in the adjacency list. If we find a node
 * with 0 indegree, we push it to the queue
 */

struct Edge
{
	int src;
	int dest;
};

class DirectedGraph
{
private:
	std::vector<std::vector<int>> adj;
	std::vector<int> indegree;	
	int nodes;

public:
	DirectedGraph(int n, const std::vector<Edge>& edges)
		: nodes(n)
	{
		adj.resize(nodes);
		indegree.resize(nodes);

		for (const auto & iter : edges)
		{
			adj[iter.src].push_back(iter.dest);
			// An edge from src to dest means, indegree of 
			// dest increases
			indegree[iter.dest]++;
		}
	}

	void doKahn()
	{
		std::cout << "Kahn's topological sorting" << std::endl;
		std::queue<int> queue;
		std::vector<int> topo;
		
		for (int i = 0; i < nodes; ++i)
		{
			if (indegree[i] == 0)
				queue.push(i);
		}

		while (!queue.empty())
		{
			int top = queue.front();
			queue.pop();
			topo.push_back(top);

			for (int j : adj[top])
			{
				indegree[j]--;

				if (indegree[j] == 0)
					queue.push(j);
			}
		}

		for (auto iter : topo)
		{
			std::cout << iter << "  ";
		}
		std::cout << std::endl;
	}
};

int main()
{
	std::vector<Edge> edges{ {0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1} };
	int num = 8;
	DirectedGraph obj(num, edges);
	obj.doKahn();
	return 0;
}