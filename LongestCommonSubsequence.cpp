#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Subsequence
{
private:
	std::vector<std::string> subseqs;
	const std::string& input;

public:
	Subsequence(const std::string& str)
		: input(str)
	{

	}

	void generate()
	{
		std::string subseq;
		generateHelper(input, 0, subseq);
	}

	void print()
	{
		std::cout << "Subsequences of " << input << " are:" << std::endl;
		for (const auto& iter : subseqs)
		{
			std::cout << iter << std::endl;
		}
	}

	const std::vector<std::string> get() const
	{
		return subseqs;
	}

private:
	void generateHelper(const std::string& input, int indx, std::string subseq)
	{
		subseqs.push_back(subseq);

		for (int i = indx; i < input.length(); ++i)
		{
			subseq.append(1, input[i]);
			generateHelper(input, i + 1, subseq);
			subseq.pop_back();
		}
	}
};

class BruteForceLongestCommonSubsequence
{
private:
	const std::string& str1;
	const std::string& str2;

public:
	BruteForceLongestCommonSubsequence(const std::string& input1, const std::string& input2)
		: str1(input1), str2(input2)
	{

	}

	void find()
	{
		Subsequence obj1(str1);
		Subsequence obj2(str2);
		obj1.generate();
		obj2.generate();
		std::vector<std::string> common_sub;
		int longest_length = 0;

		std::vector<std::string> subseqs1 = obj1.get();
		std::vector<std::string> subseqs2 = obj2.get();
		
		for (int i = 0; i < subseqs1.size(); ++i) {
			for (int j = 0; j < subseqs2.size(); ++j) {
				if (subseqs1[i].compare(subseqs2[j]) == 0) {
					common_sub.push_back(subseqs1[i]);
					longest_length = std::max(static_cast<size_t>(longest_length), subseqs1[i].length());
				}
			}
		}

		int sz = common_sub.size();
		int i = 0;
		while (i < sz)
		{
			if (common_sub[i].length() < longest_length)
			{
				common_sub.erase(common_sub.begin() + i);
				sz = common_sub.size();
			} else {
				i++;
			}
		}

		std::cout << "Brute force approach: Longest common subsequences of " << str1 << " and " << str2 << " are: " << std::endl;
		for (const auto& iter : common_sub)
		{
			std::cout << iter << std::endl;
		}
	}
};

class DynamicProgramming
{
private:
	const std::string& str1;
	const std::string& str2;
	std::unordered_map<std::string, int> map;
	std::vector<std::vector<int>> mat;

public:
	DynamicProgramming(const std::string& input1, const std::string& input2)
		: str1(input1), str2(input2)
	{

	}

	void topDown()
	{
		int len = topDownHelper(str1.length() - 1, str2.length() - 1);
		std::cout << "DP: TOP DOWN: Length of longest common subsequence of " << str1 << " and " << str2 << " is " << len << std::endl;		
	}

	void bottomUp()
	{
		int len = bottomUpHelper();
		std::cout << "DP: BOTTOM UP: Length of longest common subsequence of " << str1 << " and " << str2 << " is " << len << std::endl;
	}

	void allLCS()
	{
		std::vector<std::string> res = getLCSTopDown(mat.size() - 1, mat[0].size() - 1);
		std::cout << "All the LCS are" << std::endl;
		for (auto iter : res)
		{
			std::cout << iter << std::endl;
		}
	}

private:

	std::vector<std::string> getLCSTopDown(int indx1, int indx2)
	{
		if (indx1 <= 0 || indx2 <= 0)
		{
			std::vector<std::string> v;
			v.push_back("");
			return v;
		}			

		if (str1[indx1 - 1] == str2[indx2 - 1])
		{
			std::vector<std::string> result = getLCSTopDown(indx1 - 1, indx2 - 1);

			for (std::string & iter : result)
				iter.push_back(str1[indx1 - 1]);

			return result;
		} else if (mat[indx1 - 1][indx2] > mat[indx1][indx2 - 1]){
			// Move in the direction of greater length
			return getLCSTopDown(indx1 - 1, indx2);
		} else if (mat[indx1][indx2 - 1] > mat[indx1 - 1][indx2]) {
			// Move in the direction of greater length
			return getLCSTopDown(indx1, indx2 - 1);
		} else {
			// Both directions can result in max value. So, try both
			std::vector<std::string> left = getLCSTopDown(indx1 - 1, indx2);
			std::vector<std::string> top = getLCSTopDown(indx1, indx2 - 1);

			//Merge results
			top.insert(top.end(), left.begin(), left.end());
			return top;
		}
	}

	int topDownHelper(int indx1, int indx2)
	{
		if (indx1 < 0 || indx2 < 0)
			return 0;

		std::string key = std::to_string(indx1) + "_" + std::to_string(indx2);

		if (map.find(key) == map.end())
		{
			if (str1[indx1] == str2[indx2])
			{
				map[key] = 1 + topDownHelper(indx1 - 1, indx2 - 1);
			} else {
				map[key] = std::max(topDownHelper(indx1, indx2 - 1), topDownHelper(indx1 - 1, indx2));
			}
		} 

		return map[key];		
	}

	int bottomUpHelper()
	{
		mat = std::vector<std::vector<int>>(str1.length() + 1, std::vector<int>(str2.length() + 1, 0));

		for (int i = 1; i <= str1.length(); ++i)
		{
			for (int j = 1; j <= str2.length(); ++j)
			{
				if (str1[i - 1] == str2[j - 1])
				{
					mat[i][j] = mat[i - 1][j - 1] + 1;
				} else {
					mat[i][j] = std::max(mat[i][j - 1], mat[i - 1][j]);
				}
			}
		}

		return mat[str1.length()][str2.length()];
	}
};

int main()
{
	std::string str1("ABCBDAB");
	std::string str2("BDCABA");
	BruteForceLongestCommonSubsequence obj1(str1, str2);
	obj1.find();	
	DynamicProgramming obj2(str1, str2);
	obj2.topDown();
	obj2.bottomUp();
	obj2.allLCS();
	return 0;
}