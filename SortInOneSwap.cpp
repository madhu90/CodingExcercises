#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/sort-array-using-one-swap/

void sortInOneSwap(std::vector<int>& arr)
{
	int swapEnd = arr.size() - 1;
	int swapStart = 0;

	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (arr[i - 1] > arr[i]) {
			swapStart = i - 1;
			break;
		}
	}

	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (arr[i] > arr[swapStart]) {
			swapEnd = i - 1;
			break;
		}
	}

	std::swap(arr[swapStart], arr[swapEnd]);
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
	std::vector<int> arr{ 3, 5, 6, 9, 8, 7 };
	print(arr);
	sortInOneSwap(arr);
	print(arr);
	return 0;
}