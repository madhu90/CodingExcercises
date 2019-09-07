#include <iostream>
#include <vector>

// QUESTION : https://www.techiedelight.com/count-occurrences-number-sorted-array-duplicates/

// Count occurences of a number in a sorted array with duplicates
class Counter
{
private:
	const std::vector<int>& arr;

public:
	Counter(const std::vector<int>& a)
		: arr(a)
	{
	}

	int find(int number)
	{
		return helper(0, arr.size(), number);
	}

private:
	int helper(int low, int high, int number)
	{
		if (low >= 0 && high < arr.size() && arr[low] == arr[high] && arr[low] == number)
		{
			return high - low + 1;
		}

		if (low < high)
		{
			int mid = low + (high - low) / 2;

			if (arr[mid] == number) {
				// This could be the first, last or mid element  -> find its position!
				if ((mid + 1 < arr.size()) && (mid - 1 > 0) && (arr[mid - 1] == number) && (arr[mid + 1] == number)) {
					// mid position -> look for more in left and right directions
					return 1 + helper(low, mid - 1, number) + helper(mid + 1, high, number);
				} else if (mid + 1 < arr.size() && arr[mid + 1] == number) {
					// first position (nothing on the left)
					return 1 + helper(mid + 1, high, number);
				} else if (mid - 1 > 0 && arr[mid - 1] == number) {
					// last position (nothing on the right)
					return 1 + helper(low, mid - 1, number);
				} else {
					// element occurs only once
					return 1;
				}
			} else if (arr[mid] > number) {
				return helper(low, mid, number);
			} else {
				return helper(mid + 1, high, number);
			}
		}
	}
};

int main()
{
	std::vector<int> arr{ 2, 5, 5, 5, 6, 6, 8, 9, 9, 9 };
	Counter obj(arr);
	std::cout << "2 occurs " << obj.find(2) << " times" << std::endl;
	std::cout << "5 occurs " << obj.find(5) << " times" << std::endl;
	std::cout << "6 occurs " << obj.find(6) << " times" << std::endl;
	std::cout << "8 occurs " << obj.find(8) << " times" << std::endl;
	std::cout << "9 occurs " << obj.find(9) << " times" << std::endl;
	return 0;
}