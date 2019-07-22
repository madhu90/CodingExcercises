#include <iostream>
#include <string>
#include <vector>

class Substring
{
private:
	const std::string& str;
	std::vector<std::string> substrs;

public:
	Substring(const std::string& input)
		: str(input)
	{
	}

	std::vector<std::string> get() const
	{
		return substrs;
	}

	void generate()
	{
		std::string sub;
		generateHelper(0);
	}

	void print()
	{
		std::cout << "Substrings of string " << str << " are:" << std::endl;
		for (auto iter : substrs)
		{
			std::cout << iter << std::endl;
		}
	}

private:
	void generateHelper(int indx)
	{
		std::string sub;

		for (int i = indx; i < str.length(); ++i)
		{
			sub.append(1, str[i]);
			if (sub.length() == 1)
				// We do the recursion only when the first character is included
				// This is done to prevent duplicates
				generateHelper(i + 1);
			substrs.push_back(sub);
		}
	}
};

class BruteForceLongestCommonSubstring
{
private:
	const std::string& str1;
	const std::string& str2;
	std::vector<std::vector<int>> mat;

public:
	BruteForceLongestCommonSubstring(const std::string& input1, const std::string& input2)
		: str1(input1), str2(input2)
	{
	}

	void compute()
	{
		Substring obj1(str1);
		obj1.generate();
		std::vector<std::string> substrs = obj1.get();
		int max_length = 0;
		std::string longest;

		for (auto iter : substrs)
		{
			std::size_t found = str2.find(iter);
			if (found != std::string::npos && iter.length() > max_length)
			{
				max_length = iter.length();
				longest = iter;
			}
		}

		std::cout << "Longest common substring of strings " << str1 << " and " << str2 << " is " << longest << std::endl;
	}
};

class DPLongestCommonSubstring
{
private:
	const std::string& str1;
	const std::string& str2;
	std::vector<std::vector<int>> map;

public:
	DPLongestCommonSubstring(const std::string& input1, const std::string& input2)
		: str1(input1), str2(input2)
	{
	}

	void generate()
	{
		int rows = str1.length() + 1;
		int cols = str2.length() + 1;
		map = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
		int end_index = 0;
		int end_length = 0;

		for (int i = 1; i < rows; ++i)
		{
			for (int j = 1; j < cols; ++j) {
				if (str1[i - 1] == str2[j - 1])
				{
					map[i][j] = map[i - 1][j - 1] + 1;
					end_index = j;
					end_length = map[i][j];
				} else {
					map[i][j] = 0;
				}
			}
		}

		std::cout << "DP: Longest common substring of " << str1 << " and " << str2 << " is " << str2.substr(end_index - end_length, end_length) << std::endl;
	}
};

int main()
{
	std::string str1("ABC");
	std::string str2("BABA");
	BruteForceLongestCommonSubstring obj1(str1, str2);
	obj1.compute();
	DPLongestCommonSubstring obj2(str1, str2);
	obj2.generate();
	return 0;
}