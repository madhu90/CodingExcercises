#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// http://www.cs.cmu.edu/afs/cs/academic/class/15210-s15/www/lectures/dp-notes.pdf
// http://www.cs.cmu.edu/afs/cs/academic/class/15210-f13/www/recitations/rec13.pdf

class Palindrome
{
	std::vector<std::vector<int>> mat;
	std::unordered_map<std::string, int> map;
	std::unordered_map<std::string, std::string> strmap;

public:
	int topDown(const std::string& str)
	{
		return topDownHelper(str, 0, str.length() - 1);
	}

	int BottomUp(const std::string& str)
	{
		return BottomUpHelper(str);
	}

	std::string getPalindrome(const std::string& str)
	{
		return getPalHelper(str, 0, str.length() - 1);
	}

private:

	std::string getPalHelper(const std::string& str, int i, int j)
	{
		if (i > j)
			return "";

		if (i == j)
			return std::string(1, str[i]);

		std::string key = std::to_string(i) + "_" + std::to_string(j);

		if (strmap.find(key) == strmap.end())
		{
			if (str[i] == str[j])
			{
				strmap[key] = std::string(1, str[i]) + getPalHelper(str, i + 1, j - 1) + std::string(1, str[j]);
			} else {
				std::string first = getPalHelper(str, i + 1, j);
				std::string second = getPalHelper(str, i, j - 1);
				strmap[key] = first.length() > second.length() ? first : second;
			}
		} 

		return strmap[key];
	}

	int BottomUpHelper(const std::string& str)
	{	
		mat = std::vector<std::vector<int>>(str.length(), std::vector<int>(str.length(), 0));

		// The DP solution for this -> DAG boils down to getting the LPS information
		// about single characters, then two of them and so on. Knowing the solution for 'x'
		// is required to compute 'x*' and this in turn is required to compute 'x**'. So, filling
		// out the table has to be for increasing lengths. The final solution will be at the top right:
		//
		// ----------
		//          |
		//          | 

		// All single characters are palindromes
		for (int i = 0; i < str.length(); ++i)
			mat[i][i] = 1;
		
		// Let's start with a length of 2
		for (int length = 2; length < str.length(); ++length)
		{
			for (int i = 0; i < str.length() - length + 1; ++i) {
				int j = i + length - 1;

				if (str[i] == str[j])
				{
					mat[i][j] = 2 + mat[i + 1][j - 1];
				} else {
					mat[i][j] = std::max(mat[i][j - 1], mat[i + 1][j]);
				}
			}
		}

		return mat[1][str.length() - 1];
	}

	int topDownHelper(const std::string& str, int i, int j)
	{
		// You don't want i to cross over j
		if (i > j)
			return 0;

		// Single characters are palindromes
		if (i == j)
			return 1;

		std::string key = std::to_string(i) + "_" + std::to_string(j);

		if (map.find(key) == map.end())
		{
			if (str[i] == str[j])
			{
				map[key] = topDownHelper(str, i + 1, j - 1) + 2;
			} else {
				map[key] = std::max(topDownHelper(str, i + 1, j), topDownHelper(str, i, j - 1));
			}
		} 
		
		return map[key];
	}
};

int main()
{
	std::string str("ABBDCACB");
	Palindrome obj;
	int len1 = obj.topDown(str);
	std::cout << "Length of longest palindromic subsequence using TOP-DOWN approach is " << len1 << std::endl;
	int len2 = obj.BottomUp(str);
	std::cout << "Length of longest palindromic subsequence using BOTTOM-DOWN approach is " << len2 << std::endl;
	std::string str1 = obj.getPalindrome(str);
	std::cout << "Longest palindromic subsequence is " << str1 << std::endl;
	return 0;
}