#include <vector>
#include <iostream>
#include <numeric>

void computeEqulibriumIndex_1(const std::vector<int>& arr)
{
	// Time complexity is O(n)
	// Space complexity is O(n)
	std::vector<int> left_sum(arr.size(), 0);
	std::vector<int> right_sum(arr.size(), 0);

	for (int i = 1; i < arr.size(); ++i) {
		left_sum[i] = left_sum[i - 1] + arr[i - 1];		
	}

	for (int i = arr.size() - 2; i >= 0; --i) {
		right_sum[i] = right_sum[i + 1] + arr[i + 1];
	}

	for (int i = 0; i < arr.size(); ++i) {
		if (left_sum[i] == right_sum[i]) {
			std::cout << "Approach 1: Equilibrium index at " << i << std::endl;
		}
	}
}

void computeEqulibriumIndex_2(const std::vector<int>& arr)
{
	int array_sum = std::accumulate(arr.begin(), arr.end(), 0);
	int left_sum = 0;
	int right_sum = 0;

	for (int i = 0; i < arr.size(); ++i)
	{
		right_sum = array_sum - arr[i] - left_sum;

		if (left_sum == right_sum) {
			std::cout << "Approach 2: Equilibrium index at " << i << std::endl;
		}

		left_sum += arr[i];
	}
}

int main()
{
	std::vector<int> arr{ 0, -3, 5, -4, -2, 3, 1, 0 };
	computeEqulibriumIndex_1(arr);
	computeEqulibriumIndex_2(arr);
	return 0;
}