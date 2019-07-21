#include <iostream>
#include <string>

// QUESTION: https://www.techiedelight.com/find-minimum-number-possible-k-swaps/

class MinimumNumberGenerator
{
public:
	int generate(int number, int swap)
	{
		int min_number = number;
		std::string str(std::to_string(min_number));
		generateAndUpdateMinimum(str, min_number, swap, 0);
		return min_number;
	}

private:
	void generateAndUpdateMinimum(std::string& str,
		int& min_number, 
		int k, 
		int swap_count)
	{
		if (swap_count == k)
		{
			int num = std::stoi(str);
			if (num < min_number)
				min_number = num;
			return;
		}

		for (int i = 0; i < str.length(); ++i)
		{
			for (int j = i + 1; j < str.length(); ++j)
			{
				if (str[i] > str[j])
				{
					std::swap(str[i], str[j]);
					generateAndUpdateMinimum(str, min_number, k, swap_count + 1);
					std::swap(str[i], str[j]);
				}
			}			
		}
	}
};

int main()
{
	int num = 934651;
	std::string strnum(std::to_string(num));
	MinimumNumberGenerator obj;
	int k = 2;
	int min_number = obj.generate(num, k);
	std::cout << "Minimum number generated from " << num << " by doing " << k << " swaps is " << min_number << std::endl;
	return 0;
}