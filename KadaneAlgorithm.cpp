#include <iostream>
#include <vector>
#include <algorithm>

int maxSumSubarray(std::vector<int>& arr)
{
	// We are not using an array to save the max sums ending
	// at all indices. We use the principle:
	// local_maxima[i] = std::max(A[i], A[i] + local_maxima[i - 1])
	int local_maximum = 0;
	int global_maximum = std::numeric_limits<int>::min();

	for (size_t i = 0; i < arr.size(); ++i) {
		local_maximum = std::max(arr[i], arr[i] + local_maximum);
		if (local_maximum > global_maximum)
			global_maximum = local_maximum;
	}

	return global_maximum;
}

int main()
{
	std::vector<int> arr{-2, 1, -3, 4, -1, 2, 1, -5, 4};
	int maxSum = maxSumSubarray(arr);
	std::cout << "Maximum sum is " << maxSum << std::endl;
	return 0;
}