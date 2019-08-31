#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

/* Distinct subsets of a set. For example:
 * For the array : [1 3 1] the distinct subsets are
 * {}
 * {1}
 * {3}
 * {1, 3}
 * {1, 1}
 * {1, 3, 1}
 */

class SubsetComputer
{
private:
	std::vector<int> arr;
	std::unordered_set<std::string> subs; // to only store unique entries

public:
	SubsetComputer(const std::vector<int>& a)
		: arr(a)
	{
		// To club duplicates together.
		std::sort(arr.begin(), arr.end());
	}

	void find()
	{
		std::string temp;
		compute(0, temp);
		std::cout << "The subsets are" << std::endl;
		for (auto iter : subs)
		{
			if (iter.empty())
			{
				std::cout << "{empty}" << std::endl;
			} else {
				std::cout << "{" << iter << "}" << std::endl;
			}			
		}			
	}

private:
	void compute(int start, std::string temp)
	{
		subs.insert(temp);
		if (start == arr.size())
		{
			return;
		}

		for (int i = start; i < arr.size(); ++i) {
			compute(i + 1, temp + std::to_string(arr[i]));			
		}
	}
};

int main()
{
	std::vector<int> arr{ 1, 3, 1 };
	SubsetComputer obj(arr);
	obj.find();
	return 0;
}