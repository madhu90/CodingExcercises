#include <iostream>
#include <vector>
#include <queue>

// Question: https://www.techiedelight.com/find-minimum-passes-required-convert-negative-values-matrix/

struct Coordinates
{
	int x;
	int y;
};

class MatrixSearcher
{
private:
	std::vector<std::vector<int>> mat;
	std::vector<int> xcoords;
	std::vector<int> ycoords;
	int rows;
	int cols;

private:
	bool isvalid(int x, int y)
	{
		return x >= 0 && x < rows && y >= 0 && y < cols;
	}

	bool hasNegative()
	{
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (mat[i][j] < 0)
				{
					return true;
				}
			}
		}

		return false;
	}

public:
	MatrixSearcher()
		: rows(4), cols(5)
	{
		mat = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
		mat = { {-1, -9, 0, -1, 0},
				{-8, -3, -2, 9, -7},
				{2, 0, 0, -6, 0},
				{0, -7, -3, 5, -4 } };

		xcoords = {-1, 0, 0, 1};
		ycoords = {0, 1, -1, 0};
	}

	int minimumpasses()
	{
		int passes = 0;
		
		// Contains the original and then subsequent converted positive values
		std::queue<Coordinates> positiveValues;

		// Temporarily store all converted negative indices, till it is moved to
		// the previous queue
		std::queue<Coordinates> convertedValues;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (mat[i][j] > 0)
				{
					positiveValues.push({i, j});
				}
			}
		}

		// The idea is, the values will be moved from positiveValues to convertedValues,
		// when conversion is needed.		
		while (!positiveValues.empty())
		{
			std::swap(positiveValues, convertedValues);

			if (!convertedValues.empty() && hasNegative())
				passes++;
			
			while (!convertedValues.empty())
			{				
				Coordinates top = convertedValues.front();
				convertedValues.pop();

				for (size_t k = 0; k < xcoords.size(); ++k)
				{
					int newx = top.x + xcoords[k];
					int newy = top.y + ycoords[k];

					if (isvalid(newx, newy) && mat[newx][newy] < 0)
					{
						// Convert negative value to positive and push the new positive coordinates
						// to positiveValues queue;
						mat[newx][newy] = -mat[newx][newy];
						positiveValues.push({ newx, newy });
					}						
				}
			}

			// Incrementing this only when we have a negative value. We can't
			// rely on while loop because we could do nothing if all entries are
			// positive, OR
			// another option is to decrement passes before returning			
		}

		return passes;
	}
};

int main()
{
	MatrixSearcher obj;
	int passes = obj.minimumpasses();
	std::cout << "Minimum number of passes is " << passes << std::endl;
	return 0;
}