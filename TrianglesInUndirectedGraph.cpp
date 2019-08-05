#include <iostream>
#include <vector>

/**
 * We need to compute the cube of the adjacency matrix. The entries (i,j)
 * in A^n correspond to walks of length n from i to j. For triangles, we are
 * interested in walks of length 3 from a node to itself. That is, we are 
 * interested in (i,i) entries of A^3. For a triangle, we look for a walk that
 * looks liek this -> ijki. That is, the other two vertices are j and k. Now,
 * even ikji is a walk. So, the entries (i,i) repeat (n - 1) edges, or in this case
 * 2 edges. So, we must divide (i,i) in A^3 by 2, to get the unique triangles.
 * Moreover, the same triangle can get counted 3 times - starting for each of the
 * nodes, i, j and k. So, we further need to divide by 3. 
 * Totally, trace(A^3)/6 will give the unique triangles
 */

std::vector<std::vector<int>> multilpyWithSelf(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
{
	std::vector<std::vector<int>> C(A.size(), std::vector<int>(B.size(), 0));

	for (int i = 0; i < A.size(); ++i)
	{
		for (int j = 0; j < B.size(); ++j)
		{
			for (int k = 0; k < A.size(); ++k)
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	return C;
}

int trace(const std::vector<std::vector<int>>& adj)
{
	int sum = 0;

	for (int i = 0; i < adj.size(); ++i)
	{
		sum += adj[i][i];
	}

	return sum;
}

int countTriangles(std::vector<std::vector<int>> adj)
{
	std::vector<std::vector<int>> ASquare = multilpyWithSelf(adj, adj);
	std::vector<std::vector<int>> ACube = multilpyWithSelf(ASquare, adj);
	int tr = trace(ACube);
	return tr / 6;
}


int main()
{
	std::vector<std::vector<int>> adj{ 
		{0, 1, 1, 0},
		{1, 0, 1, 1}, 
		{1, 1, 0, 1}, 
		{0, 1, 1, 0}
	};

	int result = countTriangles(adj);
	std::cout << "Number of triangles in graph are " << result << std::endl;
	return 0;
}