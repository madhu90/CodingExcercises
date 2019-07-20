#include <iostream>
#include <string>

class StringPermuter
{
private:
	std::string& str;

private:
	void permuteHelper(int indx)
	{
		if (indx == str.length())
		{
			std::cout << str << std::endl;
			return;
		}		

		for (int i = indx; i < str.length(); ++i) 
		{
			std::swap(str[indx], str[i]);
			// Note that, all subsequent calls to permute takes 'indx' and NOT 'i+1'
			// Not sure why. While permuting, you don't reduce the string length
			permuteHelper(indx + 1);
			std::swap(str[indx], str[i]);
		}
	}

public:
	StringPermuter(std::string & inp)
		: str(inp)
	{

	}

	void permute()
	{
		permuteHelper(0);
	}
};

int main()
{
	std::string str("ABC");
	StringPermuter obj(str);
	obj.permute();
	return 0;
}