#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/quickselect-algorithm/
// Good explanation: https://rcoh.me/posts/linear-time-median-finding/

// Find the kth smallest element
class QuickSelect
{
private:
	std::vector<int> arr;

public:
	QuickSelect(const std::vector<int>& a)
		: arr(a)
	{

	}

	int findSmallest(int k)
	{
		int start = 0;
		int end = arr.size() - 1;
		int indx = findHelper(start, end, k);
		return indx;
	}

private:
	int findHelper(int low, int high, int k)
	{
		if (low == high)
			return arr[low];

		int pvt = partition(low, high);

		if (pvt == k)
		{
			return arr[pvt];
		} else if (pvt < k) {
			// search in right half
			return findHelper(pvt + 1, high, k);
		} else {
			// search in left half
			return findHelper(low, pvt - 1, k);
		}			
	}

	int partition(int low, int high)
	{
		int pivot = arr[high];
		int start = low;
		int end = high - 1;

		while (start <= end)
		{
			if (arr[start] > pivot && arr[end] <= pivot) {
				std::swap(arr[low], arr[high]);
				++start;
				--end;
			} else if (arr[start] > pivot) {
				--end;
			} else {
				++start;
			}
		}

		std::swap(arr[start], arr[high]);
		return start;
	}
};

int main()
{
	std::vector<int> arr{ 7, 4, 6, 3, 9, 1 };
	int k = 2;
	QuickSelect obj(arr);
	int result = obj.findSmallest(k);
	std::cout << k << "th smallest element is " << result << std::endl;
	return 0;
}