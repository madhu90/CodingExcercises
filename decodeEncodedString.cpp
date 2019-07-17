#include <iostream>
#include <string>

// Question reference: https://leetcode.com/problems/decode-string/ and 

class StringDecoder
{
public:
    std::string decode(const std::string& input)
    {       
        int indx = 0;
        std::string result = decodeHelper(input, indx);
        return result;
    }

private:
    std::string decodeHelper(const std::string& input, int& str_index)
    {
        if (str_index >= input.length())
            return "";

        if (isNumber(input[str_index]))
        {
            int numberToReplicate = getNumberFromString(input, str_index);
            std::string substr = decodeHelper(input, str_index);
			std::string replstr = replicateString(substr, numberToReplicate);
			++str_index;
            return replstr + decodeHelper(input, str_index);
        } else if (isOpenParen(input[str_index])) {
            str_index++;
            return decodeHelper(input, str_index);            
        } else if (isClosedParen(input[str_index])) {
            return "";
        } else {
            std::string currChar(1, input[str_index]);
            str_index++;
            return currChar + decodeHelper(input, str_index);
        }
    }

    int getNumberFromString(const std::string& input, int& str_index)
    {        
        std::string numChars;

        while (str_index < input.length() && isNumber(input[str_index]))
        {
            numChars.append(1, input[str_index]);
            str_index++;
        }

        return std::stoi(numChars);
    }

    std::string replicateString(const std::string& input, int repeat)
    {
        std::string result;
        
        for (size_t i = 1; i <= repeat; ++i)
        {
            result += input;
        }

        return result;
    }

    bool isNumber(char c)
    {
        int value = getNumFromChar(c);
        return value >= 0 && value <= 9;
    }

    bool isOpenParen(char c)
    {
        return c == '[';
    }

    bool isClosedParen(char c)
    {
        return c == ']';
    }

    int getNumFromChar(char c)
    {
        return c -'0';
    }
};

int main()
{
	StringDecoder obj;
	std::string pattern1("3[a]2[bc]");
	std::string decode1 = obj.decode(pattern1);
	std::cout << "Input: " << pattern1 << "    Output:  " << decode1 << std::endl;
	std::string pattern2("3[a2[c]]");
	std::string decode2 = obj.decode(pattern2);
	std::cout << "Input: " << pattern2 << "    Output:  " << decode2 << std::endl;
	std::string pattern3("2[abc]3[cd]ef");
	std::string decode3 = obj.decode(pattern3);
	std::cout << "Input: " << pattern3 << "    Output:  " << decode3 << std::endl;
	std::string pattern4("10[a]ed3[cd]f");
	std::string decode4 = obj.decode(pattern4);
	std::cout << "Input: " << pattern4 << "    Output:  " << decode4 << std::endl;
	std::string pattern5("3[a]2[b4[F]c]");
	std::string decode5 = obj.decode(pattern5);
	std::cout << "Input: " << pattern5 << "    Output:  " << decode5 << std::endl;
	return 0;
}