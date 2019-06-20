// Implementation of Karatsuba multiplication
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <math.h>

// x = (10^n/2)*a + b
// y = (10^n/2)*c + d
// x*y = ((10^n/2)*a + b)*((10^n/2)*c + d)
//     = (10^n)*ac + (10^n/2)*(ad + bc) + bd

class Karatsuba
{
private:
    unsigned int f1;
    unsigned int f2;
    unsigned int numdigits;

public:
    Karatsuba(unsigned int val1, unsigned int val2)
        : f1(val1), f2(val2)
    {
        numdigits = std::to_string(std::max(f1, f2)).length();
    }

    unsigned int computeProduct(void)
    {
        return compute(f1, f2, numdigits);
    }

    void printLookupContents()
    {
        std::cout << "Lookup map contents" << std::endl;
        for (const auto& iter : lookup)
        {
            std::cout << iter.first << "   --->   " << iter.second << std::endl;
        }
    }

private:
    unsigned int compute(unsigned int val1, unsigned int val2, unsigned int numdigits)
    {
        if (numdigits == 1)
            return val1 * val2;

        unsigned int newdigits = numdigits / 2;
        unsigned int a = val1 / std::pow(10, newdigits);
        unsigned int b = val1 % static_cast<unsigned int>(std::pow(10, newdigits));
        unsigned int c = val2 / std::pow(10, newdigits);
        unsigned int d = val2 % static_cast<unsigned int>(std::pow(10, newdigits));

        // Check map if entry exists
        unsigned int ac = 0;
        unsigned int bd = 0;
        unsigned int ad_bc = 0;

        // ac
        std::string key1 = std::to_string(a) + std::string("*") + std::to_string(c);
        if (lookup.find(key1) == lookup.end()) {
            lookup[key1] = compute(a, c, newdigits);
            ac = lookup[key1];
        } else {
            ac = lookup[key1];
        }

        // bd
        std::string key2 = std::to_string(b) + std::string("*") + std::to_string(d);
        if (lookup.find(key2) == lookup.end()) {
            lookup[key2] = compute(b, d, newdigits);
            bd = lookup[key2];
        } else {
            bd = lookup[key2];
        }

        // ad + bc
        std::string key3 = std::to_string(a) + std::to_string(d) + std::string("*") + std::to_string(b) + std::to_string(c);
        if (lookup.find(key3) == lookup.end()) {
            lookup[key3] = compute((a + b), (c + d), newdigits) - ac - bd;
            ad_bc = lookup[key3];
        } else {
            ad_bc = lookup[key3];
        }

        return std::pow(10, numdigits)*ac + std::pow(10, newdigits)*ad_bc + bd;
    }

private:
    std::unordered_map<std::string, unsigned int> lookup;
};

int main()
{
    unsigned int value1 = 1234;
    unsigned int value2 = 5678;
    Karatsuba calc(value1, value2);    
    unsigned int result = calc.computeProduct();
    std::cout << "Result of " << value1 << "*" << value2 << "   " << result << std::endl;
    calc.printLookupContents();
    return 0;
}
