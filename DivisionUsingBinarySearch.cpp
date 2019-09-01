#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/division-two-numbers-using-binary-search-algorithm/

class Divide
{
private:
	int num;
	int den;

public:
	Divide(int a, int b)
		: num(a), den(b)
	{

	}

	double compute()
	{
		// we want to compute result = x/y
		// or x = result*y
		if (den == 0)
			return std::numeric_limits<double>::infinity();

		int sign = 1;
		if ((num ^ den) < 0)
			sign = -1;

		double precision = 0.001;
		double low = 0;
		double high = std::numeric_limits<double>::max();
		double result = 0;

		while (1)
		{
			result = low + (high - low) / 2;
			double temp = result*den;

			if (std::abs(temp - num) <= precision)
				return result*sign;

			if (temp > num)
			{
				high = result;
			} else {
				low = result;
			}
		}
	}
};

int main()
{
	Divide obj(22, 7);
	double result = obj.compute();
	std::cout << "22/7 is " << result << std::endl;
	return 0;
}