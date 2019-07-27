#include <iostream>
#include <vector>
#include <algorithm>

// QUESTION: https://www.techiedelight.com/find-maximum-product-subarray-given-array/

/**
 * At every element, we have 3 options:
 * a) Multiplying the element with the previous maximum will increase the product. This is
 *    true if the element is positive
 * b) Multiplying the element with the previous minimum will increase the product. This is
 *    true if the element is negative
 * c) The current element corresponds to the new start index for maximum (similar to Kadane's
 *    algorithm)
 *
 * Ref: https://www.quora.com/How-do-I-solve-maximum-product-subarray-problems
 *
 * In these scenarios, we don't have to worry about previous maximum being negative or previous
 * minimum being positive because, if multiplying previous max with the current positive element
 * makes the result negative, we will discard the product and take the current element as the new
 * product. We only pick the min or max at each step
 */

class MaxProductSubarray
{
public:
	int compute(const std::vector<int>& arr)
	{
		int prev_max_pdt = arr[0];
		int prev_min_pdt = arr[0];
		int curr_max_pdt = arr[0];
		int curr_min_pdt = arr[0];
		int ans = arr[0];

		for (size_t i = 1; i < arr.size(); ++i) {
			// curr_max = std::max(prev_max*arr[i], prev_min*arr[i], arr[i]);
			curr_max_pdt = std::max(prev_max_pdt*arr[i], prev_min_pdt*arr[i]);
			curr_max_pdt = std::max(curr_max_pdt, arr[i]);

			// curr_min = std::min(prev_max*arr[i], prev_min*arr[i], arr[i]);
			curr_min_pdt = std::min(prev_max_pdt*arr[i], prev_min_pdt*arr[i]);
			curr_min_pdt = std::min(curr_min_pdt, arr[i]);

			// Update result based on current_max
			ans = std::max(ans, curr_max_pdt);

			// DP: Cache previous computation
			prev_max_pdt = curr_max_pdt;
			prev_min_pdt = curr_min_pdt;
		}

		return ans;
	}
};

int main()
{
	std::vector<int> arr{-6, 4, -5, 8, -10, 0, 8};
	MaxProductSubarray obj;
	int pdt = obj.compute(arr);
	std::cout << "Maximum product is " << pdt << std::endl;
	return 0;
}