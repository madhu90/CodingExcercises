#include <iostream>
#include <vector>
#include <algorithm>

// https://www.techiedelight.com/find-peak-element-array/

class PeakElement
{
public:
	int find(const std::vector<int>& arr)
	{
		if (arr.size() == 1)
			return arr[0];

		if (arr.size() == 2)
			return std::max(arr[0], arr[1]);

		return findHelper(arr, 0, arr.size() - 1);
	}

private:
	int findHelper(const std::vector<int>& arr, int low, int high)
	{		
		if (low <= high)
		{
			int mid = low + (high - low) / 2;

			if (mid == 0 && (arr[mid] > arr[mid + 1]))
				return arr[mid];

			if (mid == arr.size() - 1 && arr[mid] > arr[mid - 1])
				return arr[mid];

			if ((mid - 1 >= 0) && (mid + 1 < arr.size()) && (arr[mid - 1] < arr[mid]) && (arr[mid] > arr[mid + 1]))
				return arr[mid];

			if ((mid + 1 < arr.size()) && arr[mid + 1] > arr[mid])
			{
				low = mid + 1;
			} else {
				high = mid - 1;
			}

			return findHelper(arr, low, high);
		}

		return -1;
	}
};

int main()
{
	std::vector<int> arr1{8, 9, 10, 2, 5, 6};
	std::vector<int> arr2{8, 9, 10, 12, 15};
	std::vector<int> arr3{ 10, 8, 6, 5, 3, 2 };
	std::vector<int> arr4{ 1,2,3,1 };
	PeakElement obj;
	int elem1 = obj.find(arr1);
	int elem2 = obj.find(arr2);
	int elem3 = obj.find(arr3);
	int elem4 = obj.find(arr4);
	std::cout << "Peak element is " << elem1 << std::endl;
	std::cout << "Peak element is " << elem2 << std::endl;
	std::cout << "Peak element is " << elem3 << std::endl;
	std::cout << "Peak element is " << elem4 << std::endl;
	return 0;
}