#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// QEUESTION: https://www.techiedelight.com/subset-sum-problem/

class SubsetSum
{
private:
	std::unordered_map<std::string, bool> map;
	const std::vector<int>& arr;
	int targetSum;

public:
	SubsetSum(const std::vector<int>& a, int sum)
		: arr(a), targetSum(sum)
	{

	}

	bool doExponential()
	{
		std::cout << "Exponential approach to subset sum problem" << std::endl;
		return doExponentialHelper(arr.size() - 1, targetSum);
	}

	bool doTopDown()
	{
		std::cout << "Top-down approach to subset sum problem" << std::endl;
		return doTopDownHelper(arr.size() - 1, targetSum);
	}

	bool doBottomUp()
	{
		std::cout << "Bottom-up approach to subset sum problem" << std::endl;
		std::vector<std::vector<bool>> lookup(arr.size() + 1, std::vector<bool>(targetSum + 1, 0));

		// If sum = 0, we have the option of ignoring every element because {} is a subset
		for (int i = 0; i < lookup.size(); ++i)
			lookup[i][0] = true;

		for (int i = 1; i < lookup.size(); ++i) {
			for (int j = 1; j < lookup[i].size(); ++j) {
				if (arr[i - 1] > j)
				{
					lookup[i][j] = lookup[i - 1][j];
				} else {
					lookup[i][j] = lookup[i - 1][j] || lookup[i - 1][j - arr[i - 1]];
				}
			}
		}

		return lookup[arr.size()][targetSum];
	}

private:
	bool doTopDownHelper(int indx, int sum)
	{
		if (sum == 0)
			return true;

		if (indx < 0)
			return false;

		std::string key = std::to_string(indx) + "_" + std::to_string(sum);

		if (map.find(key) == map.end())
		{
			if (sum - arr[indx] >= 0)
			{
				map[key] = doExponentialHelper(indx - 1, sum - arr[indx]) || doExponentialHelper(indx - 1, sum);
			} else {
				map[key] = doExponentialHelper(indx - 1, sum);
			}
		}

		return map[key];
	}

	bool doExponentialHelper(int indx, int sum)
	{
		if (sum == 0)
			return true;

		if (indx < 0)
			return false;
		
		if (sum - arr[indx] >= 0)
		{
			return doExponentialHelper(indx - 1, sum - arr[indx]) || doExponentialHelper(indx - 1, sum);
		} else {
			return doExponentialHelper(indx - 1, sum);
		}
	}

};

int main()
{
	std::vector<int> arr{ 7, 3, 2, 5, 8 };
	int sum = 14;
	SubsetSum obj(arr, sum);
	bool result1 = obj.doExponential();
	std::cout << "Subset sum result " << result1 << std::endl;
	bool result2 = obj.doTopDown();
	std::cout << "Subset sum result " << result2 << std::endl;
	bool result3 = obj.doBottomUp();
	std::cout << "Subset sum result " << result3 << std::endl;
	return 0;
}