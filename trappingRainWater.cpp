#include <iostream>
#include <vector>
#include <algorithm>

// Question: https://www.techiedelight.com/trapping-rain-water-within-given-set-bars/
// https://leetcode.com/problems/trapping-rain-water/solution/


/* For each element in the array, we find the maximum level of water it can trap after the rain, 
   which is equal to the minimum of maximum height of bars on both the sides minus its own height.

	Algorithm

	- Initialize ans = 0ans = 0
	- Iterate the array from left to right :
	- Initialize max_left = 0 and max_right = 0
	- Iterate from the current element to the beginning of array updating:
		max_left = max(max_left, height[j])
	- Iterate from the current element to the end of array updating:
		max_right = max(max_right, height[j])
	- Add min(max_left , max_right) - height[i] to ans

	This has a time complexity of O(n^2)
*/

int maxWater_BruteForce(const std::vector<int>& arr)
{
	int water = 0;
	int max_left = 0;
	int max_right = 0;

	for (size_t i = 0; i < arr.size(); ++i)
	{
		max_left = arr[i];
		max_right = arr[i];

		for (size_t j = 0; j < i; ++j)
		{
			max_left = std::max(max_left, arr[j]);
		}

		for (size_t j = i + 1; j < arr.size(); ++j)
		{
			max_right = std::max(max_right, arr[j]);
		}

		water += std::min(max_left, max_right) - arr[i];
	}

	return water;
}

int maxWater_DP(const std::vector<int>& arr)
{
	// Max to the left of current element
	std::vector<int> left(arr.size(), 0);
	std::vector<int> right(arr.size(), 0);
	int water = 0;
	left[0] = arr[0];
	right[arr.size() - 1] = arr[arr.size() - 1];

	for (size_t i = 1; i < arr.size(); ++i)
	{
		left[i] = std::max(arr[i], left[i - 1]);
	}

	for (int i = arr.size() - 2; i >= 0; --i)
	{
		right[i] = std::max(arr[i], right[i + 1]);
	}

	for (size_t i = 0; i < arr.size(); ++i)
	{
		water += std::min(left[i], right[i]) - arr[i];
	}

	return water;
}

int maxWater_Optimized(const std::vector<int>& arr)
{
	int water = 0;
	int left = 0;
	int left_max = 0;
	int right = arr.size() - 1;
	int right_max = 0;

	while (left <= right)
	{
		if (arr[left] > arr[right])
		{
			// Equilibrium point determined by the lower side
			if (arr[left] >= left_max)
			{
				left_max = arr[left];
			} else {
				water += (left_max - arr[left]);
			}
			left++;
		} else {
			if (arr[right] >= right_max)
			{
				right_max = arr[right];
			} else {
				water += (right_max - arr[right]);
			}
			right--;
		}
	}
	return water;
}

int main()
{
	std::vector<int> arr{ 7, 0, 4, 2, 5, 0, 6, 4, 0, 5 };
	int water1 = maxWater_BruteForce(arr);
	std::cout << "Water capacity (Brute force) is " << water1 << std::endl;
	int water2 = maxWater_DP(arr);
	std::cout << "Water capacity (DP) is " << water2 << std::endl;
	int water3 = maxWater_Optimized(arr);
	std::cout << "Water capacity (optimized) is " << water3 << std::endl;
	return 0;
}