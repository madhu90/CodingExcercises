#include <iostream>
#include <vector>
#include <queue>

// QUESTION: https://www.techiedelight.com/bipartite-graph/

struct Edge
{
	int src;
	int dest;
};

class UndirctedGraph {
private:
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
	std::vector<int> level;
	int nodes;

public:
	UndirctedGraph(int n, const std::vector<Edge>& edges)
		: nodes(n)
	{
		adj.resize(nodes);
		visited.resize(nodes);
		level = std::vector<int>(nodes, -1);

		for (const auto& iter : edges)
		{
			adj[iter.src].push_back(iter.dest);
		}
	}

	void isBipartite()
	{
		doBFS();
	}

private:
	void doBFS()
	{
		bool isbipartite = true;

		for (int i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{
				if (!doBFSHelper(i))
				{
					isbipartite = false;
					break;
				}
			}
		}

		if (isbipartite)
		{
			std::cout << "Graph is bipartite" << std::endl;
		} else {
			std::cout << "Graph is not bipartite" << std::endl;
		}
	}

	bool doBFSHelper(int start)
	{
		std::queue<int> queue;
		queue.push(start);
		level[start] = 0;
		visited[start] = true;

		for (int j : adj[start])
		{
			if (!visited[j])
			{
				visited[j] = true;
				level[j] = level[start] + 1;
				queue.push(j);
			} else {
				if (level[j] == level[start])
					return false;
			}
		}

		return true;
	}
};

int main()
{
	std::vector<Edge> edges{ {1,2}, {2, 3}, {2, 8}, {3, 4}, {4, 6}, {5, 7}, {5, 9}, {8, 9} };
	int n = 10;
	UndirctedGraph obj(n, edges);
	obj.isBipartite();
	return 0;
}