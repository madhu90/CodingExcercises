#include <iostream>
#include <vector>

// Mereg sort without using a temporary variable
class MergeSort {
private:
	std::vector<int>& arr;

public:
	MergeSort(std::vector<int>& a)
		: arr(a)
	{

	}

	void compute()
	{
		print();
		sort(0, arr.size() - 1);
		print();
	}

private:
	void sort(int low, int high)
	{
		if (low < high)
		{
			int mid = low + (high - low) / 2;
			sort(low, mid);
			sort(mid + 1, high);
			merge(low, mid, high);
		}
	}

	void merge(int low, int mid, int high)
	{
		int start1 = low;
		int start2 = mid + 1;

		while (start1 < mid && start2 < high)
		{
			if (arr[start1] > arr[start2]) {
				std::swap(arr[start1], arr[start2]);
				if (sortsubarray(start2, high)) {
					++start2;
				} 							
			} 
			++start1;
		}

		// start2 == high
		while (start1 <= mid)
		{
			if (arr[start1] > arr[start2])
				std::swap(arr[start1], arr[start2]);
			++start1;
		}

		// start1 == mid
		while (start2 <= high)
		{
			if (arr[start1] > arr[start2])
				std::swap(arr[start1], arr[start2]);
			if (sortsubarray(start2, high))
				++start2;
		}
	}

	void print()
	{
		std::cout << "The array is " << std::endl;
		for (int j : arr)
		{
			std::cout << j << "  ";
		}
		std::cout << std::endl;
	}

	bool sortsubarray(int start, int end)
	{		
		int curr = start;
		int temp = start + 1;
		
		while (temp <= end)
		{
			if (arr[curr] > arr[temp])
			{
				std::swap(arr[curr], arr[temp]);
				curr = temp;
			}
			++temp;
		}

		return curr == start;
	}
};

int main()
{
	std::vector<int> arr1{ 1, 9, 6, 4, 5 };
	std::vector<int> arr2{4, 6, 3, 9, 7, 10};
	std::vector<int> arr3{1, 9, 3, 6, 4, 5};
	std::vector<int> arr4{ 1, 2, 3, 4, 5 };
	MergeSort obj1(arr1);
	MergeSort obj2(arr2);
	MergeSort obj3(arr3);
	MergeSort obj4(arr4);
	obj1.compute();
	obj2.compute();
	obj3.compute();
	obj4.compute();
	return 0;
}