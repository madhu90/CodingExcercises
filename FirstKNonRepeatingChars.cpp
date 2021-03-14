//
// Find first k non-repeating characters in a string in single traversal
// For example, if the string is ABCDBAGHCHFAC and K = 3, output would be D G F
// The idea is to traverse the string once and store two pieces of information in
// a map:
// a) Character count
// b) Index of first/last occurence of character
// We then traverse the map and look for characters with count = 1. Since we are
// interested in the first k characters (lower index values), we create a min heap
// and store the indices of the characters with count = 1. Size of the heap is "k"
// because we are only interested in those many characters. After the heap is populated,
// we compare the index of a newly found character with the top of the heap. if teh index is
// small (character appears ealier), we pop and push the new character
//

#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

struct ChardData {
    int count;
    int indx;
};

void printFirstKNonRepeatingChars(const std::string& str, int k)
{
    std::unordered_map<char, ChardData> map;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    
    for (int i = 0; i < str.length(); ++i)
    {
        map[str[i]].count++;
        map[str[i]].indx = i;
    }
    
    for (const auto& iter : map)
    {
        int charCount = iter.second.count;
        int startOrEndIndex = iter.second.indx;
        
        if (charCount == 1) {
            if (pq.size() < k)
            {
                pq.push(startOrEndIndex);
            } else {
                if (startOrEndIndex < pq.top())
                {
                    pq.pop();
                    pq.push(startOrEndIndex);
                }
            }
        }
    }
    
    std::cout << "The first " << k << " non repeating characters are :";
    while (!pq.empty())
    {
        std::cout << "  " << str[pq.top()];
        pq.pop();
    }
    
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    std::string str = "ABCDBAGHCHFAC";
    int k = 3;
    printFirstKNonRepeatingChars(str, k);
    return 0;
}
