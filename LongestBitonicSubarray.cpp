#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/find-longest-bitonic-subarray-array/

class Bitonic
{
private:
	const std::vector<int>& arr;

public:
	Bitonic(const std::vector<int>& input)
		: arr(input)
	{

	}

	void find()
	{
		int max_len = 0;
		int start_indx = 0;
		int end_indx = 0;
		int j = 0;

		while (j + 1 < arr.size())
		{
			int len = 1;

			while (j + 1 < arr.size() && arr[j] < arr[j + 1])
			{
				j++; 
				len++;
			}
				
			while (j + 1 < arr.size() && arr[j] > arr[j + 1])
			{
				j++; 
				len++;
			}				

			if (len > max_len)
			{
				max_len = len;
				start_indx = j - len + 1;
				end_indx = j;
			}
		}


		std::cout << "Length of longest bitonic subarray is " << max_len << " and it is:" << std::endl;
		for (int i = start_indx; i <= end_indx; ++i)
		{
			std::cout << arr[i] << std::endl;
		}
	}
};

int main()
{
	std::vector<int> arr{ 3, 5, 8, 4, 5, 9, 10, 8, 5, 3, 4 };
	Bitonic obj(arr);
	obj.find();
	return 0;
}