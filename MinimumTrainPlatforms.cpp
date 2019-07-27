#include <iostream>
#include <vector>
#include <algorithm>

// QUESTION: https://www.techiedelight.com/minimum-number-of-platforms-needed-avoid-delay-arrival-train/

/**
 * This is asking you to find the maximum number of trains that can be in the station
 * at the same time. So, this will correspond to the minimum number of platforms, to avoid
 * waiting
 * Sort both arrival(arr) and departure(dep) arrays.
 * Compare current element in arrival and departure array and pick smaller one among both.
 * If element is pick up from arrival array then increment platform_needed.
 * If element is pick up from departure array then decrement platform_needed.
 * While performing above steps, we need track count of maximum value reached for platform_needed.
 * In the end, we will return maximum value reached for platform_needed.
 * Time complexity : O(NLogN)
 * Diagram in google drive will explain this
 */

class PlatformFinder
{
public:
	int getMinimum(
		std::vector<double> arrival,
		std::vector<double> departure)
	{
		int min = 1;
		int train_count = 0;

		// Sort the times
		std::sort(arrival.begin(), arrival.end());
		std::sort(departure.begin(), departure.end());
		size_t arrival_indx = 0;
		size_t depart_indx = 0;

		while (arrival_indx < arrival.size() && depart_indx < departure.size())
		{
			if (arrival[arrival_indx] < departure[depart_indx])
			{
				train_count++;
				min = std::max(min, train_count);
				if (arrival_indx < arrival.size())
					arrival_indx++;
			} else {
				train_count--;
				if (depart_indx < departure.size())
					depart_indx++;
			}

			if ((arrival_indx == (arrival.size() - 1)) && (depart_indx == (departure.size() - 1)))
				break; // Break out of loop
		}

		return min;
	}
};

int main()
{
	std::vector<double> arrival1{2.00, 2.10, 3.00, 3.20, 3.50, 5.00};
	std::vector<double> departure1{2.30, 3.40, 3.20, 4.30, 4.00, 5.20};
	PlatformFinder obj;
	int result1 = obj.getMinimum(arrival1, departure1);
	std::cout << "Minimum number of platforms needed is " << result1 << std::endl;

	std::vector<double> arrival2{ 1.00, 1.40, 1.50, 2.00, 2.15, 4.00 };
	std::vector<double> departure2{ 1.10, 3.00, 2.20, 2.30, 3.15, 6.00 };
	int result2 = obj.getMinimum(arrival2, departure2);
	std::cout << "Minimum number of platforms needed is " << result2 << std::endl;

	std::vector<double> arrival3{ 9.00, 9.40, 9.50, 11.00, 15.00, 18.00 };
	std::vector<double> departure3{ 9.10, 12.00, 11.20, 11.30, 19.00, 20.00 };
	int result3 = obj.getMinimum(arrival3, departure3);
	std::cout << "Minimum number of platforms needed is " << result3 << std::endl;
	return 0;
}