#include <vector>
#include <iostream>
#include <algorithm>

// QUESTION: https://www.techiedelight.com/exponential-search/

class ExponentialSearch
{
private:
	const std::vector<int>& arr;

public:
	ExponentialSearch(const std::vector<int>& a)
		: arr(a)
	{

	}

	int find(int target)
	{
		int bound = 1;

		// Find the bounds. The power of 2 (2^k) which is greater than
		// the target. The upper bound will be 2^k (or the array length, whichever
		// is the minimum) and lower bound will be 2^k-1 (or 2^k/2)
		while (bound < arr.size() && std::pow(2, bound) < target)
			bound = bound * 2;

		return binarySearch(bound / 2, std::min(bound, static_cast<int>(arr.size() - 1)), target);
	}

private:
	int binarySearch(int low, int high, int target)
	{
		while (low <= high)
		{
			int mid = low + (high - low) / 2;

			if (arr[mid] == target)
				return mid;

			if (target > arr[mid])
			{
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}		

		return -1;
	}
};

int main()
{
	const std::vector<int> arr{ 2, 5, 6, 8, 9, 10 };
	ExponentialSearch obj(arr);
	int indx = obj.find(9);
	std::cout << "Index of 9 is " << indx << std::endl;
	return 0;
}