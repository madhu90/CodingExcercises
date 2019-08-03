#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/print-triplets-array-sum-less-equal-given-number/

class TripletFinder
{
public:
	void find(const std::vector<int>& arr, int number)
	{
		std::vector<int> triplet;
		findHelper(arr, number, triplet, 0, 0);
	}

private:
	void findHelper(const std::vector<int>& arr, 
		int number, 
		std::vector<int>& triplet, 
		int start,
		int running_sum)
	{
		if (triplet.size() == 3)
		{
			for (std::vector<int>::reverse_iterator iter = triplet.rbegin(); iter != triplet.rend(); ++iter)
			{
				std::cout << *iter << "  ";
			}

			std::cout << std::endl;
		}

		for (int i = start; i < arr.size(); ++i)
		{
			if (running_sum + arr[i] <= number)
			{
				running_sum += arr[i];
				triplet.push_back(arr[i]);
				findHelper(arr, number, triplet, i + 1, running_sum);
				if (!triplet.empty())
					triplet.pop_back();
				running_sum -= arr[i];
			}
		}
	}
};

int main()
{
	std::vector<int> arr{ 2, 7, 4, 9, 5, 1, 3 };
	int sum = 10;
	TripletFinder obj;
	obj.find(arr, sum);
	return 0;
}