#include <iostream>
#include <vector>
// https://leetcode.com/problems/single-number-ii/
// https://www.geeksforgeeks.org/find-the-element-that-appears-once/

int findSingleElement(const std::vector<int>& arr)
{	
	int ones = 0; // Bits that appear once
	int twos = 0; // Bits that appear twice
	int thrice; // Bits that appear thrice
	
	for (auto iter : arr)
	{
		twos |= ones & iter; // Only if ones and the current element have same bit pattern, twos will get updated
		ones ^= iter; // XOR will add this bit to ones if it's not there or remove this bit from ones if it's already there;
		thrice = ~(ones & twos); // We are extracting the bits that ones and twos have in common (same element appears in both groups)
		ones &= thrice; // If an element appears thrice, we remove it from ones
		twos &= thrice; // If an element appears thrice, we remove it from twos
	}

	return ones; // we are interested in the single element
}

int main()
{
	std::vector<int> arr1{ 2, 2, 3, 2 };
	std::vector<int> arr2{0, 1, 0, 1, 0, 1, 99};
	std::cout << "Single element is " << findSingleElement(arr1) << std::endl;
	std::cout << "Single element is " << findSingleElement(arr2) << std::endl;
	return 0;
}