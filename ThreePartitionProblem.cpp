#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <numeric>

// QUESTIONhttps://www.techiedelight.com/3-partition-problem/

class Partition
{
private:
	const std::vector<int>& arr;

public:
	Partition(const std::vector<int>& a)
		: arr(a)
	{

	}

	bool doExponential()
	{
		std::cout << "Exponential solution to 3 partition problem" << std::endl;
		int sum = std::accumulate(arr.begin(), arr.end(), 0);
		return (sum % 3) != 0 ? false : doExponentialHelper(arr.size() - 1, sum/3, sum/3, sum/3);
	}

private:
	bool doExponentialHelper(int curr_indx, int Asum, int Bsum, int Csum)
	{
		if ((Asum == 0) && (Bsum == 0) && (Csum == 0))
			return true;

		if (curr_indx < 0)
			return false;

		bool includeInA = false;
		bool includeInB = false;
		bool includeInC = false;

		// Current item becomes part of A
		if (Asum - arr[curr_indx] >= 0)
		{
			includeInA = doExponentialHelper(curr_indx - 1, Asum - arr[curr_indx], Bsum, Csum);
		} 

		// If current item is not a part of A, let's try B
		if (!includeInA && (Bsum - arr[curr_indx] >= 0))
			includeInB = doExponentialHelper(curr_indx - 1, Asum, Bsum - arr[curr_indx], Csum);

		// // If current item is not a part of A and B, let's try C
		if (!includeInA && !includeInB && (Csum - arr[curr_indx] >= 0))
			includeInC = doExponentialHelper(curr_indx - 1, Asum, Bsum, Csum - arr[curr_indx]);

		return includeInA || includeInB || includeInC;
	}
};

int main()
{
	std::vector<int> arr{7, 3, 2, 1, 5, 4, 8};
	Partition obj(arr);
	bool result1 = obj.doExponential();
	std::cout << "Partition exists " << result1 << std::endl;
	return 0;
}