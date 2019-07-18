#include <iostream>
#include <vector>
#include <stack>

// DFS on an undirected graph - https://www.techiedelight.com/depth-first-search/#iterative

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

	void iterativeDFS()
	{
		std::vector<bool> visited(nodes, false);
		std::cout << "Iterative DFS" << std::endl;

		for (int i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{
				iterativeDFSHelper(visited, i);
			}
		}

		std::cout << std::endl;
	}

	void recursiveDFS()
	{
		std::vector<bool> visited(nodes, false);
		std::cout << "Recursive DFS" << std::endl;

		for (int i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{
				recursiveDFSHelper(visited, i);
			}
		}

		std::cout << std::endl;
	}

private:

	void recursiveDFSHelper(std::vector<bool>& visited, int i)
	{
		visited[i] = true;
		std::cout << i << "  ";

		for (int j : adjlist[i])
		{
			if (!visited[j])
			{
				recursiveDFSHelper(visited, j);
			}
		}
	}

	void iterativeDFSHelper(std::vector<bool>& visited, int i)
	{
		std::stack<int> stack;
		stack.push(i);
		visited[i] = true;

		while (!stack.empty())
		{
			int top = stack.top();
			std::cout << top << "  ";
			stack.pop();

			for (auto j = adjlist[top].rbegin(); j != adjlist[top].rend(); ++j)
			{
				if (!visited[*j])
				{
					visited[*j] = true;
					stack.push(*j);
				}
			}
		}
	}
};

int main()
{
	std::vector<Edge> edges{ {1, 2}, {1, 7}, 
	{1, 8}, {2, 3}, {2, 6}, {3, 4}, {3, 5}, 
	{8, 9}, {8, 12}, {9, 10}, {9, 11} };
	int numnodes = 13;
	UndirectedGraph obj(numnodes, edges);
	obj.iterativeDFS();
	obj.recursiveDFS();
	return 0;
}