#include <iostream>
#include <vector>

class QuickSorter
{
private:
	std::vector<int>& data;

public:
	QuickSorter(std::vector<int>& input)
		: data(input)
	{

	}

	void sort()
	{
		sortHelper(0, data.size() - 1);
	}

	void print()
	{
		for (auto iter : data)
		{
			std::cout << iter << "  ";
		}

		std::cout << std::endl;
	}

private:
	void sortHelper(int low, int high)
	{
		if (low < high)
		{
			int pivot = swapEntries(low, high);
			sortHelper(low, pivot - 1);
			sortHelper(pivot + 1, high);			
		}
	}

	int swapEntries(int low, int high)
	{		
		int pivot = data[high];
		int pivotIndex = high;
		int largestFromLeft = low;
		int smallestFromRight = pivotIndex - 1;

		while (largestFromLeft <= smallestFromRight)
		{
			if (data[largestFromLeft] > pivot && data[smallestFromRight] <= pivot)
			{
				std::swap(data[largestFromLeft], data[smallestFromRight]);
				++largestFromLeft;
				--smallestFromRight;
			} else if (data[largestFromLeft] > pivot) {
				--smallestFromRight;
			} else {
				++largestFromLeft;
			}					
		}

		pivotIndex = largestFromLeft;
		std::swap(data[high], data[pivotIndex]);

		return pivotIndex;		
	}
};

int main()
{
	std::vector<int> arr{9, -3, 5, 2, 6, 8, -6, 1, 3};
	QuickSorter obj(arr);
	std::cout << "Before sorting" << std::endl;
	obj.print();
	obj.sort();
	std::cout << "After sorting" << std::endl;
	obj.print();
	return 0;
}