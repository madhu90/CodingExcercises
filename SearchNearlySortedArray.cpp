#include <iostream>
#include <vector>

// QUESTION : https://www.techiedelight.com/search-nearly-sorted-array-ologn-time/

class NearlySorted
{
private:
	std::vector<int>& arr;

public:
	NearlySorted(std::vector<int>& a)
		: arr(a)
	{

	}

	int find(int element)
	{
		int indx = -1;
		int low = 0;
		int high = arr.size() - 1;

		while (low < high)
		{
			int mid = low + (high - low) / 2;

			if (arr[mid] == element)
			{
				indx = mid;
				break;
			}

			// Check if element is at the immediate left or right
			if ((mid - 1 >= 0) && arr[mid - 1] == element)
			{
				indx = mid - 1;
				break;
			}

			if ((mid + 1 < arr.size()) && arr[mid + 1] == element)
			{
				indx = mid + 1;
				break;
			}

			// Mid element, the netry on its left and right are not equal to the target.
			// So, we divide the search space by comparing current element with elements
			// at indices indx + 2 and indx - 2
			if (element < arr[mid])
			{
				// search on left side
				high = mid - 2;
			} else {
				low = mid + 2;
			}
		}

		return indx;
	}
};

int main()
{
	std::vector<int> arr1{2, 1, 3, 5, 4, 7, 6, 8, 9};
	std::vector<int> arr2{ 2, 1, 3, 5, 4, 7, 6, 8, 9 };
	NearlySorted obj1(arr1);
	NearlySorted obj2(arr2);
	int element1 = obj1.find(5);
	int element2 = obj2.find(10);
	std::cout << "5 is found at index " << element1 << std::endl;
	std::cout << "10 is found at index " << element2 << std::endl;
	return 0;
}