#include <iostream>
#include <vector>

void inPlaceMergeSort(std::vector<int>& x, std::vector<int>& y)
{
	// Pick the larger array
	size_t idx_x = 0;
	
	while (idx_x < x.size())
	{
		if (x[idx_x] > y[0])
		{
			std::swap(x[idx_x], y[0]);
			
			// Swap new element with first element
			// and move it to the right position
			size_t idx_y = 1;
			
			while (idx_y < y.size())
			{
				if (y[0] > y[idx_y])
					std::swap(y[0], y[idx_y]);
				++idx_y;
			}				
		}
		++idx_x;
	}	
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
	std::vector<int> x{1, 4, 7, 8, 10};
	std::vector<int> y{ 2, 3, 9 };
	std::cout << "x is: " << std::endl;
	print(x);
	std::cout << "y is: " << std::endl;
	print(y);
	inPlaceMergeSort(x, y);
	std::cout << "x is: " << std::endl;
	print(x);
	std::cout << "y is: " << std::endl;
	print(y);
	return 0;
}