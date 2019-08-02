#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/arrival-departure-time-vertices-dfs/

struct Edge
{
	int src;
	int dest;
};

class DirectedGraph
{
private:
	std::vector<std::vector<int>> adj;
	std::vector<int> arrival;
	std::vector<int> departure;
	std::vector<bool> visited;
	int nodes;

public:
	DirectedGraph(int num, const std::vector<Edge>& edges)
		: nodes(num)
	{
		adj.resize(nodes);
		arrival = std::vector<int>(nodes, -1);
		departure = std::vector<int>(nodes, -1);
		visited = std::vector<bool>(nodes, false);

		for (const auto& iter : edges)
		{
			adj[iter.src].push_back(iter.dest);
		}
	}

	void printTimes()
	{
		int time = 0;
		
		for (int i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{
				compute(i, time);
			}
		}

		for (int i = 0; i < nodes; ++i)
		{
			std::cout << "Vertex" << i << ":  " << "(" << arrival[i] << ", " << departure[i] << ")" << std::endl;
		}
	}

private:
	void compute(int start, int& time)
	{
		visited[start] = true;
		arrival[start] = time++;

		for (int j : adj[start])
		{
			if (!visited[j])
			{
				compute(j, time);
			}
		}

		departure[start] = time++;
	}
};

int main()
{
	std::vector<Edge> edges{ {0, 1}, {0, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 5}, {4, 5}, {6, 7} };
	int nodes = 8;
	DirectedGraph obj(nodes, edges);
	obj.printTimes();
	return 0;
}