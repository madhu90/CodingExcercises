#include <string>
#include <iostream>

class Anagrams
{
public:
	bool find(const std::string& x, const std::string& y)
	{
		if (x.length() != y.length())
			return false;

		int xor_results =  0;

		for (int i = 0; i < x.length(); ++i)
		{
			xor_results  = xor_results ^ x[i];
			xor_results = xor_results ^ y[i];
		}

		return xor_results == 0;
	}
};

int main()
{
	const std::string x("tommarvoloriddle");
	const std::string y("iamlordvoldemort");
	Anagrams obj;
	bool result = obj.find(x, y);
	
	if (result)
	{
		std::cout << x << " and " << y << " are anagrams" << std::endl;
	} else {
		std::cout << x << " and " << y << " are not anagrams" << std::endl;
	}

	return 0;
}