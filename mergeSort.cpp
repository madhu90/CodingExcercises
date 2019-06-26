#include <iostream>
#include <vector>

class Sorter
{
private:
	std::vector<int>& arr;

public:
	Sorter(std::vector<int>& input)
		: arr(input)
	{
	}

	void print()
	{
		std::cout << "Array contents are" << std::endl;
		for (auto iter : arr)
		{
			std::cout << iter << "  ";
		}
		std::cout << std::endl;
	}

	void sort()
	{
		mergeSort(0, arr.size() - 1);
	}

private:
	void mergeSort(size_t low, size_t high)
	{
		if (low < high)
		{
			size_t mid = (low + high) / 2;
			mergeSort(low, mid);
			mergeSort(mid + 1, high);
			merge(low, mid, high);
		}
	}

	void merge(size_t low, size_t mid, size_t high)
	{
		std::vector<int> temp(high - low + 1, 0);
		size_t i = low;
		size_t j = mid + 1;
		size_t k = 0;

		while (i <= mid && j <= high)
		{
			if (arr[i] < arr[j])
			{
				temp[k++] = arr[i++];
			} else if (arr[j] < arr[i]) {
				temp[k++] = arr[j++];
			}
		}

		while (i <= mid)
			temp[k++] = arr[i++];

		while (j <= high)
			temp[k++] = arr[j++];

		// Copy temp to arr
		for (size_t ind = low; ind <= high; ++ind)
		{
			/**
			 * Why temp[ind - low]? If low = 1, it corresponds to
			 * the 2nd element in arr. However, it is the 1st element
			 * in temp. We should always start from the 0th index in
			 * temp
			 */
			arr[ind] = temp[ind - low];
		}
	}
};

int main()
{
	std::vector<int> arr{ 5, 4, 1, 8 , 7, 2, 6, 3 };
	Sorter obj(arr);
	obj.print();
	obj.sort();
	obj.print();
	return 0;
}