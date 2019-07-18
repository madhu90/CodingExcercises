#include <iostream>
#include <vector>
#include <queue>

// Question: https://www.techiedelight.com/least-cost-path-weighted-digraph-using-bfs/

struct Edge
{
	int src;
	int dest;
	int weight;
};

class DirectedGraph
{
private:
	std::vector<std::vector<int>> adj; // we don't have to store weight because we are doing more work to make it 1 !
	int nodes; // Can increase if we add new nodes

private:
	void printPath(const std::vector<int>& v, int parent, std::vector<int>& path, int& cost)
	{
		if (parent < 0)
			return;
		printPath(v, v[parent], path, cost);
		cost++;
		path.push_back(parent);
	}

public:
	DirectedGraph(int numnodes, const std::vector<Edge>& edges)
		: nodes(numnodes)
	{
		int extranodes = 0;

		// Find out how many additional nodes are needed
		for (auto iter : edges)
		{
			if (iter.weight > 1)
			{
				extranodes += (iter.weight - 1);
			}
		}

		adj.resize(extranodes + nodes);

		for (auto iter : edges)
		{			
			int src = iter.src;
			int dest = iter.dest;
			int weight = iter.weight;

			if (weight == 3)
			{
				// 2 new nodes needed
				++nodes;
				int newidx1 = nodes - 1;
				adj[src].push_back(newidx1);
				++nodes;
				int newidx2 = nodes - 1;
				adj[newidx1].push_back(newidx2);
				adj[newidx2].push_back(dest);	
			} else if (weight == 2) { 
				// 1 new node needed				
				++nodes;
				int newidx1 = nodes - 1;
				adj[src].push_back(newidx1);
				adj[newidx1].push_back(dest);
			} else {
				adj[src].push_back(dest);
			}
		}
	}

	void lowcostpath(int src, int dest)
	{		
		std::queue<int> queue;
		std::vector<bool> visited(nodes, false);
		std::vector<int> parent(nodes, -1);
		visited[src] = true;		
		queue.push(src);

		while (!queue.empty())
		{
			int top = queue.front();
			queue.pop();

			if (top == dest)
			{
				int cost = -1;
				std::vector<int> path;
				printPath(parent, top, path, cost);
				std::cout << "The shortest path has a cost of " << cost << " and, it is:" << std::endl;				

				for (auto iter : path)
				{
					std::cout << iter << "  ";
				}

				std::cout << std::endl;
				break;
			} else {
				for (int j : adj[top])
				{
					if (!visited[j])
					{
						visited[j] = true;
						parent[j] = top;
						queue.push(j);
					}
				}
			}
		}
	}

	void print()
	{
		std::cout << "Printing directed graph" << std::endl;
		for (size_t i = 0; i < nodes; ++i)
		{
			std::cout << "(" << i;

			for (auto j : adj[i])
			{
				std::cout << ", " << j;
			}
			std::cout << ")" << std::endl;
		}
	}
};

int main()
{
	std::vector<Edge> edges{ {0, 1, 3}, {0, 4, 1}, {1, 2, 1}, {1, 3, 3}, {1, 4, 1}, {4, 2, 2}, {4, 3, 1} };
	int nodes = 5;
	DirectedGraph obj(nodes, edges);
	obj.print();
	obj.lowcostpath(0, 2);

	
	//Graph graph(edges, 1, 5);
	//graph.print();
	//int source = 0, dest = 2;
	//BFS(graph, source, dest, 5);
	return 0;
}