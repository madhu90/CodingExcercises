#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/find-all-possible-topological-orderings-of-dag/
// This uses recursive backtracking and a DFS approach

struct Edge
{
	int src;
	int dest;
};

class DirectedGraph
{
private:
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
	std::vector<int> indegree;
	int nodes;

public:
	DirectedGraph(int n, const std::vector<Edge>& edges)
		: nodes(n)
	{
		adj.resize(n);
		visited.resize(n);
		indegree.resize(n);

		for (const auto& iter : edges) {
			adj[iter.src].push_back(iter.dest);
			indegree[iter.dest]++;
		}
	}

	void printAllTopo()
	{
		std::vector<int> path;
		printTopoHelper(path);
	}

private:
	void printTopoHelper(std::vector<int>& path)
	{
		for (int i = 0; i < nodes; ++i)
		{
			if (indegree[i] == 0 && !visited[i])
			{
				for (int j : adj[i])
					indegree[j]--;

				visited[i] = true;
				path.push_back(i);
				printTopoHelper(path);

				for (int j : adj[i])
					indegree[j]++;

				visited[i] = false;
				path.pop_back();
			}
		}

		if (path.size() == nodes)
		{
			for (auto iter : path)
			{
				std::cout << iter << "  ";
			}

			std::cout << std::endl;
		}		
	}
};

int main()
{
	std::vector<Edge> edges{ {0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}};
	int n = 8;
	DirectedGraph obj(n, edges);
	obj.printAllTopo();
	return 0;
}