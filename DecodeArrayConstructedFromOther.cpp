#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/decode-the-array-constructed-another-array/

/**
 * Consider the input array => inp = [1, 2, 3, 4]
 * Transformed array 'A' has 6 elements => A = [1+2, 1+3, 1+4, 2+3, 2+4, 3+4]
 * That is, we choose combinations of 2 and sum them. For an array of size n, there are
 * n choose 2 number of such combinations m. That is:
 * m = n!/2*(n - 2)! => m = n(n-1)/2
 * n^2 - n - 2m = 0;
 * D = b^2 - 4ac = 1 + 8m
 * n = -b +sqrt(D)/2a => (1 + sqrt(1 + 8m))/2
 * Let us write out how A is obtained from inp:
 * A[0] = inp[0] + inp[1]
 * A[1] = inp[0] + inp[2]
 * A[2] = inp[0] + inp[3]
 * A[3] = inp[1] + inp[2] => A[n - 1] where n is 4
 * A[4] = inp[1] + inp[3]
 * A[5] = inp[2] + inp[3]
 * In order to get inp from A, computing inp[0] is sufficient:
 * inp[0] + inp[1] = A[0]
 * inp[0] + inp[2] = A[1]
 * => 2*inp[0] + inp[1] + inp[2] = A[0] + A[1]
 * inp[1] + inp[2] = A[n - 1]
 * => 2*inp[0] + A[n - 1] = A[0] + A[1]
 * => inp[0] = (A[0] + A[1] - A[n - 1])/2;
 * Once we have inp[0], we can compute all other entries of inp
 * inp[1] = A[0] - inp[0]
 * inp[2] = A[1] - inp[0]
 * => inp[i] = A[i - 1] - inp[0]
 */

class Decode {
private:
	const std::vector<int>& A;
	std::vector<int> inp;
	int m;
	int n;

public:
	Decode(const std::vector<int>& a)
		: A(a), m(a.size())
	{
		n = (1 + std::sqrt(1 + (8 * m))) / 2;
		inp.resize(n);
	}

	void get()
	{
		// Compute inp[0]
		inp[0] = (A[0] + A[1] - A[n - 1]) / 2;

		// Compute remaining entries of inp
		for (int i = 1; i < n; ++i) {
			inp[i] = A[i - 1] - inp[0];
		}

		for (int j : inp) {
			std::cout << j << "  ";
		}
		std::cout << std::endl;
	}
};

int main()
{
	std::vector<int> arr{ 3, 4, 5, 6, 5, 6, 7, 7, 8, 9 };
	Decode obj(arr);
	obj.get();
	return 0;
}