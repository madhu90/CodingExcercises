#include <iostream>
#include <vector>
#include <string>

// Link: Techie deligh: https://www.techiedelight.com/combinations-of-words-formed-replacing-given-numbers-corresponding-english-alphabet/
// 1   --->    65
// 2   --->    66
// 3   --->    67

class AphabetConverter
{
private:
	const std::string alphabets;

public:
	AphabetConverter()
		: alphabets("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
	{
	}

	void convert(const std::vector<int>& arr)
	{
		std::string converted;
		convertHelper(arr, 0, converted);
	}

private:
	void convertHelper(const std::vector<int>& arr, int curr_index, std::string convertered)
	{
		if (curr_index == arr.size())
		{
			std::cout << convertered << std::endl;
			return;
		}

		int sum = 0;

		for (int i = curr_index; i < arr.size(); ++i)
		{
			sum = (sum * 10) + arr[i];

			if (sum <= 26)
				convertHelper(arr, i + 1, convertered + alphabets[sum - 1]);
		}
	}
};

int main()
{
	std::vector<int> arr{ 1, 2, 2 };
	AphabetConverter obj;
	obj.convert(arr);	
	return 0;
}