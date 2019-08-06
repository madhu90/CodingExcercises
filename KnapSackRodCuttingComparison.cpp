#include <iostream>
#include <vector>

/**
 * How to identify a 1D and 2D problem? Source: https://www.quora.com/In-DP-problems-how-do-you-know-whether-to-use-a-1D-array-table-or-a-2D-array-table
 * When you analyze a problem, what you really search for is a function with some number 
 * of parameters that represent a state. Then you try to relate the current state to some 
 * previous states of the function.
 *
 * Now, if you have one parameter that describes the state(eg. fibonacci numbers) you use 
 * 1-D array. Why? Because arr[0] represents the value of the function for state 0, arr[1]
 * represents the value of the function for state 1 and so on.
 *
 * If you have k parameters that represent the state of the function than you have k-dimensional
 * array and arr[x1][x2][x3][..][xk] represents the value of the function for the state (x1,x2,x3,..,xk). 
 * The only things that really matter are these:
 *   a) representation of a state (by some number of parameters)
 *   b) relating a state to some other states(devising a transition between states)
 *
 * Recursion computes the values of the function at some state on the fly and in DP you actually 
 * store them because you want to avoid recomputation and that's all.
 * 
 * In the following examples, note that, for the rid cutting problem, the recursive function findHelper
 * just takes the sum of the partitions as the input. So, an array is sufficient to represent the states
 * findHelper(0), findHelper(1) etc. The repeated computations here are different permutations of a split.
 * For example, for a rod of length 4, there are 8 splits -> [4,0], [2 1 1], [1 2 1], [3 1], [2 2], [1 3], 
 * [1 1 2], [1 1 1 1]. Here, [1 2 1], [2 1 1] and [1 1 2] are essentially the same
 *
 * In the knapsack example, the recursive function findHelper takes 2 inputs - the starting index and the
 * sum of the weights. So, each state is represented as 2 dimensions and we need a matrix to represent
 * these states. The repeated computations here are for a specific state - a certain index and a 
 * given weight
 */

int count = 0;

void print(
	int target,
	int sum,
	std::vector<int> combs)
{
	if (sum == target)
	{
		++count;
		for (auto iter : combs)
		{
			std::cout << iter << "  ";
		}

		std::cout << std::endl;
		return;
	}

	if (sum > target)
		return;

	for (int i = 1; i <= target; ++i)
	{
		combs.push_back(i);
		print(target, sum + i, combs);
		if (!combs.empty())
			combs.pop_back();
	}
}

void findSubsets(const std::vector<int>& arr, std::vector<int>& subs, int start)
{
	if (subs.size() > 0)
		count++;

	for (auto iter : subs)
	{
		std::cout << iter << "  ";
	}

	std::cout << std::endl;

	for (int i = start; i < arr.size(); ++i) {
		subs.push_back(arr[i]);
		findSubsets(arr, subs, i + 1);
		if (!subs.empty())
			subs.pop_back();
	}
}

class BruteForceRodLengthProblem
{
private:
	const std::vector<int>& price;
	int length;
	std::vector<int> combs;	
	int maxProfit;

public:
	BruteForceRodLengthProblem(const std::vector<int>& p)
		: price(p)
	{
		length = price.size();
		maxProfit = 0;
	}

	int find()
	{
		findHelper(0);
		return maxProfit;
	}

private:
	void findHelper(int sum)
	{
		if (sum == length)
		{
			int pft = 0;
			for (auto iter : combs)
			{
				pft += price[iter - 1];
			}

			if (pft > maxProfit)
				maxProfit = pft;

			return;
		}

		if (sum > length)
			return;

		for (int i = 1; i <= length; ++i)
		{
			combs.push_back(i);
			findHelper(sum + i);
			if (!combs.empty())
				combs.pop_back();
		}
	}
};

void BruteForceMaxProfit(int target,
	int sum,
	std::vector<int> combs,
	const std::vector<int> price,
	int &mxPrf)
{
	if (sum == target)
	{
		int pft = 0;
		for (auto iter : combs)
		{
			pft += price[iter - 1];
		}

		if (pft > mxPrf)
			mxPrf = pft;

		return;
	}

	if (sum > target)
		return;

	for (int i = 1; i <= target; ++i)
	{
		combs.push_back(i);
		BruteForceMaxProfit(target, sum + i, combs, price, mxPrf);
		if (!combs.empty())
			combs.pop_back();
	}
}

class BruteForceZeroOneKnapSack
{
private:
	const std::vector<int>& val;
	const std::vector<int> wt;
	int W;
	std::vector<int> subs;
	int maxPrf;

public:
	BruteForceZeroOneKnapSack(const std::vector<int>& v, const std::vector<int>& w, int target)
		: val(v), wt(w), W(target)
	{
		maxPrf = 0;
	}

	int find()
	{
		findHelper(0, 0);
		return maxPrf;
	}

private:
	void findHelper(int start, int sum)
	{
		if (sum > W)
			return;

		int value = 0;

		for (auto iter : subs)
		{
			value += val[iter];
		}

		if (value > maxPrf)
			maxPrf = value;

		for (int i = start; i < val.size(); ++i)
		{
			subs.push_back(i);
			findHelper(i + 1, sum + wt[i]);
			if (!subs.empty())
				subs.pop_back();
		}
	}
};

/*void BruteForceKnapSack(
	const std::vector<int>& val,
	const std::vector<int> wt,
	int W,
	std::vector<int>& subs,
	int start,
	int sum,
	int& maxPrf)
{
	if (sum > W)
		return;

	int value = 0;

	for (auto iter : subs)
	{
		value += val[iter];
	}

	if (value > maxPrf)
		maxPrf = value;

	for (int i = start; i < val.size(); ++i)
	{
		subs.push_back(i);
		BruteForceKnapSack(val, wt, W, subs, i + 1, sum + wt[i], maxPrf);
		if (!subs.empty())
			subs.pop_back();
	}
}*/

int main()
{
	// Rod cutting
	const std::vector<int> price{ 1, 5, 8, 9, 10, 17, 17, 20 };
	BruteForceRodLengthProblem obj1(price);
	std::cout << "Max profit for rod cutting using brute force approach is is " << obj1.find() << std::endl;

	/*int target = price.size();
	std::vector<int> combs1;
	int mx = 0;
	std::cout << "Log of length " << target << " can be split up as shown below:" << std::endl;
	print(target, 0, combs1);
	std::cout << "There are totally " << count << " number of ways in which the rod of length " << target << " can be split up" << std::endl;
	combs1.clear();
	BruteForceMaxProfit(target, 0, combs1, price, mx);
	std::cout << "Max profit for rod cutting using brute force approach is is " << mx << std::endl;*/

	// Knapsack
	const std::vector<int> val{ 60, 100, 120 };
	const std::vector<int> wt{ 10, 20, 30 };
	int  W = 50;
	BruteForceZeroOneKnapSack obj2(val, wt, W);
	std::cout << "Max profit using brute force 0-1 knapsack is " << obj2.find() << std::endl;
	/*const std::vector<int> val{ 60, 100, 120 };
	const std::vector<int> wt{ 10, 20, 30 };
	int  W = 50;
	std::vector<int> combs2;
	count = 0;
	std::cout << "The subsets of the given value array are: " << std::endl;
	findSubsets(val, combs2, 0);
	std::cout << "There are totally " << ++count << " subsets of the given array of size " << val.size() << std::endl;
	combs2.clear();
	int maxPrf = 0;
	BruteForceKnapSack(val, wt, W, combs2, 0, 0, maxPrf);
	std::cout << "Max profit using brute force 0-1 knapsack is " << maxPrf << std::endl;*/
	return 0;
}