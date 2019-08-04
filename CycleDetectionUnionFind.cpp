#include <iostream>
#include <vector>
#include <unordered_map>

// QUESTION: https://www.techiedelight.com/union-find-algorithm-cycle-detection-graph/
// REFERENCE: https://algorithms.tutorialhorizon.com/graph-find-cycle-in-undirected-graph-using-disjoint-set-union-find/

struct Edge
{
	int src;
	int dest;
};

class DisjointSet
{
private:
	std::unordered_map<int, int> parent;
	std::unordered_map<int, int> rank;
	
public:
	DisjointSet(int N)
	{
		for (int i = 1; i <= N; ++i)
		{
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int find(int x)
	{
		if (x != parent[x])
		{
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void makeUnion(int x, int y)
	{
		int rootx = find(x);
		int rooty = find(y);

		if (rootx == rooty)
			return;

		if (rank[rootx] > rank[rooty]) {
			parent[rooty] = rootx;
		} else if (rank[rooty] > rank[rootx]) {
			parent[rootx] = rooty;
		} else {
			parent[rootx] = rooty;
			rank[rooty]++;
		}
	}
};

class UndirectedGraph
{
private:
	std::vector<std::vector<int>> adj;
	int nodes;

public:
	UndirectedGraph(int n, const std::vector<Edge>& edges)
		: nodes(n)
	{
		adj.resize(nodes);

		for (const auto& iter : edges) {
			adj[iter.src].push_back(iter.dest);
			// Don't do the following! The logic used in union find will end up
			// detecting an edge 1-2 as a cycle because, we will first encounter 1-2 and
			// mark 1 as the parent for 1 and 2. Then we will encounter 2-1 and we will see that
			// they have the same root 1.
			//adj[iter.dest].push_back(iter.src);
		}
	}

	bool hasCycle()
	{
		DisjointSet obj(nodes);

		for (int i = 0; i < nodes; ++i)
		{
			int start = i;			

			for (int j : adj[i])
			{
				int dest = j;
				int root_source = obj.find(start);
				int root_dest = obj.find(dest);

				if (root_source == root_dest)
					return true;

				// you can also pass the start and dest variables. Since you have
				// already computed the roots, you can pass this info. FIND will 
				// first compute the roots only
				obj.makeUnion(root_source, root_dest);
			}
		}
		return false;
	}
};

int main()
{
	std::vector<Edge> edges{ {1, 2}, {1, 7}, {1, 8}, {2, 3}, {2, 6}, {3, 4}, {3, 5}, {8, 9}, {8, 12}, {9, 10}, {9, 11}, {11, 12} };
	int n = 13;
	UndirectedGraph obj(n, edges);
	std::cout << "Graph has cycles: " << obj.hasCycle() << std::endl;
	return 0;
}