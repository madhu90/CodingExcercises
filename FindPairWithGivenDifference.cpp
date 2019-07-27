#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

class PairFinder
{
public:
	std::set<std::pair<int, int>> find(const std::vector<int>& arr, int diff)
	{
		// map of array element and its index
		std::unordered_map<int, int> map;
		std::set<std::pair<int, int>> result;

		for (size_t i = 0; i < arr.size(); ++i)
		{
			auto found1 = map.find(arr[i] - diff);
			auto found2 = map.find(arr[i] + diff);

			if (found1 != map.end()) {
				result.insert(std::make_pair(found1->first, arr[i]));
			} else if (found2 != map.end()) {
				result.insert(std::make_pair(found2->first, arr[i]));
			} else {
				map[arr[i]] = i;	
			}
		}

		return result;
	}
};

int main()
{
	std::vector<int> arr{1, 5, 2, 2, 2, 5, 5, 4};
	int k = 3;
	PairFinder obj;
	std::set<std::pair<int, int>> result = obj.find(arr, k);
	std::cout << "Pairs with difference " << k << " are:" << std::endl;

	for (auto iter : result)
	{
		std::cout << "(" << iter.first << ", " << iter.second << ")" << std::endl;
	}
	return 0;
}