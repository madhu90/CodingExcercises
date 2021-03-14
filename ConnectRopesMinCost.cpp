//
// Connect N ropes with minimum cost
// Input: [5, 4, 2, 8]
// Output: The minimum cost is 36
//
// [5, 4, 2, 8] –> First, connect ropes of lengths 4 and 2 that will cost 6.
// [5, 6, 8]    –> Next, connect ropes of lengths 5 and 6 that will cost 11.
// [11, 8]      –> Finally, connect the remaining two ropes that will cost 19.
//
// Therefore, the total cost for connecting all ropes is 6 + 11 + 19 = 36.
// Here, the order in which we pick the numbers matters initially. So, we need
// to pick numbers in the ascending order and we will use a heap for it
//

#include <queue>
#include <iostream>
#include <vector>

int findMinCost(const std::vector<int>& vec)
{
    int cost = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    
    for (const auto& iter : vec)
        pq.push(iter);
    
    while (pq.size() > 1)
    {
        int first = pq.top();
        pq.pop();
        
        int second = pq.top();
        pq.pop();
        
        cost += (first + second);
        pq.push(first + second);
    }
    
    return cost;
}

int main(int argc, const char * argv[]) {
    std::vector<int> prices { 5, 4, 2, 8 };
    std::cout << "The minimum cost is " << findMinCost(prices) << std::endl;
    return 0;
}
