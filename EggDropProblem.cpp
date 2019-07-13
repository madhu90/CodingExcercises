#include <iostream>
#include <vector>
#include <algorithm>

class EggDropSimulator
{
private:
	int eggs;
	int floors;

public:
	EggDropSimulator(int numEggs, int numFloors)
		: eggs(numEggs), floors(numFloors)
	{

	}

	int findPivotalFloor()
	{
		std::vector<std::vector<int>> dp(eggs + 1, std::vector<int>(floors + 1, 0));

		// Base condition 1: If number of eggs is 0, we can't do anything
		// Base condition 2: If number of floors is 0, we can't do anything
		// Base condition 3: If number of eggs is 1, worst case depends on number of floors
		for (size_t i = 1; i < dp[0].size(); ++i)
			dp[1][i] = i;

		// Base condition 4: If number of floors is 1, worst case depends drops is always 1
		for (size_t i = 1; i < dp.size(); ++i)
			dp[i][1] = 1;

		for (size_t i = 2; i < dp.size(); ++i)
		{
			for (size_t j = 2; j < dp[0].size(); ++j)
			{
				// For a given question dp[i][j], we need to look
				// at the worst case from dp[i][1] to dp[i][j]
				dp[i][j] = std::numeric_limits<int>::max();

				for (size_t k = 1; k <= j; ++k)
				{
					int max_value = std::max(dp[i][j - k], dp[i - 1][k - 1]) + 1;
					// We want minimum number of turns from the worst case
					if (max_value < dp[i][j])
						dp[i][j] = max_value;
				}				
			}
		}

		return dp[eggs][floors];
	}
};

int main()
{
	int numEggs = 2;
	int numFloors = 100;
	EggDropSimulator sim(numEggs, numFloors);
	int numSims = sim.findPivotalFloor();
	std::cout << "Worst case number of turns for " << numEggs << " eggs and " << numFloors << " floors is " << numSims << std::endl;
	return 0;
}