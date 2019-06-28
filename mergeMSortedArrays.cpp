#include <iostream>
#include <vector>
#include <queue>

// The comparator used with std::priority_queue
// template <class T, class Container = vector<T>,
// class Compare = less<typename Container::value_type> > class priority_queue;
/* A binary predicate of form comp(a, b) which returns
 * true if a is considered to go before b in the strict weak ordering 
 * the function defines.
 * That is, if the comparator is defined as follows
 struct comp
 {
	bool operator()(T a, T b) const
	{
		return a > b;
	}
 };

 This will return true if a > b. So, a goes before b. That is, the larger
 element goes before the smaller element and the smallest element will be
 at the end and this is the top of the heap => min heap.
 */

struct Node
{
	int value;
	int array_idx;
	int element_idx;
};

struct comp
{
	bool operator()(const Node& a, const Node& b) const
	{
		return a.value > b.value;
	}
};

class ArrayMerger
{
private:
	std::vector<int> mergedArray;
	const std::vector<std::vector<int>>& inputArrays;

public:
	ArrayMerger(const std::vector<std::vector<int>>& inp)
		: inputArrays(inp)
	{
		size_t result_length = 0;

		for (size_t i = 0; i < inputArrays.size(); ++i)
		{
			for (size_t j = 0; j < inputArrays[i].size(); ++j)
			{
				result_length++;
			}
		}

		mergedArray.reserve(result_length);
	}

	void print()
	{
		std::cout << "Merged array" << std::endl;
		for (auto iter : mergedArray)
		{
			std::cout << iter << "   ";
		}

		std::cout << std::endl;
	}

	void merge()
	{
		std::priority_queue<Node, std::vector<Node>, comp> pq;

		// Fill first element
		for (int i = 0; i < inputArrays.size(); ++i)
		{
			pq.push({inputArrays[i][0], i, 0});
		}

		while (!pq.empty())
		{
			Node curr = pq.top();
			pq.pop();
			mergedArray.push_back(curr.value);

			if (curr.element_idx + 1 < inputArrays[curr.array_idx].size())
			{
				int new_idx = curr.element_idx += 1;
				int new_val = inputArrays[curr.array_idx][curr.element_idx];
				int new_arr = curr.array_idx;
				pq.push({new_val, new_arr, new_idx});
			}
		}
	}
};

int main()
{
	std::vector<std::vector<int>> arr
	{
		{10, 20, 30, 40},
		{15, 25, 35},
		{27, 29, 37, 48, 93},
		{32, 33}
	};

	ArrayMerger obj(arr);
	obj.merge();
	obj.print();
	return 0;
}