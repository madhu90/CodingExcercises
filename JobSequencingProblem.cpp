#include <iostream>
#include <vector>
#include <algorithm>

// QUESTION: https://www.techiedelight.com/job-sequencing-problem-deadlines/

struct Job
{
	int id;
	int deadline;
	int profit;
};

class Scheduler
{
private:
	std::vector<Job> jobs;

public:
	Scheduler(std::vector<Job> j)
		: jobs(j)
	{
		// Sor in decreasing order of profit
		std::sort(jobs.begin(), jobs.end(), 
			[](const Job& a, const Job& b)
		{
			return a.profit > b.profit;
		});
	}

	void compute()
	{
		std::vector<int> slots(jobs.size(), -1);
		int maxProft = 0;

		for (const auto& iter : jobs)
		{
			int deadline = iter.deadline - 1;

			// Try to see if any slot before the deadline is available
			for (int j = deadline; j >= 0; --j)
			{
				if (slots[j] == -1)
				{
					slots[j] = iter.id;
					maxProft += iter.profit;
					break;
				}
			}
		}

		std::cout << "Jobs can be scheduled as shown below, to get a max profit of " << maxProft << std::endl;

		for (auto iter : slots)
		{
			std::cout << iter << "  ";
		}

		std::cout << std::endl;
	}
};

int main()
{
	std::vector<Job> jobs{
		{1, 9, 15},
		{2, 2, 2},
		{3, 5, 18}, 
		{4, 7, 1},
		{5, 4, 25},
		{6, 2, 20},
		{7, 5, 8},
		{8, 7, 10},
		{9, 4, 12},
		{10, 3, 5}
	};

	Scheduler obj(jobs);
	obj.compute();
}