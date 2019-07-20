#include <iostream>
#include <vector>
#include <cmath>

bool isPrime(int n)
{
	if (n <= 3)
		return true;

	int upper_limit = std::ceil(std::sqrt(n));

	for (size_t i = 2; i <= upper_limit; ++i)
	{
		if (n % i == 0)
			return false;
	}

	return true;
}

int main()
{
	std::vector<int> nums;
	int N = 13;

	for (size_t i = 2; i <= N; ++i)
	{
		if (isPrime(i))
			nums.push_back(i);
	}

	std::cout << "Prime numbers less than " << N << " are:" << std::endl;

	for (auto iter : nums)
	{
		std::cout << iter << std::endl;
	}

	return 0;
}