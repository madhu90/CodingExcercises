#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// QUESTION: https://www.techiedelight.com/print-all-quadruplets-with-given-sum-4-sum-problem-extended/

class QuadrupletFinder
{
private:
	const std::vector<int>& data;
	std::vector<int> arr;

public:
	QuadrupletFinder(const std::vector<int>& d)
		: data(d)
	{
		// quadruplet
	}

	void find(int sum)
	{
		findHelper(0, sum);
	}

private:
	void findHelper(int start, int remaining)
	{
		if (arr.size() == 4 && remaining == 0)
		{
			for (int j : arr)
			{
				std::cout << j << "  ";
			}
			std::cout << std::endl;
			return;
		}

		if (remaining < 0)
			return;

		for (int i = start; i < data.size(); ++i)
		{
			if (remaining - data[i] >= 0)
			{
				arr.push_back(data[i]);
				findHelper(i + 1, remaining - data[i]);
				if (!arr.empty())
					arr.pop_back();
			}
		}
	}
};

class HashBasedFinder
{
private:
	std::unordered_map<int, std::pair<int, int>> map; // key = sum and value = pair

public:
	bool find(std::vector<int>& arr, int sum)
	{
		for (int i = 0; i < arr.size(); ++i) {
			for (int j = i + 1; j < arr.size(); ++j) {
				int val = sum - (arr[i] + arr[j]);

				if (map.find(val) == map.end()) {
					map[arr[i] + arr[j]] = std::make_pair(i, j);
				} else {
					std::pair<int, int> data = map.find(val)->second;
					if (data.first != i && data.first != j && data.second != i && data.second != j)
					{
						//std::cout << arr[i] << "  " << arr[j] << "  " << arr[data.first] << "  " << arr[data.second] << std::endl;
						return true;
					}						
				}
			}
		}
		return false;
	}

	void print(std::vector<int> arr, int sum)
	{
		int low = 0;
		int high = 0;
		std::sort(arr.begin(), arr.end());
		// Consider array [0, 1, 2, 3, 4, 5, 7, 9]. If you look at every pair, we will be able
		// to find 4 elements only if they are available. That is, let's consider the pairs:
		// (0,1), (1,2), (2,3), (3,4), (4,5), (5,7) and (7,9). There is no point considering
		// pairs (5,7) and (7,9) because, with (5,7), you are only left with 9 and with (7,9), you
		// are left with nothing. That is why the following loops end at arr.size() - 4 and arr.size() - 3
		for (int i = 0; i < arr.size() - 4; ++i) {
			for (int j = i + 1; j < arr.size() - 3; ++j) {
				int val = sum - (arr[i] + arr[j]);
				low = j + 1;
				high = arr.size() - 1;

				while (low < high)
				{
					if (arr[low] + arr[high] < val) {
						low++;
					} else if (arr[low] + arr[high] > val) {
						high--;
					} else {
						std::cout << arr[i] << "  " << arr[j] << "  " << arr[low] << "  " << arr[high] << std::endl;
						low++;
						high--;
					}
				}
			}
		}
	}
};

int main()
{
	std::vector<int> arr{ 2, 7, 4, 0, 9, 5, 1, 3 };
	/*QuadrupletFinder obj1(arr);
	obj1.find(20);*/
	HashBasedFinder obj2;
	if (obj2.find(arr, 20))
		obj2.print(arr, 20);
	return 0;
}