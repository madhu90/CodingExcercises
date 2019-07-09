#include <iostream>
#include <vector>

// Sort binary array in linear time
// We will be using the quick-sort logic

void sorter(std::vector<int>& arr)
{
	int pivot = 1;
	int swapIdx = 0;

	for (size_t iter = 0; iter < arr.size(); ++iter)
	{
		if (arr[iter] < pivot)
		{
			std::swap(arr[iter], arr[swapIdx]);
			++swapIdx;
		}
	}
}

void print(std::vector<int>& arr)
{
	for (auto iter : arr)
	{
		std::cout << iter << "  ";
	}

	std::cout << std::endl;
}

int main()
{
	std::vector<int> arr{1, 0, 0, 0, 1, 0, 1, 1};
	std::cout << "Before sorting" << std::endl;
	print(arr);
	sorter(arr);
	std::cout << "After sorting" << std::endl;
	print(arr);
	return 0;
}