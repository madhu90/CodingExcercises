// Given an array, find a pair with the given sum
#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<std::pair<int, int>> findPairs(std::vector<int>& arr, int sum)
{
	// Map of value and array index
	std::unordered_map<int, int> map;
	std::vector<std::pair<int, int>> result;

	for (size_t iter = 0; iter < arr.size(); ++iter)
	{
		auto map_idx = map.find(sum - arr[iter]);
		if (map_idx != map.end())
		{			
			result.push_back(std::make_pair(iter, map_idx->second));
		} else {
			map[arr[iter]] = iter;
		}
	}

	return result;
}

int main()
{
	std::vector<int> arr{8, 7, 2, 5, 3, 1};	
	int sum = 10;
	std::vector<std::pair<int, int>> result = findPairs(arr, sum);

	if (result.empty())
	{
		std::cout << "Pair with sum " << sum << " not found" << std::endl;
	} else {
		for (auto iter : result)
		{
			std::cout << arr[iter.first] << " and " << arr[iter.second] << " sum upto " << sum << std::endl;
		}		
	}
}