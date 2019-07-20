#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class MaxElementFinder
{
public:
	int findMax(const std::vector<int>& arr, int k)
	{
		// Min heap
		std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

		// Push 1st k elements into heap
		for (size_t i = 0; i < k; ++i)
		{
			pq.push(arr[i]);
		}

		// Compare root to other elements
		int indx = k;
		while (indx < arr.size())
		{
			if (arr[indx] > pq.top())
			{
				pq.pop();
				pq.push(arr[indx]);
			}

			++indx;
		}

		return pq.top();
	}
};

int main()
{
	std::vector<int> arr{ 7, 4, 6, 3, 9, 1 };
	int k = 2;
	MaxElementFinder obj;
	int element = obj.findMax(arr, k);
	std::cout << k << "th largest element is " << element << std::endl;
	return 0;
}