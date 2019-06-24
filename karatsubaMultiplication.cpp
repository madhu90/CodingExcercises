// Implementation of Karatsuba multiplication
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <math.h>

// If x and y have same lengths
// x = (10^n/2)*a + b
// y = (10^n/2)*c + d
// x*y = ((10^n/2)*a + b)*((10^n/2)*c + d)
//     = (10^n)*ac + (10^n/2)*(ad + bc) + bd

class Karatsuba
{
private:
	unsigned int f1;
	unsigned int f2;
	std::string f1String;
	std::string f2String;

public:
	Karatsuba(unsigned int val1, unsigned int val2)
		: f1(val1), f2(val2)
	{
		f1String = std::to_string(f1);
		f2String = std::to_string(f2);
	}

	unsigned int computeProduct(void)
	{		
		return compute(f1String, f2String);
	}

private:

	unsigned int padZeros(std::string& str1, std::string& str2)
	{
		if (str1.length() > str2.length()) {
			str2.insert(0, std::string(str1.length() - str2.length(), '0'));
		} else if (str1.length() < str2.length()) {
			str1.insert(0, std::string(str2.length() - str1.length(), '0'));
		}
		
		return str1.length();
	}

	unsigned long long int compute(
		std::string num1,
		std::string num2)
	{
		unsigned int length = padZeros(num1, num2);
		unsigned long long int val1 = static_cast<unsigned long long int>(std::stoi(num1));
		unsigned long long int val2 = static_cast<unsigned long long int>(std::stoi(num2));

		if (length == 1)
			return val1 * val2;

		unsigned int left_idx = length / 2;
		unsigned int right_idx = length - left_idx;
		
		std::string a = num1.substr(0, left_idx);
		std::string b = num1.substr(left_idx, right_idx);
		std::string c = num2.substr(0, left_idx);
		std::string d = num2.substr(left_idx, right_idx);

		unsigned long long int ac = compute(a, c);
		unsigned long long int bd = compute(b, d); 
		unsigned long long int ad_bc = compute(std::to_string(std::stoi(a) + std::stoi(b)), std::to_string(std::stoi(c)+std::stoi(d))) - ac - bd;
		
		std::cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << std::endl;
		std::cout << "    ac = " << ac << ", bd = " << bd << ", ad + bc = " << ad_bc << std::endl;
		
		/* Why do we multiply by right_idx here and not length/2 ?
		 * Consider a situation where we have odd length numbers:
		 * x = 12345    ----> a = 12, b = 345
		 * y = 05678    ----> c = 05, d = 678
		 * Here, how are a,b and c,d combined to get x and y?
		 * x = 12*1000 + 345
		 * y = 5*1000 + 345
		 * The power of 10 is really the length of the right half
		 * because that is how much the left half must be shifted
		 * Also, in our split for odd length data, the left will always
		 * be shorter (floor(length/2)) and the right will be larger 
		 * ceil(length/2). So, we always pick the length of the right
		 * half and use that as 10's exponent
		 */
		return std::pow(10, 2*right_idx)*ac + std::pow(10, right_idx)*ad_bc + bd;
	}
};

int main()
{
	unsigned int value1 = 123;
	unsigned int value2 = 5678;
	Karatsuba calc(value1, value2);
	unsigned int result = calc.computeProduct();
	std::cout << "Result of " << value1 << "*" << value2 << "   " << result << std::endl;	
	return 0;
}
