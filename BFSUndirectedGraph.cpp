#include <iostream>
#include <vector>
#include <queue>

// BFS on an undirected graph - https://www.techiedelight.com/breadth-first-search/

struct Edge
{
	int src;
	int dest;
};

class UndirectedGraph
{
private:
	int nodes;
	std::vector<std::vector<int>> adjlist;

public:
	UndirectedGraph(int numnodes, const std::vector<Edge>& edges)
		: nodes(numnodes)
	{
		adjlist.resize(nodes);

		for (auto iter : edges)
		{
			adjlist[iter.src].push_back(iter.dest);
			adjlist[iter.dest].push_back(iter.src);
		}
	}

	void iterativeBFS()
	{
		std::vector<bool> visited(nodes, false);
		std::cout << "Iterative BFS" << std::endl;

		// FOR loop is needed if graph is not connected
		for (size_t i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{			
				iterativeBFSHelper(visited, i);
			}
		}

		std::cout << std::endl;
	}

	void recursiveBFS()
	{
		std::vector<bool> visited(nodes, false);
		std::cout << "Recursive BFS" << std::endl;
		std::queue<int> queue;
		
		// FOR loop is needed if graph is not connected
		for (size_t i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{
				queue.push(i);
				recursiveBFSHelper(visited, queue);
			}
		}
		std::cout << std::endl;
	}

private:

	void recursiveBFSHelper(std::vector<bool>& visited, std::queue<int>& queue)
	{
		if (queue.empty())
			return;

		int top = queue.front();
		visited[top] = true;		
		std::cout << top << "  ";
		queue.pop();

		for (int j : adjlist[top])
		{
			if (!visited[j])
			{
				queue.push(j);
			}
		}

		recursiveBFSHelper(visited, queue);
	}

	void iterativeBFSHelper(std::vector<bool>& visited, int start)
	{
		// Mark node as discovered or visited
		visited[start] = true;

		std::queue<int> queue;
		queue.push(start);

		while (!queue.empty())
		{
			int top = queue.front();
			std::cout << top << "  ";
			queue.pop();

			for (int j : adjlist[top])
			{
				if (!visited[j])
				{
					visited[j] = true;
					queue.push(j);
				}
			}
		}
	}
};

int main()
{
	std::vector<Edge> edges{ {1, 2}, {1, 3}, 
	{1, 4}, {2, 5}, {2, 6}, {5, 9}, {5, 10}, 
	{4, 7}, {4, 8}, {7, 11}, {7, 12} };
	int numnodes = 15;
	UndirectedGraph obj(numnodes, edges);
	obj.iterativeBFS();
	obj.recursiveBFS();
	return 0;
}