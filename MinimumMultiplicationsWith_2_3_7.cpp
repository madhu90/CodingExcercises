#include <iostream>
#include <vector>

// QUESTION: https://www.geeksforgeeks.org/minimum-multiplications-with-2-3-7-to-make-two-numbers-equal/

/**
 * If you need to multiply a number with 2, 3, or 7 to make it equal to another number, 
 * then, it must be a multiple of these numbers as well. That is:
 *
 * num1 = x * 2^x1 * 3^x2 * 7^x3
 * num2 = y * 2^y1 * 3^y2 * 7^y3
 *
 * Only if x and y are equal, multiplying it with 2, 3, or 7 will translate to the other number.
 * And, the minimum number os operations will be the sum of the absoluate difference of the powers
 * Note that, x and y cannot be a multiple of 2, 3, or 7 because, if it were, we would pulled it out
 * and added it to the exponent.
 * So, we need to filter the number by dividing it by 2, 3, and 7 and return the result
 */

class ExponentCalculator
{
private:
	std::vector<int> exps;
	int remaining;

public:
	ExponentCalculator(int number)
	{
		int count = 0;

		// Test with 2
		if (number % 2 == 0)
		{
			while (number % 2 == 0)
			{
				number /= 2;
				count++;
			}

			exps.push_back(count);
		} else {
			exps.push_back(0);
		}
		
		count = 0;

		// Test with 7
		if (number % 7 == 0)
		{
			while (number % 7 == 0)
			{
				number /= 7;
				count++;
			}

			exps.push_back(count);
		} else {
			exps.push_back(0);
		}
		
		count = 0;

		// Test with 3
		if (number % 3 == 0)
		{
			while (number % 3 == 0)
			{
				number /= 3;
				count++;
			}

			exps.push_back(count);
		} else {
			exps.push_back(0);
		}		

		remaining = number;
	}

	int getremainder() const
	{
		return remaining;
	}

	std::vector<int> getexponents()
	{
		return exps;
	}
};

class MinimumMultiplicationCalculator
{
public:
	int compute(int x, int y)
	{
		int result = 0;
		ExponentCalculator obj1(x);
		ExponentCalculator obj2(y);

		if (obj1.getremainder() == obj2.getremainder() && obj1.getremainder() != 1)
		{
			std::vector<int> exps1 = obj1.getexponents();
			std::vector<int> exps2 = obj2.getexponents();

			for (size_t i = 0; i < 3; ++i)
			{
				result += std::abs(exps1[i] - exps2[i]);
			}
		}

		return result;
	}
};

int main()
{
	MinimumMultiplicationCalculator obj;
	int result = obj.compute(7, 2);

	if (result == 0) {
		std::cout << " The numbers cannot be made equal" << std::endl;
	} else {
		std::cout << " Minimum number of operatons is " << result << std::endl;
	}
	return 0;
}