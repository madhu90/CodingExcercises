#include <iostream>
#include <vector>

// QUESTION: https://leetcode.com/problems/search-a-2d-matrix/

class MatrixSearcher
{
private:
	const std::vector<std::vector<int>>& mat;
	int rows;
	int cols;

public:
	MatrixSearcher(const std::vector<std::vector<int>>& m)
		: mat(m)
	{
		rows = mat.size();
		cols = mat[0].size();
	}

	bool find(int target)
	{
		int low = getLinIndex(0, 0);
		int high = getLinIndex(mat.size() - 1, mat[0].size() - 1);
		return binarySearch(low, high, target);
	}

private:
	bool binarySearch(int low, int high, int target)
	{
		while (low <= high)
		{
			int mid = low + (high - low) / 2;
			int midvalue = getValue(mid);

			if (midvalue == target)
				return true;

			if (target > midvalue)
			{
				low = mid + 1;
			} else {
				high = mid - 1;
			}			
		}

		return false;
	}

	int getValue(int linIndex)
	{
		std::pair<int, int> coords = getXY(linIndex);
		return mat[coords.first][coords.second];
	}

	int getLinIndex(int x, int y)
	{
		return cols*x + y;		
	}

	std::pair<int, int> getXY(int linIndex)
	{		
		return std::make_pair(linIndex / cols, linIndex % cols);
	}
};

int main()
{
	std::vector<std::vector<int>> mat{
		{1, 3, 5, 7},
		{10, 11, 16, 20},
		{23, 30, 34, 50}
	};
	
	int target = 3;
	MatrixSearcher obj(mat);
	bool result = obj.find(target);
	std::cout << "Found status is " << result << std::endl;
	return 0;
}