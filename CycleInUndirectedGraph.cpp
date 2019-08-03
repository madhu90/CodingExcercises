#include <iostream>
#include <vector>
#include <queue>

// QUESTION: https://www.techiedelight.com/check-undirected-graph-contains-cycle-not/

struct Edge
{
	int src;
	int dest;
};

class UndirectedGraph
{
private:
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
	int nodes;

private:
	bool dfsHelper(std::pair<int, int> start)
	{
		bool result = false;

		visited[start.first] = true;

		for (int j : adj[start.first])
		{
			if (!visited[j])
			{
				result = dfsHelper(std::make_pair(j, start.first));
			} else if (j != start.second) {
				result = true;
				break;
			}
		}

		return result;
	}

public:
	UndirectedGraph(int n, const std::vector<Edge>& edges)
		: nodes(n)
	{
		adj.resize(nodes);
		visited = std::vector<bool>(nodes, false);

		for (const auto& iter : edges)
		{
			adj[iter.src].push_back(iter.dest);
		}
	}

	void dfs()
	{
		visited.clear();
		visited = std::vector<bool>(nodes, false);
		bool cycle = dfsHelper(std::make_pair(1, -1));

		if (cycle)
		{
			std::cout << "DFS detected a cycle" << std::endl;
		} else {
			std::cout << "DFS dit not detect a cycle" << std::endl;
		}
	}

	void bfs()
	{
		visited.clear();
		visited = std::vector<bool>(nodes, false);
		bool cycle = false;
		std::queue<std::pair<int, int>> queue;
		queue.push({1, -1});
		visited[1] = true;

		while (!queue.empty())
		{
			std::pair<int, int> top = queue.front();
			queue.pop();

			for (int j : adj[top.first])
			{
				if (!visited[j])
				{
					visited[j] = true;
					queue.push({j, top.first});
				} else if (j != top.second) {
					cycle = true;
					break;
				}
			}
		}

		if (cycle)
		{
			std::cout << "BFS detected a cycle" << std::endl;
		} else {
			std::cout << "BFS dit not detect a cycle" << std::endl;
		}
	}
};

int main()
{
	std::vector<Edge> edges1{ {1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {5, 9}, {5, 10}, {4, 7}, {4, 8}, {7, 11}, {7, 12}, {6, 10} };
	int num1 = 13;
	UndirectedGraph obj1(num1, edges1);
	obj1.bfs();
	std::vector<Edge> edges2{ {1, 2}, {1, 7}, {1, 8}, {2, 3}, {2, 6}, {3, 4}, {3, 5}, {8, 9}, {8, 12}, {9, 10}, {9, 11}, {11, 12} };
	int num2 = 13;
	UndirectedGraph obj2(num2, edges2);
	obj2.dfs();
	return 0;
}