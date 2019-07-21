#include <iostream>
#include <string>

// QUESTION: https://www.techiedelight.com/find-binary-strings-can-formed-given-wildcard-pattern/

class WilcardInterpreter
{
private:
	const std::string& str;

private:
	void generateHelper(int indx, std::string genstr)
	{
		if (indx >= str.length())
		{
			std::cout << genstr << std::endl;
			return;
		}

		if (str[indx] == '?')
		{
			genstr.append(1, '0');
			generateHelper(indx + 1, genstr);
			genstr.pop_back();
			genstr.append(1, '1');
			generateHelper(indx + 1, genstr);
		} else {
			genstr.append(1, str[indx]);
			generateHelper(indx + 1, genstr);
		}
	}

public:
	WilcardInterpreter(const std::string& input)
		: str(input)
	{

	}

	void generate()
	{
		std::string pattern;
		generateHelper(0, pattern);
	}
};

int main()
{
	std::string str("1?11?00?1?");
	WilcardInterpreter obj(str);
	obj.generate();
	return 0;
}