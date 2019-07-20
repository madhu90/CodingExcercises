#include <iostream>
#include <vector>

class NQueensSolver
{
private:
	std::vector<std::vector<int>> mat;
	int rows;
	int cols;
	int numsolns;
	int printResults;
	int sample;

public:
	NQueensSolver(int sz, bool printR = false)
		: rows(sz), cols(sz), numsolns(0), printResults(printR), sample(0)
	{
		mat = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
	}

private:
	void print()
	{
		if (printResults && sample < 3) {
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j) {
					if (mat[i][j]) {
						std::cout << 'Q' << "  ";
					} else {
						std::cout << '_' << "  ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			++sample;
		}
	}

	void solveRow(int currrow)
	{
		if (currrow == rows)
		{
			// One solution found. Print and backtrack
			++numsolns;
			print();
			return;
		}

		for (int i = 0; i < cols; ++i)
		{
			if (safe(currrow, i))
			{
				mat[currrow][i] = 1;
				solveRow(currrow + 1);
				mat[currrow][i] = 0;
			}
		}
	}

	// Do 2 queens conflict each other ? We only need check from
	// 0 to x
	bool safe(int x, int y)
	{		
		int i;
		int j;

		// Check columns
		for (i = 0; i < x; ++i)
		{
			if (mat[i][y] == 1)
			{
				return false;
			}			
		}

		// Check left diagonal		
		for (i = x,  j = y; i >= 0 && j >= 0; --i, --j)
		{
			if (mat[i][j] == 1)
				return false;
		}

		// Check right diagonal
		for (i = x, j = y; i >= 0 && j < cols; --i, ++j)
		{
			if (mat[i][j] == 1)
				return false;
		}
		return true;
	}

public:
	void solve()
	{
		solveRow(0);
	}

	const int getTotalSolutions() const
	{
		return numsolns;
	}
};

int main()
{
	int N = 8;
	NQueensSolver obj(N, true);
	obj.solve();
	std::cout << " The number of solutions to N Queens  problem for a board of size " << N << "x" << N << " is " << obj.getTotalSolutions() << std::endl;
	return 0;
}