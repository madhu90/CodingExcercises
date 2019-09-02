#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

// QUESTION: https://www.techiedelight.com/rot-cutting/

class RodCutting
{
private:
	const std::vector<int>& length;
	const std::vector<int>& price;
	std::unordered_map<std::string, int> map;

public:
	RodCutting(const std::vector<int>& l, const std::vector<int>& p)
		: length(l), price(p)
	{

	}

	int findMaxProfitBruteForce(int length)
	{
		return profit(length);
	}

	int findMaxProfitTopDown(int length)
	{
		return topdown(length);
	}

	int findMaxProfitBottomUp(int length)
	{
		return bottomUp(length);
	}

private:

	int bottomUp(int length)
	{
		std::vector<int> lookup(length + 1, 0);

		for (int len = 1; len <= length; ++len)
		{
			// For each length start with j = 1 upto i
			for (int j = 1; j <= len; ++j)
				lookup[len] = std::max(lookup[len], price[j - 1] + lookup[len - j]);
		}

		return lookup[length];
	}

	int topdown(int length)
	{
		if (length == 0)
			return 0;

		std::string key = std::to_string(length);

		if (map.find(key) == map.end())
		{
			int result = std::numeric_limits<int>::min();
			for (int start = 1; start <= length; ++start)
			{
				int cost = price[start - 1] + topdown(length - start);
				if (cost > result)
					result = cost;
			}

			map[key] = result;
		} 

		return map[key];
	}

	int profit(int length)
	{
		int result = std::numeric_limits<int>::min();

		if (length == 0)
			return 0; // we don't have price[-1]

		for (int start = 1; start <= length; ++start)
		{
			int cost = price[start - 1] + profit(length - start);

			if (cost > result)
				result = cost;
		}

		return result;
	}
};

int main()
{
	std::vector<int> length{ 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> price{ 1, 5, 8, 9, 10, 17, 1, 20 };
	RodCutting obj(length, price);
	int result1 = obj.findMaxProfitBruteForce(4);
	std::cout << "Max profit (brute force) is " << result1 << std::endl;
	int result2 = obj.findMaxProfitTopDown(4);
	std::cout << "Max profit (top down) is " << result2 << std::endl;
	int result3 = obj.findMaxProfitBottomUp(4);
	std::cout << "Max profit (bottom up) is " << result3 << std::endl;
	return 0;
}