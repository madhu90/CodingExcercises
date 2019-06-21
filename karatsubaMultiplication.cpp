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

// If x and y have different lengths
// x = (10^n/2)*a + b
// y = (10^m/2)*c + d
// x*y = ((10^n/2)*a + b)*((10^m/2)*c + d)
//     = (10^(n+m)/2)*ac + (10^n/2)*ad +  (10^m/2)*bc + bd

class Karatsuba
{
private:
    unsigned int f1;
    unsigned int f2;
    unsigned int numdigits1;
    unsigned int numdigits2;

public:
    Karatsuba(unsigned int val1, unsigned int val2)
        : f1(val1), f2(val2)
    {
        numdigits1 = std::to_string(f1).length();
        numdigits2 = std::to_string(f2).length();
    }

    unsigned int computeProduct(void)
    {
        return compute(f1, f2, numdigits1, numdigits2);
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
    unsigned int compute(unsigned int val1, 
        unsigned int val2, 
        unsigned int m, 
        unsigned int n)
    {        
        unsigned int a = 0;
        unsigned int b = 0;
        unsigned int c = 0;
        unsigned int d = 0;
        unsigned int ac = 0;
        unsigned int bd = 0;
        unsigned int ad = 0;
        unsigned int bc = 0;        
        unsigned int new_m = m;
        unsigned int new_n = n;

        if (new_m == 1 && new_n == 1) {
            return val1 * val2;
        } else if (new_m == 1) {
            // Split y   
            a = val1;
            b = 1;
            splitData(c, d, val2, new_n);            
        } else if (new_n == 1) {
            // Split x  
            c = val2;
            d = 1;
            splitData(a, b, val1, new_m);            
        } else {
            // Split x and y  
            splitData(a, b, val1, new_m);
            splitData(c, d, val2, new_n);
        }
         
        // ac
        ac = compute(a, c, new_m, new_n);

        // bd
        bd = compute(b, d, new_m, new_n);

        // ad + bc
        ad = compute(a, d, new_m, new_n);
        bc = compute(b, c, new_m, new_n);        

        return std::pow(10, (m + n)/2)*ac + std::pow(10, n/ 2)*ad + std::pow(10, m / 2)*bc + bd;        
    }

    void splitData(unsigned int& c, unsigned int &d, unsigned int val, unsigned int& n)
    {
        n = n / 2;
        c = val / std::pow(10, n);
        d = val % static_cast<unsigned int>(std::pow(10, n));
    }
};

int main()
{
    unsigned int value1 = 12345;
    unsigned int value2 = 56783;
    Karatsuba calc(value1, value2);    
    unsigned int result = calc.computeProduct();
    std::cout << "Result of " << value1 << "*" << value2 << "   " << result << std::endl;
    calc.printLookupContents();
    return 0;
}
