#include <iostream>
#include <vector>

class Heap
{
protected:
	std::vector<int> data;

	int left(int indx)
	{
		return 2 * indx + 1;
	}

	int right(int indx)
	{
		return 2 * indx + 2;
	}

	int parent(int indx)
	{
		return std::floor((indx - 1)/2);
	}

	virtual void bubble_up(int data_indx) = 0;
	virtual void bubble_down(int data_indx) = 0;

public:

	void push(int dat)
	{
		data.push_back(dat);
		bubble_up(data.size() - 1);
	}

	void pop()
	{
		if (!data.empty())
		{
			std::swap(data[0], data[data.size() - 1]);
			data.pop_back();
			bubble_down(0);
		}		
	}

	int top()
	{
		if (!data.empty())
		{
			return data[0];
		} else {
			return std::numeric_limits<int>::min();
		}
	}
};

class MinHeap : public Heap 
{
public:
	virtual void bubble_up(int data_indx) override
	{
		int prnt = parent(data_indx);
		if (data[prnt] > data[data_indx])
		{
			std::swap(data[data_indx], data[prnt]);
			bubble_up(prnt);
		}
	}

	virtual void bubble_down(int data_indx) override
	{
		int left_idx = left(data_indx);
		int right_idx = right(data_indx);
		int min_element_idx = data_indx;

		if (left_idx < data.size() && data[left_idx] < data[min_element_idx])
			min_element_idx = left_idx;

		if (right_idx < data.size() && data[right_idx] < data[min_element_idx])
			min_element_idx = right_idx;

		if (data[min_element_idx] != data[data_indx])
		{
			std::swap(data[data_indx], data[min_element_idx]);
			bubble_down(min_element_idx);
		}
	}
};

class MaxHeap : public Heap
{
public:
	virtual void bubble_up(int data_indx) override
	{
		int prnt = parent(data_indx);
		if (data[data_indx] > data[prnt])
		{
			std::swap(data[data_indx], data[prnt]);
			bubble_up(prnt);
		}
	}

	virtual void bubble_down(int data_indx) override
	{
		int left_idx = left(data_indx);
		int right_idx = right(data_indx);
		int max_element_idx = data_indx;

		if (left_idx < data.size() && data[left_idx] > data[max_element_idx])
			max_element_idx = left_idx;

		if (right_idx < data.size() && data[right_idx] > data[max_element_idx])
			max_element_idx = right_idx;

		if (max_element_idx != data_indx)
		{
			std::swap(data[data_indx], data[max_element_idx]);
			bubble_down(max_element_idx);
		}
	}
};

int main()
{
	MinHeap pq;
	std::cout << "Min heap stuff" << std::endl;
	pq.push(3);
	pq.push(2);
	pq.push(15);
	std::cout << pq.top() << " ";
	pq.pop();
	std::cout << pq.top() << " ";
	pq.pop();
	pq.push(5);
	pq.push(4);
	pq.push(45);
	std::cout << pq.top() << " ";
	pq.pop();
	std::cout << pq.top() << " ";
	pq.pop();
	std::cout << pq.top() << " ";
	pq.pop();
	std::cout << pq.top() << " ";
	std::cout << std::endl;

	MaxHeap pq1;
	std::cout << "Max heap stuff" << std::endl;
	pq1.push(3);
	pq1.push(2);
	pq1.push(15);
	std::cout << pq1.top() << " ";
	pq1.pop();
	std::cout << pq1.top() << " ";
	pq1.pop();
	pq1.push(5);
	pq1.push(4);
	pq1.push(45);
	std::cout << pq1.top() << " ";
	pq1.pop();
	std::cout << pq1.top() << " ";
	pq1.pop();
	std::cout << pq1.top() << " ";
	pq1.pop();
	std::cout << pq1.top() << " ";
	pq1.pop();
	std::cout << std::endl;
	return 0;
}