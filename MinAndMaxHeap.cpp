//
//  Implementation of min and max heap in C++
//  In heaps, there are a couple of things to remember:
//  a) While adding a new value, you always start at the lowest level and left-most side
//     and you keep swapping up till heap-order property is maintained
//  b) While removing an element, it is always at the top/root. You keep swapping down
//     till heap-order property is maintained
//
//  Created by Madhumitha Raghu on 1/18/21.
//

#include <iostream>
#include <vector>

template<typename T>
class Heap {
private:
    std::vector<int> data;
    T comparator;
    
public:
    Heap()
    : comparator(T()) {
        
    }
    
    void push(int value)
    {
        if (data.empty())
        {
            data.push_back(value);
        } else {
            data.push_back(value);
            heapify_up(data.size() - 1);
        }
    }
    
    void pop()
    {
        if (data.empty())
            throw;
        data[0] = data.back();
        data.pop_back();
        heapify_down(0);
    }
    
    int top()
    {
        if (data.empty())
            throw;
        return data[0];
    }
    
    size_t size()
    {
        return data.size();
    }
    
    void print()
    {
        std::cout << "Printing queue  :  ";
        for (auto iter : data)
        {
            std::cout << iter << "  ";
        }
        std::cout << std::endl;
    }
    
private:
    size_t parent(size_t child_indx)
    {
        return (child_indx - 1) / 2;
    }
    
    size_t left(size_t indx)
    {
        return 2*indx + 1;
    }
    
    size_t right(size_t indx)
    {
        return 2*indx + 2;
    }
    
    void heapify_up(size_t indx)
    {
        // The parent must either be smaller than
        // or larger then the children
        if (indx != 0) { // if we have reached the root, then the heap order is maintained
            size_t parent_indx = parent(indx);
            bool result = comparator(data[indx], data[parent_indx]);
            if (result)
            {
                std::swap(data[indx], data[parent_indx]);
                heapify_up(parent_indx);
            }
        }
    }
    
    void heapify_down(size_t indx)
    {
        size_t maxIndx = indx;
        size_t leftindx = left(indx);
        size_t rightindx = right(indx);
        
        if (leftindx >= 0 && comparator(data[leftindx], data[maxIndx]))
            maxIndx = leftindx;
        
        if (rightindx < data.size() && comparator(data[rightindx], data[maxIndx]))
            maxIndx = rightindx;
        
        if (maxIndx != indx)
        {
            // continue process because we made changes
            // to keep the headp-order
            std::swap(data[indx], data[maxIndx]);
            heapify_down(maxIndx);
        }
    }
};



int main(int argc, const char * argv[]) {
    /* Max heap testing */
    std::cout << "Testing max heap" << std::endl;
    Heap<std::greater<int>> MaxHeap;
    MaxHeap.push(3);
    MaxHeap.push(2);
    MaxHeap.push(15);
    std::cout << "Size is " << MaxHeap.size() << std::endl;
    std::cout << MaxHeap.top() << " ";
    MaxHeap.pop();
    std::cout << MaxHeap.top() << " ";
    MaxHeap.pop();
    MaxHeap.push(5);
    MaxHeap.push(4);
    MaxHeap.push(45);
    std::cout << std::endl << "Size is " << MaxHeap.size() << std::endl;
    std::cout << MaxHeap.top() << " ";
    MaxHeap.pop();
    std::cout << MaxHeap.top() << " ";
    MaxHeap.pop();
    std::cout << MaxHeap.top() << " ";
    MaxHeap.pop();
    std::cout << MaxHeap.top() << " ";
    MaxHeap.pop();
    std::cout << std::endl;
    
    /* Min heap testing */
    std::cout << "Testing min heap" << std::endl;
    Heap<std::less<int>> MinHeap;
    MinHeap.push(3);
    MinHeap.push(2);
    MinHeap.push(15);
    std::cout << "Size is " << MinHeap.size() << std::endl;
    std::cout << MinHeap.top() << " ";
    MinHeap.pop();
    std::cout << MinHeap.top() << " ";
    MinHeap.pop();
    MinHeap.push(5);
    MinHeap.push(4);
    MinHeap.push(45);
    std::cout << std::endl << "Size is " << MinHeap.size() << std::endl;
    std::cout << MinHeap.top() << " ";
    MinHeap.pop();
    std::cout << MinHeap.top() << " ";
    MinHeap.pop();
    std::cout << MinHeap.top() << " ";
    MinHeap.pop();
    std::cout << MinHeap.top() << " ";
    MinHeap.pop();
    return 0;
}

