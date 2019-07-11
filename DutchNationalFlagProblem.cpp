#include <iostream>
#include <vector>

void sorter(std::vector<int>& arr)
{
	int endOfZero = 0; // left of pivot
	int endOfOne = 0; // right of pivot
	int high = arr.size() - 1;
	int pivot = 1;
	
	while (endOfOne <= high)
	{
		if (arr[endOfOne] < pivot) // 0
		{
			std::swap(arr[endOfZero], arr[endOfOne]);
			endOfOne++;
			endOfZero++;
		} else if (arr[endOfOne] > pivot) { // 2
			std::swap(arr[endOfOne], arr[high]);
			high--;
		} else {
			endOfOne++;
		}
	}

	int x = 5;
}

void print(const std::vector<int>& arr)
{
	for (auto iter : arr)
	{
		std::cout << iter << "  ";
	}

	std::cout << std::endl;
}

int main()
{
	std::vector<int> arr{ 0, 1, 2, 2, 1, 0, 0, 2, 0, 1, 1, 0 };
	std::cout << "Before sorting" << std::endl;
	print(arr);
	sorter(arr);
	std::cout << "After sorting" << std::endl;
	print(arr);
	return 0;
}