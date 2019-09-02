#include <iostream>
#include <vector>

// QUESTION : https://www.techiedelight.com/find-number-1s-sorted-binary-array/

class SortedBinaryArray
{
private:
	const std::vector<int>& arr;

public:
	SortedBinaryArray(const std::vector<int>& a)
		: arr(a)
	{

	}

	int findNumberOfOnes()
	{
		return helper(0, arr.size() - 1);
	}

private:
	int helper(int low, int high)
	{
		if (arr[high] == 0)
			return 0;

		if (arr[low] == 1)
			return high - low + 1;

		int mid = low + (high - low) / 2;

		return helper(low, mid) + helper(mid + 1, high);
	}
};

int main()
{
	std::vector<int> arr1{ 0, 0, 0, 0, 1, 1, 1 };
	std::vector<int> arr2{ 0, 0, 1, 1, 1, 1, 1 };
	SortedBinaryArray obj1(arr1);
	SortedBinaryArray obj2(arr2);
	int num1 = obj1.findNumberOfOnes();
	int num2 = obj2.findNumberOfOnes();
	std::cout << "Number of 1's is " << num1 << std::endl;
	std::cout << "Number of 1's is " << num2 << std::endl;
	return 0;
}