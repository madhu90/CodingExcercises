#include <iostream>
#include <string>

class PalindromeComputer
{
private:
	const std::string& str;

private:

	std::string expand(int low, int high)
	{
		while (low >= 0 && high < str.length() && str[low] == str[high])
		{
			--low;
			++high;
		}

		return str.substr(low + 1, high - low - 1);
	}

public:
	PalindromeComputer(const std::string& s)
		: str(s)
	{

	}

	std::string findLongest()
	{
		std::string max_len_str;
		int max_len = 0;

		for (int i = 0; i < str.length(); ++i)
		{
			// Odd length palindrome
			std::string odd_length_pal = expand(i, i);

			if (odd_length_pal.length() > max_len)
			{
				max_len = odd_length_pal.length();
				max_len_str = odd_length_pal;
			}

			// Even length palindrome
			std::string even_length_pal = expand(i, i + 1);

			if (even_length_pal.length() > max_len)
			{
				max_len = even_length_pal.length();
				max_len_str = even_length_pal;
			}
		}

		return max_len_str;
	}
};

int main()
{
	const std::string str("ABDCBCDBDCBBC");
	PalindromeComputer obj(str);
	const std::string result = obj.findLongest();
	std::cout << "Longest palindromic substring is " << result << std::endl;
	return 0;
}