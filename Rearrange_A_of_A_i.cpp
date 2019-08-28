#include <iostream>
#include <vector>

// QUESTION  : https://www.techiedelight.com/rearrange-array-such-that-array-index-is-set-to-i/

/**
 * Original = [1, 3, 4, 2, 0];
 * New      = [4, 0, 3 , 1, 2];
 *
 * STEP 1 (Transformation - whatever is multiplied by 5 is what we eventually want. That is, 3 should become 0 (0*5))
 * 3 => 3 + 0*5 = 3
 * 2 => 2 + 1*5 = 7
 * 0 => 0 + 2*5 = 10
 * 4 => 4 + 3*5 = 19
 * 1 => 1 + 4*5 = 21
 *
 * STEP 2 (Now, we need to extract 0, 1, 2, 3, 4 from the modified values => divide by 5 and quotient will be these values
 * and remainder will be original values)
 */

class Rearrange
{
private:
	std::vector<int> arr;

public:
	Rearrange(std::vector<int>& a)
		: arr(a)
	{

	}

	void computeEfficient()
	{
		// STEP 1
		// 2 => 2 + 1 * 5 = 7
		// To get 2 back, take 7 % 5
		// To get 1, take 7 / 5
		for (int i = 0; i < arr.size(); ++i) {
			int indx = arr[i] % arr.size(); // To get 2 back, take 7 % 5
			arr[indx] += i*arr.size();
		}

		// STEP 2
		for (int i = 0; i < arr.size(); ++i) {
			arr[i] = arr[i]/arr.size(); // To get 1, take 7 / 5
		}

		for (int i = 0; i < arr.size(); ++i) {
			std::cout << arr[i] << "  ";
		}

		std::cout << std::endl;
	}
};

int main()
{
	std::vector<int> arr{ 1, 3, 4, 2, 0 };
	Rearrange obj(arr);
	obj.computeEfficient();
	return 0;
}