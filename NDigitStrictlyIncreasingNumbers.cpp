#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/find-n-digit-strictly-increasing-numbers-bottom-top-approach/

class BruteForceStrictlyIncreasing
{
private:
	int numberOfDigits;

public:
	BruteForceStrictlyIncreasing(int N)
		: numberOfDigits(N)
	{

	}

	void find()
	{
		helper(1, 10, 0, 0);
	}

private:
	void helper(int startdigit, int power, int numdigits, int number)
	{
		if (numdigits == numberOfDigits)
		{
			std::cout << number << std::endl;
			return;
		}

		for (int i = startdigit; i <= 9; ++i)
		{
			helper(i + 1, power, numdigits + 1, number*power + i);
		}
	}
};

int main()
{
	int N = 8;
	BruteForceStrictlyIncreasing obj1(N);
	obj1.find();
	return 0;
}