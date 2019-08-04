#include <iostream>
#include <vector>
#include <numeric>

// QUESTION: https://www.techiedelight.com/k-partition-problem-print-all-subsets/

class KPartition
{
private:
	const std::vector<int>& arr;
	std::vector<std::vector<int>> subsetsFound;

public:
	KPartition(const std::vector<int>& a)
		: arr(a)
	{
	}

	void find(int k)
	{
		int sum = std::accumulate(arr.begin(), arr.end(), 0);

		if ((sum % k) != 0) {
			std::cout << "The array cannot be partitioned into " << k << " subsets of equal sum" << std::endl;
		} else {
			std::cout << "The array can be partitioned into " << k << " subsets of equal sum, and they are:" << std::endl;
			std::vector<int> sumArray = std::vector<int>(k, sum / k);			
			subsetsFound.resize(k);
			kPartitionHelper(arr.size() - 1, sumArray, k);

			for (int i = 0; i < subsetsFound.size(); ++i)
			{
				std::cout << "Partition " << i << "    :    ";

				for (int j : subsetsFound[i])
				{
					std::cout << j << "  ";
				}

				std::cout << std::endl;
			}
		}
	}

private:

	bool check(std::vector<int>& sumArray)
	{
		bool result = true;

		for (int j : sumArray)
		{
			if (j != 0)
			{
				result = false;
				break;
			}				
		}

		return result;
	}

	bool kPartitionHelper(int curr_indx, 
		std::vector<int>& sumArray,		
		int k)
	{
		// Solution found
		if (check(sumArray))
		{			
			return true;
		}

		// Cannot continue
		if (curr_indx < 0)
			return false;

		bool included = false;

		for (int i = 0; i < k; ++i)
		{
			if (!included && (sumArray[i] - arr[curr_indx] >= 0))
			{				
				subsetsFound[i].push_back(arr[curr_indx]);
				sumArray[i] = sumArray[i] - arr[curr_indx];
				included = kPartitionHelper(curr_indx - 1, sumArray, k);

				if (!included)
				{
					subsetsFound[i].pop_back();
					sumArray[i] = sumArray[i] + arr[curr_indx];
				}					
			}
		}

		return included;
	}
};

int main()
{
	const std::vector<int> arr{7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4};
	int k = 5;
	KPartition obj(arr);
	obj.find(k);
	return 0;
}