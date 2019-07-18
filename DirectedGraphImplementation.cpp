#include <iostream>
#include <vector>

struct Edge
{
	int src;
	int dest;
};

class DirectedGraph
{
private:
	int nodes;
	std::vector<std::vector<int>> adjlist;

public:
	DirectedGraph(int numnodes, const std::vector<Edge>& edges)
		: nodes(numnodes)
	{
		// With std::vector::reserve, you only allocate the specified amount
		// of memory. The logical size of the vector is still the same. So,
		// you need to push back elements

		// With std::vector::resize, the size of the vector is modified. So,
		// you can directly index into elements
		adjlist.resize(numnodes);

		for (auto iter : edges)
		{
			adjlist[iter.src].push_back(iter.dest);
		}
	}

	void print()
	{
		std::cout << "Directed graph" << std::endl;

		for (int i = 0; i < nodes; ++i)
		{
			std::cout << "(" << i;

			for (auto j : adjlist[i])
			{
				std::cout << " ," << j;
			}

			std::cout << ")" << std::endl;
		}
	}
};

int main()
{
	std::vector<Edge> edges{ {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4} };
	int numnodes = 6;
	DirectedGraph obj(numnodes, edges);
	obj.print();
	return 0;
}