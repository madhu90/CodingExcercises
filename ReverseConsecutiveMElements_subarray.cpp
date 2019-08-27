#include <iostream>
#include <vector>

// QUESTION : https://www.techiedelight.com/reverse-every-consecutive-m-elements-given-subarray/

class ReverseSubGrps
{
private:
	std::vector<int> arr;
	int start;
	int end;
	int m;

public:
	ReverseSubGrps(std::vector<int> a, int i, int j, int grp)
		: arr(a), start(i), end(j), m(grp)
	{
	}

	void print()
	{
		for (int j : arr)
		{
			std::cout << j << "  ";
		}
		std::cout << std::endl;
	}

	void perform()
	{
		int groups = ((end - start) + 1) / m;
		int i;
		int j = start - 1;
		int k;
		int l;

		while (groups-- > 0)
		{
			i = j + 1;
			j = i + m - 1;
			k = i;
			l = j;

			while (k < l)
			{
				std::swap(arr[k], arr[l]);
				k++;
				l--;
			}
		}

		std::cout << "i = " << start << " , j = " << end << std::endl;
		print();
	}
};

int main()
{
	std::vector<int> arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	ReverseSubGrps obj1(arr, 1, 7, 3);
	obj1.perform();	
	ReverseSubGrps obj2(arr, 1, 9, 3);
	std::cout << std::endl;
	obj2.perform();
	ReverseSubGrps obj3(arr, 3, 5, 3);
	std::cout << std::endl;
	obj3.perform();
	ReverseSubGrps obj4(arr, 3, 4, 3);
	std::cout << std::endl;
	obj4.perform();
	return 0;
}