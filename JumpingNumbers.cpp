#include <iostream>
#include <vector>
#include <queue>

// QUESTION: https://www.geeksforgeeks.org/print-all-jumping-numbers-smaller-than-or-equal-to-a-given-value/

class JumpingNumberGenerator
{
private:
	std::vector<int> numbers;

private:
	void bfs(int start, int target)
	{
		std::queue<int> queue;
		queue.push(start);

		while (!queue.empty())
		{
			int top = queue.front();			
			queue.pop();

			if (top < target)
			{
				numbers.push_back(top);

				// Get the last digit
				int last_digit = top % 10;

				if (last_digit == 0)
				{
					// you can't go in the left direction
					queue.push(10 * top + (last_digit + 1));
				} else if (last_digit == 9) {
					// you can't go in the right direction
					queue.push(10 * top + (last_digit - 1));
				} else {
					// you can go in both directions
					queue.push(10 * top + (last_digit - 1));
					queue.push(10 * top + (last_digit + 1));
				}
			}
		}
	}

public:
	void generate(int input)
	{
		// Push 0 onto the result
		if (input > 0)
			numbers.push_back(0);			

		// Do a level-wise traveral for all single digit numbers, to get
		// multiple digits
		for (int i = 1; i <= 9; ++i)
		{
			if (i < input)
				bfs(i, input);
		}
	}

	void print()
	{
		std::cout << "There are " << numbers.size() << " jumping numbers are" << std::endl;
		for (auto iter : numbers)
		{
			std::cout << iter << std::endl;
		}
	}
};

int main()
{
	JumpingNumberGenerator obj;
	obj.generate(105);
	obj.print();
	return 0;
}