#include <iostream>
#include <vector>

int duplicateElement(std::vector<int>& arr)
{
	int element = 0;

	for (auto iter : arr)
	{
		element ^= iter;
	}

	for (int i = 1; i < arr.size(); ++ i) {
		element ^= i;
	}

	return element;
}

int main()
{
	std::vector<int> arr{ 1, 2, 3, 4, 2 };
	int element = duplicateElement(arr);
	std::cout << "Duplicate element is " << element << std::endl;
	return 0;
}