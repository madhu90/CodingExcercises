#include <iostream>
#include <vector>
#include <unordered_map>

// QUESTION: https://www.techiedelight.com/surpasser-count-each-element-array/

class SurpasserCount
{
private:
	std::vector<int> arr;
	std::unordered_map<int, int> map;

public:
	SurpasserCount(std::vector<int>& a)
		: arr(a)
	{
		// Initialize map
		for (int j : arr)
		{
			map[j] = 0;
		}
	}

	void compute()
	{
		std::vector<int> temp = arr;
		computeHelper(0, arr.size() - 1, temp);
		int end_index = (arr.size() - 1);

		for (int i = 0; i < arr.size(); ++i)
		{
			// We have information about the number of elements to
			// the right which are smaller than arr[i] (in the map)
			// We are interested in finding the number of elements
			// greater. So, we subtract the contents of the map from
			// the length of the array and additionally subtract the current
			// index to get all the elements to thr right of it
			std::cout << end_index - i - map[arr[i]] << "  ";
		}

		std::cout << std::endl;
	}

private:
	void computeHelper(int low, int high, std::vector<int>& input)
	{
		if (low < high)
		{
			int mid = (low + high) / 2;
			computeHelper(low, mid, input);
			computeHelper(mid + 1, high, input);
			merge(low, mid, high, input);
		}
	}

	void merge(int low, int mid, int high, std::vector<int>& input)
	{		
		int invCount = 0;
		std::vector<int> temp(high - low + 1, 0);
		int i = low;
		int j = mid + 1;
		int k = 0;

		while (i <= mid && j <= high)
		{
			if (input[i] < input[j])
			{			
				// Element to the right is greater. This map stores
				// the number of elements with which input[i] forms
				// an inversion pair
				map[input[i]] += invCount;
				temp[k++] = input[i++];
			} else {
				// input[i] > input[j]. That is, element to left is
				// greater than element to the right => Increase inversion count
				invCount ++;				
				temp[k++] = input[j++];
			}
		}

		while (i <= mid)
		{	
			// The right array had smaller elements than the left array
			// These add to the inversion. 
			// Consider the array [4, 6, 3]. Here, high is 3 and low is 4.
			// The first iteration will increment inversion count => 3 is lesser
			// than 4. It must also be lesser than 6. This is because, the previous
			// merge step on an array of size 2 [4, 6] should have sorted it. So, right
			// here, we have 2 inversion pairs => (4,3) and (6,3). So, increment the map
			// with this count
			map[input[i]] += invCount;
			temp[k++] = input[i++];
		}

		while (j <= high)
		{
			temp[k++] = input[j++];
		}

		// Copy over elements
		for (i = low; i <= high; ++i)
		{
			input[i] = temp[i - low];
		}
	}
};

int main()
{
	std::vector<int> arr{ 4, 6, 3, 9, 7, 10 };
	SurpasserCount obj(arr);
	obj.compute();
	return 0;
}