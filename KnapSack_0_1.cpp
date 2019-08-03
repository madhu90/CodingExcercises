#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

// QUESTION: https://www.techiedelight.com/0-1-knapsack-problem/

class Knapsack
{
private:
	int targetWt;
	std::unordered_map<std::string, int> map;
	const std::vector<int>& wts;
	const std::vector<int>& values;

public:
	Knapsack(int W, const std::vector<int>& w, const std::vector<int>& v)
		: targetWt(W), wts(w), values(v)
	{

	}

	int doExponential()
	{
		std::cout << "Exponential solution to 0-1 Knapsack" << std::endl;
		return doExponentialHelper(wts.size() - 1, targetWt);
	}

	int doTopDown()
	{
		std::cout << "DP: Top-down solution to 0-1 Knapsack" << std::endl;
		return doTopDownHelper(wts.size() - 1, targetWt);
	}

	int doBottomUp()
	{
		std::cout << "DP: Bottom-up solution to 0-1 Knapsack" << std::endl;
		std::vector<std::vector<int>> lookup(wts.size() + 1, std::vector<int>(targetWt+ 1, 0));

		for (int i = 1; i < lookup.size(); ++i) {
			for (int j = 1; j < lookup[i].size(); ++j) {
				if (wts[i - 1] > j)
				{
					lookup[i][j] = lookup[i - 1][j];
				} else {
					lookup[i][j] = std::max(lookup[i - 1][j], values[i - 1] + lookup[i - 1][j - wts[i - 1]]);
				}
			}
		}

		return lookup[wts.size()][targetWt];
	}

private:
	int doTopDownHelper(int curr_index, int total_wt)
	{
		if (curr_index < 0 || total_wt == 0)
			return 0;

		std::string key = std::to_string(curr_index) + "_" + std::to_string(total_wt);

		if (map.find(key) == map.end())
		{
			// If you can include the current element, then return the max of including
			// and excluding it
			if (total_wt - wts[curr_index] >= 0)
			{
				int include = values[curr_index] + doTopDownHelper(curr_index - 1, total_wt - wts[curr_index]);
				int exclude = doTopDownHelper(curr_index - 1, total_wt);
				map[key] = std::max(include, exclude);
			} else {
				// If you can't include the current element, find the maximum by excluding it
				map[key] = doTopDownHelper(curr_index - 1, total_wt);
			}
		} 

		return map[key];
	}

	int doExponentialHelper(int curr_index, int total_wt)
	{
		if (curr_index < 0 || total_wt == 0)
			return 0;

		// If you can include the current element, then return the max of including
		// and excluding it
		if (total_wt - wts[curr_index] >= 0)
		{
			int include = values[curr_index] + doExponentialHelper(curr_index - 1, total_wt - wts[curr_index]);
			int exclude = doExponentialHelper(curr_index - 1, total_wt);
			return std::max(include, exclude);
		} else {
			// If you can't include the current element, find the maximum by excluding it
			return doExponentialHelper(curr_index - 1, total_wt);
		}	
	}
};

int main()
{
	const std::vector<int> wt{ 1, 2, 3, 8, 7, 4 };
	const std::vector<int> v{ 20, 5, 10, 40, 15, 25 };
	int W = 10;
	Knapsack obj(W, wt, v);
	int result1 = obj.doExponential();
	std::cout << "Max value is " << result1 << std::endl;
	int result2 = obj.doTopDown();
	std::cout << "Max value is " << result2 << std::endl;
	int result3 = obj.doBottomUp();
	std::cout << "Max value is " << result3 << std::endl;
	return 0;
}