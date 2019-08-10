#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/inversion-count-array/

class InversionCount
{
private:
	std::vector<int>& arr;

public:
	InversionCount(std::vector<int>& a)
		: arr(a)
	{
	}

	int compute()
	{
		return computeHelper(0, arr.size() - 1);
	}

private:
	int computeHelper(int low, int high)
	{
		int inversion = 0;

		if (low < high)
		{
			int mid = (high + low) / 2;
			inversion += computeHelper(low, mid); // left inversions
			inversion += computeHelper(mid + 1, high); // right inversions
			inversion += splitInversions(low, mid, high); // split inversions
		}		

		return inversion;
	}

	int splitInversions(int low, int mid, int high)
	{
		std::vector<int> temp(high - low + 1);
		int count = 0;
		int k = 0;
		int i = low;
		int j = mid + 1;

		while (i <= mid && j <= high)
		{
			if (arr[j] < arr[i])
			{
				// Every subsequent element of i will be greater than j
				// So, include all of them
				count += (mid - i + 1);
				temp[k++] = arr[j++];				
			} else {
				temp[k++] = arr[i++];				
			}
		}

		while (i <= mid)
		{
			temp[k++] = arr[i++];
		}			

		while (j <= high)
		{
			temp[k++] = arr[j++];
		}

		// Copy over temp to original array
		for (i = low; i <= high; ++i)
		{
			arr[i] = temp[i - low];
		}

		return count;
	}
};

int main()
{
	std::vector<int> arr{ 1, 9, 6, 4, 5 };
	InversionCount obj(arr);
	std::cout << "Inversion count is " << obj.compute() << std::endl;
	return 0;
}