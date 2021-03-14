//
// Given k sorted linked lists, merge them into a single list
// Input: k = 3
// List 1: 1 -> 5 -> 7 -> NULL
// List 2: 2 -> 3 -> 6 -> 9 -> NULL
// List 3: 4 -> 8 -> 10 -> NULL
// Output: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> NULL
// Simple idea is to create a list of size len(List1) + len(List2) + len(List3) and sort it
// using a good algorithm like merge sort. This has a time complexity of O(NlogN).
// We can make use of the fact that we have k sorted lists by creating a min heap of size 'k'
// will the smallest element from each list. We keep popping the root (min element) and inserting
// elements from the list. This has a complexity of O(Nlog(k))
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
