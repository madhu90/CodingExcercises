//
//  main.cpp
//  CheckifArrayDividedIntoPairsDivisibleByK
// Given an integer array, determine if it can be divided into pairs such that the sum of elements in each
// pair is divisible by a given integer k.
// The key idea here is that we are interested in pairs. Given any number x, we only have two options:
// a) x %  k == 0 -> divisible by k
// b) x % k != 0 -> not divisible by k and has a remainder r
// If a), then we need to find another number such that y % k == 0 so that we can form a pair (x,y). So,
// we are really interested in finding the frequency of the remainder 0. If it is even, we can form pairs.
// If not, we can't form pairs
// If b), we have found a remainder r. A pair is possible only if we find another element y which produces
// a remainder s such that r + s == k. For e.g. say k = 5 and we are processing entries 7,8. 7%5==2. Here
// r = 2. To find another number, the remainders should add up to 5 and only then it will be divisible by 5
// So, s must be 3 and 8%5==3. Here again, since we are interested in pairs and the remainders can be
// repeated, we can only return something meaningful if the frquency of r = frequency of s
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

bool canPairsBeFormed(const std::vector<int>& arr, int k)
{
    if (arr.size() % 2 != 0) // odd number of elements
        return false;
    
    std::unordered_map<int, std::vector<int>> map;
    std::vector<std::pair<int, int>> pairs;
    
    // Store remainder frequency in map
    for (int i = 0; i < arr.size(); ++i) {
        int remainder = arr[i] % k;
        
        if (remainder < 0) // handling negative values : https://torstencurdt.com/tech/posts/modulo-of-negative-numbers/#:~:text=The%20modulo%20operator%20returns%20the%20remainder%20of%20a%20division.&text=Doing%20an%20integer%20division%20and,and%20by%20that%20the%20modulo.
            remainder += k;
        
        map[remainder].push_back(arr[i]);
    }
    
    auto iter = map.begin();
    
    while (!map.empty()) {
        int remainder = iter->first;
        std::vector<int> values = iter->second;
        
        
        
        if (remainder == 0) {
            if (values.size() % 2 != 0) {
                return false;
            } else {
                for (int j = 0; j+1 < values.size(); j+=2) {
                    pairs.emplace_back(values[j], values[j+1]);
                }
                map.erase(iter);
            }
        } else {
            int valueToBeDivisible = k - remainder;
            if (valueToBeDivisible != remainder) {
                auto completeValueiter = map.find(valueToBeDivisible);
                
                if (completeValueiter == map.end())
                    return false;
                
                std::vector<int> secondValues = completeValueiter->second;
                if (secondValues.size() != values.size())
                    return false;
                
                for (int j = 0; j < values.size(); ++j) {
                    pairs.emplace_back(values[j], secondValues[j]);
                }
                
                map.erase(iter);
                map.erase(completeValueiter);
            } else {
                for (int j = 0; j+1 < values.size(); j+=2) {
                    pairs.emplace_back(values[j], values[j+1]);
                }
                map.erase(iter);
            }
        }
        
        if (!map.empty())
            iter = map.begin();
    }
    
    std::cout << "The pairs are:" << std::endl;
    for(int i = 0; i < pairs.size(); ++i) {
        std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ")" << std::endl;
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    std::vector<int> arr1{3,1,2,6,9,4};
    std::vector<int> arr2{3,1,2,9,4};
    std::vector<int> arr3 {2,9,4,1,3,5};
    std::vector<int> arr4{3,1,2,6,9,4};
    std::vector<int> arr5{-1, 6, -2, 7};
    bool result1 = canPairsBeFormed(arr1, 5);
    bool result2 = canPairsBeFormed(arr2, 5);
    bool result3 = canPairsBeFormed(arr3, 6);
    bool result4 = canPairsBeFormed(arr4, 6);
    bool result5 = canPairsBeFormed(arr5, 5);
    std::cout << result1 << std::endl;
    std::cout << result2 << std::endl;
    std::cout << result3 << std::endl;
    std::cout << result4 << std::endl;
    std::cout << result5 << std::endl;
    return 0;
}
