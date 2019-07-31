#include <iostream>
#include <vector>
#include <queue>

// QUESTION: https://www.geeksforgeeks.org/find-a-tour-that-visits-all-stations/
//           https://leetcode.com/problems/gas-station/


struct Node
{
	int index;
	int fuel;
};

class MinIndexFinder
{
public:
	int find(const std::vector<int>& capacity, const std::vector<int>& cost)
	{
		int min_index = -1;		
		
		for (int i = 0; i < capacity.size(); ++i)
		{
			if (capacity[i] >= cost[i])
			{
				int indx = findHelper(capacity, cost, i);

				if (indx != -1)
				{
					min_index = indx;
					break;
				}					
			}
		}

		return min_index;
	}

private:

	int findHelper(const std::vector<int>& capacity, const std::vector<int>& cost, int start)
	{
		int firstLookup = true;
		std::queue<Node> queue;
		queue.push({ start, capacity[start] - cost[start] + capacity[findNext(start, capacity.size())] });

		while (!queue.empty())
		{
			Node top = queue.front();
			queue.pop();

			if (top.index == start && !firstLookup)
			{
				return start;
			}

			if (firstLookup)
				firstLookup = false;

			int nextMove = findNext(top.index, capacity.size());

			if (top.fuel >= cost[nextMove])
			{
				queue.push({nextMove, top.fuel - cost[nextMove] + capacity[findNext(nextMove, capacity.size())]});
			}
		}

		return -1;
	}
	int findNext(int curr, int length)
	{
		return (curr + 1) % length;
	}
};

int main()
{
	MinIndexFinder obj;
	std::vector<int> capacity1{5,1,2,3,4};
	std::vector<int> cost1{4,4,1,5,1};
	std::vector<int> capacity2 {2,3,4};
	std::vector<int> cost2{ 3,4,3 };
	std::vector<int> capacity3{1,2,3,4,5};
	std::vector<int> cost3{3,4,5,1,2};
	int indx1 = obj.find(capacity1, cost1);
	int indx2 = obj.find(capacity2, cost2);
	int indx3 = obj.find(capacity3, cost3);
	std::cout << "Min index is " << indx1 << std::endl;
	std::cout << "Min index is " << indx2 << std::endl;
	std::cout << "Min index is " << indx3 << std::endl;
	std::vector<int> capacity4{ 3,3,4 };
	std::vector<int> cost4{ 3,4,4 };
	int indx4 = obj.find(capacity4, cost4);
	std::cout << "Min index is " << indx4 << std::endl;

	std::vector<int> capacity5{ 4,5,2,6,5,3 };
	std::vector<int> cost5{ 3,2,7,3,2,9 };
	int indx5 = obj.find(capacity5, cost5);
	std::cout << "Min index is " << indx5 << std::endl;
	return 0;
}