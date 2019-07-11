#include <iostream>
#include <vector>


void printUniqueCombinationHelper(std::vector<int>& arr, int start, std::vector<int>& vec, int r)
{
	if (vec.size() == r)
	{
		for (auto iter : vec)
		{
			std::cout << iter << "  ";
		}
		std::cout << std::endl;

		return;
	}

	for (int i = start; i < arr.size(); ++i)
	{
		vec.push_back(arr[i]);
		printUniqueCombinationHelper(arr, i + 1, vec, r);
		vec.pop_back();
	}
}

void printUniqueCombination(std::vector<int>& arr, int r)
{
	std::vector<int> vec;
	printUniqueCombinationHelper(arr, 0, vec, r);
}

int main()
{	
	//std::vector<int> arr{ 1, 2, 3, 5, 7 };
	std::vector<int> arr{ 1, 2, 3 };
	int grps = 2;
	printUniqueCombination(arr, grps);
	return 0;
}