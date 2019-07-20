#include <vector>
#include <iostream>
#include <cstdlib>

class SmallestElementComputer
{

private:
	int partition(std::vector<int>& arr, int left, int right, int pivIndex)
	{
		std::swap(arr[pivIndex], arr[right]);
		int pivot = arr[right];
		int greaterThanPivot = left;
		int smallerThanPivot = right - 1;

		while (greaterThanPivot <= smallerThanPivot)
		{
			if (arr[greaterThanPivot] > pivot && arr[smallerThanPivot] < pivot)
			{
				std::swap(arr[greaterThanPivot], arr[smallerThanPivot]);
				--smallerThanPivot;
				++greaterThanPivot;
			} else if (arr[greaterThanPivot] < pivot) {
				++greaterThanPivot;
			} else {
				--smallerThanPivot;
			}
		}

		std::swap(arr[greaterThanPivot], arr[right]);

		return greaterThanPivot;
	}

	int select(std::vector<int>& arr, int left, int right, int k)
	{
		if (left == right)
			return arr[left];

		int pivot = left + std::rand() % (left - right + 1);
		pivot = partition(arr, left, right, pivot);

		if (k == pivot)
			return arr[k];

		if (k < pivot)
		{
			// Look to left
			return select(arr, left, pivot - 1, k);
		} else {
			// Look to right
			return select(arr, pivot + 1, right, k);
		}
	}

public:
	int find(int k, std::vector<int> arr)
	{
		return select(arr, 0, arr.size() - 1, k);
	}
};

int main()
{
	std::vector<int> arr{ 7,4,6,3,9,1 };
	int k = 2;
	SmallestElementComputer obj;
	int element = obj.find(k, arr);
	std::cout << k << "th smallest element is " << element << std::endl;
	return 0;
}