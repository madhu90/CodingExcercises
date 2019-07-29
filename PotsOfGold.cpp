#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

// QUESTION: https://www.techiedelight.com/pots-gold-game-dynamic-programming/

/**
 * The way to tackle this problem -> There are 2 players and both are playing optimally. This means
 * given an opportunity, each player will try to maximize his coins. The goal if for player A to 
 * get maximum coins and these are the rules:
 *
 * Player A always starts the game
 * Each player can only take a coin from the ends
 * Player B must follow player A and he must try to maximize the coins as well
 * 
 * We need to find out how to make A maximize the coins. Let's look at a sample walk through:
 *
 *                            A           B
 * (4, 6, 2, 3)               4
 * (6, 2, 3)                              6
 * (2, 3)                     3
 * 2                                      2
 * 
 * Here, A gets a total of 7 coins and B gets 8 coins (We don't want this because B gets more coins)
 *
 * We have 2 base cases here:
 * a) There is only one coin  --> No choice, it gets picked
 * b) There are 2 coins  --> The maximum value gets picked
 *
 * At any given point, the option for either player is just to choose between 2 coins (at either ends).
 * However, what needs to be kept in mind is, the result of the decision. We are reducing the problem
 * space each time and hence, we should have some way of caching the results of smaller problems (decisions
 * between different combinations of 2 coins). Let's express this mathematically:
 *
 * If you consider coins[i...j] to represent the vector containing coins, at each turn player A has 2 options:
 * a) Choose coin at i
 *    -> This leaves player B with 2 options - Choose coin at i + 1 or choose coin at j
 *        -> If B chooses coin at i + 1, then A is left with maximizing what's left between i + 2 and j
 *        -> If B chooses coin at j, then A is left with maximizing what's left between i + 1 and j - 1
 * b) Choose coin at j
 *    -> This leaves player B with 2 options - Choose coin at i or choose coin at j - 1
 *        -> If B chooses coin at i, then A is left with maximizing what's left between i + 1 and j - 1
 *        -> If B chooses coin at j - 1, then A is left with maximizing what's left between i and j - 2
 * 
 * One key point to note here is, we are trying to find best move for A. We need to take B's moves into consideration
 * because he is also playing optimally. So, B's move will always be a minimizing move for A. 
 *
 * This is a problem that has an optimal substructure because, solving the problem with 1 and 2 coins can be used, 
 * to solve the problem for multiple coins. That is, an optimal solution with a smaller subset can be extended to find 
 * the global optimum. Consider the case where we start with a single coin and grow:
 *         (1) --> A picks 1
 *         (1,4)  --> A picks max(1,4)
 *         (1,4,9) - Here, A has 2 options because choosing max(1,9) need not be the best strategy. The question we need to
 *                   answer is, given A's choice, how will the game continue and what will A finally get. 
 *         (1,4,9) - If A picks 1, B will pick max(4,9) and A will pick 4 => Total of 5 coins
 *                 - If A picks 9, B will pick max(1,4) and A will pick 1 => Total of 10 coins
 *
 * This also has overlapping solutions. Consider the case where we have 4 coins:
 *        (1,4,9,8) --> A has 2 options to choose
 *                      A picks 1, this leaves B with trying to maximize what it can with (4,9,8) --> minimizing move for A
 *                      A picks 8, this leaves B with trying to maximize what it can with (1,4,9) --> minimizing move for A
 *
 * From the previous step, we know what A needs to do to maximize its coins with (1,4,9) => B will use this cached information!
 * 
 */

class ExponetialSearch
{
private:
	int maxhelper(const std::vector<int>& coins, int i, int j)
	{
		// Single coin
		if (i == j)
			return coins[j];

		// 2 coins
		if (j == i + 1)
			return std::max(coins[i], coins[j]);

		// A chooses i -> B has 2 options and A chooses the minimizing move
		// max(2 options) for B means, min(2 options) for A. The next move for A is only after B plays
		int chooseI = coins[i] + std::min(maxhelper(coins, i + 2, j) , maxhelper(coins, i+ 1, j - 1));

		// A chooses j -> B has 2 options
		int chooseJ = coins[j] + std::min(maxhelper(coins, i + 1, j - 1), maxhelper(coins, i, j - 2));

		return std::max(chooseI, chooseJ);
	}
public:
	int searchMaximum(const std::vector<int>& coins)
	{
		return maxhelper(coins, 0, coins.size() - 1);
	}
};

class DynamicProgramming
{
private:
	std::unordered_map<std::string, int> map;
	const std::vector<int>& coins;

private:
	int topDownHelper(int i, int j)
	{
		if (i == j)
			return coins[i];

		if (j == i + 1)
			return std::max(coins[i], coins[j]);

		std::string key = std::to_string(i) + "_" + std::to_string(j);

		if (map.find(key) == map.end())
		{
			int chooseI = coins[i] + std::min(topDownHelper(i + 2, j), topDownHelper(i + 1, j - 1));
			int chooseJ = coins[j] + std::min(topDownHelper(i + 1, j - 1), topDownHelper(i, j - 2));
			map[key] = std::max(chooseI, chooseJ);
		} else {
			int x = 5;
		}

		return map[key];
	}

public:
	DynamicProgramming(const std::vector<int>& c)
		: coins(c)
	{
	}

	int topDown()
	{
		return topDownHelper(0, coins.size() - 1);
	}

	int bottomUp()
	{
		// Pair represents value for max move (first) and min move (second)
		std::vector<std::vector<std::pair<int, int>>> lookup(coins.size(), std::vector<std::pair<int, int>>(coins.size(), std::make_pair(0, 0)));
		
		// Base condition: only 1 coin
		for (int i = 0; i < coins.size(); ++i) {
			lookup[i][i] = std::make_pair(coins[i], 0);
		}

		// Base condition: two coins
		for (int i = 0; i < coins.size() - 1; ++i) {
			int j = i + 1;
			lookup[i][j] = std::make_pair(std::max(coins[i], coins[j]), std::min(coins[i], coins[j]));
		}

		// Start with 3 coins at a time
		for (int length = 3; length <= coins.size(); ++length)
		{
			for (int i = 0; i <= coins.size() - length; ++i)
			{
				int j = i + length - 1;
				
				// A picks coins[i], then it gets the min of the remaining (second)
				// Then, it gets the max of picking i or j
				if (coins[i] + lookup[i + 1][j].second > coins[j] + lookup[i][j - 1].second)
				{
					lookup[i][j].first = coins[i] + lookup[i + 1][j].second;
					lookup[i][j].second = lookup[i + 1][j].first; // If A gets the min of this move, then B should get the max because it does not get coin[i]
				} else {
					// A picks coins[j] and it gets min of the remaining (second)
					lookup[i][j].first = coins[j] + lookup[i][j - 1].second;
					lookup[i][j].second = lookup[i][j - 1].first;
				}				
			}
		}

		return lookup[0][coins.size() - 1].first;
	}
};

int main()
{
	std::vector<int> coins1{ 4,6,2,3 };
	std::vector<int> coins2{ 6, 1, 4, 9, 8, 5 };
	ExponetialSearch obj1;
	int AMax1 = obj1.searchMaximum(coins1);
	std::cout << "Maximum coins1 collected by A (EXPONENTIAL) is " << AMax1 << std::endl;	
	DynamicProgramming obj2(coins2);
	int AMax2 = obj2.topDown();
	std::cout << "Maximum coins2 collected by A (DP - Top down) is " << AMax2 << std::endl;
	int AMax3 = obj2.bottomUp();
	std::cout << "Maximum coins2 collected by A (DP - Bottom up) is " << AMax3 << std::endl;
	return 0;
}