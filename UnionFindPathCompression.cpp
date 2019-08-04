#include <iostream>
#include <vector>
#include <unordered_map>

// Reference: https://algorithms.tutorialhorizon.com/disjoint-set-union-find-algorithm-union-by-rank-and-path-compression/
//            https://www.cs.princeton.edu/courses/archive/spring13/cos423/lectures/UnionFind.pdf
//            http://typeocaml.com/2014/11/26/height-depth-and-level-of-a-tree/

class QuickUnion
{
private:
	// Key = node, Value - parent
	std::unordered_map<int, int> map;
	const std::vector<int>& arr;

public:

	QuickUnion(const std::vector<int>& a)
		: arr(a)
	{
	}

	void makeSet()
	{
		for (size_t i = 1; i <= arr.size(); ++i)
		{
			map[i] = arr[i - 1];
		}
	}

	int find(int x)
	{
		if (map[x] == x)
			return x;

		return find(map[x]);
	}

	void makeUnion(int x, int y)
	{
		int rootx = find(x);
		int rooty = find(y);

		if (rootx != rooty)
			map[rootx] = rooty;
	}

	void print()
	{
		for (size_t i = 1; i <= arr.size(); ++i)
		{
			std::cout << find(i) << "  ";
		}

		std::cout << std::endl;
	}
};

class UnionFindPathCompression
{
private:
	const std::vector<int>& arr;
	// Key is node and value is parent
	std::unordered_map<int, int> parent;
	// Key is node and value is rank
	std::unordered_map<int, int> rank;

public:
	UnionFindPathCompression(const std::vector<int>& a)
		: arr(a)
	{
	}

	void makeSet()
	{
		for (int i = 1; i <= arr.size(); ++i)
		{
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int find(int x)
	{
		if (x != parent[x])
		{
			// Path compression. The root of this set will be the
			// parent for all entries in it. Instead of having multiple
			// links to the root, each entity will have a direct link
			parent[x] = find(parent[x]);
		}

		return parent[x];
	}

	void makeUnion(int x, int y)
	{
		int rootx = find(x);
		int rooty = find(y);

		if (rootx == rooty)
			return;

		if (rank[rootx] > rank[rooty]) {
			parent[rooty] = rootx;
		} else if (rank[rooty > rank[rootx]]) {
			parent[rootx] = rooty;
		} else {
			parent[rootx] = rooty;
			rank[rooty]++;
		}
	}

	void print()
	{
		for (size_t i = 1; i <= arr.size(); ++i)
		{
			std::cout << find(i) << "  ";
		}

		std::cout << std::endl;
	}
};

int main()
{
	std::vector<int> arr{ 1, 2, 3, 4, 5 };
	std::cout << "Quick union" << std::endl;
	QuickUnion obj1(arr);
	obj1.makeSet();
	obj1.print();
	obj1.makeUnion(4, 3);
	obj1.print();
	obj1.makeUnion(2, 1);
	obj1.print();
	obj1.makeUnion(1, 3);
	obj1.print();

	std::cout << "Union find and path compression" << std::endl;
	UnionFindPathCompression obj2(arr);
	obj2.makeSet();
	obj2.print();
	obj2.makeUnion(4, 3);
	obj2.print();
	obj2.makeUnion(2, 1);
	obj2.print();
	obj2.makeUnion(1, 3);
	obj2.print();
	return 0;
}