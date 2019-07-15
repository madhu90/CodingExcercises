#include <iostream>
// Question: https://www.geeksforgeeks.org/count-ways-reach-nth-stair/

void findNumberOfWays(int targetStairs, int& total_no_ways, int curr_count, int stairsAtOnceAtmost)
{
	if (curr_count == targetStairs)
	{
		total_no_ways++;
		return;
	}

	if (curr_count < targetStairs)
	{
		for (size_t i = 1; i <= stairsAtOnceAtmost; ++i)
		{
			findNumberOfWays(targetStairs, total_no_ways, curr_count + i, stairsAtOnceAtmost);
		}		
	}	
}

int main()
{
	int targetStairs = 4;
	int stairsAtOnceAtmost = 2;
	int total_no_ways = 0;
	findNumberOfWays(targetStairs, total_no_ways, 0, stairsAtOnceAtmost);
	std::cout << "Total number of ways is " << total_no_ways << std::endl;
	return 0;
}