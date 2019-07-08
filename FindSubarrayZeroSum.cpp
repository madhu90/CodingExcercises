// Find all subarrays ina given array with 0 sum
#include <iostream>
#include <vector>
#include <map>

std::vector<std::pair<int, int>> subArraysWithZeroSum(std::vector<int>& arr)
{
	std::vector<std::pair<int, int>> array_indices;
	std::multimap<int, int> map; // Map of array value and index
	map.insert(std::make_pair(0, -1)); // If sub-array starts at 0, we need to handle this situation
	int running_sum = 0;

	for (size_t i = 0; i < arr.size(); ++i) 
	{
		running_sum += arr[i];

		// Get a pair representing a range of indices where sum is running_sum
		auto found_idx = map.equal_range(running_sum);
		
		if (found_idx.first != map.end())
		{
			for (auto iter = found_idx.first; iter != found_idx.second; ++iter)
			{
				array_indices.push_back(std::make_pair(iter->second + 1, i));				
			}			
		} 

		map.insert(std::make_pair(running_sum, i));
	}

	return array_indices;
}

int main()
{
	std::vector<int> arr{ 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };
	std::vector<std::pair<int, int>> result = subArraysWithZeroSum(arr);

	if (result.empty()) {
		std::cout << "No subarray with zero sum found" << std::endl;
	} else {
		for (auto iter : result)
		{
			std::cout << "Zero sum subarray starts at " << iter.first << " and ends at " << iter.second << std::endl;
		}
	}
	return 0;
}