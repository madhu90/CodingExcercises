#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <queue>

// Dutch national flag problem
class DutchSorter
{
private:
	std::vector<int>& arr;

public:
	DutchSorter(std::vector<int>& a)
		: arr(a)
	{

	}

	void sort()
	{
		int ptr0 = 0; // points to end of zeros
		int ptr1 = 0; // points to end of ones
		int high = arr.size() - 1; // end of array

		// The pointers will eventually look like this
		// 0....0 1.......1 2....2
		//      |         |      
		//     ptr0     ptr1    

		// Our goal is to make sure the position of ptr1 is correct
		while (ptr1 <= high)
		{
			if (arr[ptr1] == 0)
			{
				// If 0 is at the position of 1, swap it with 1
				// We know ptr1 will always point to 1
				std::swap(arr[ptr1], arr[ptr0]);
				++ptr0;
				++ptr1; // ptr1 is always after ptr0
			} else if (arr[ptr1] == 1) {				
				++ptr1;
			} else {
				// If 2 is at the position of 1, swap it
				// However, we don't know what value we picked up from the
				// end -> it could be 0 or 1. So, we just reduce high
				std::swap(arr[ptr1], arr[high]);
				high--;
			}
		}

		int x = 5;
	}

	void print()
	{
		for (int iter : arr)
		{
			std::cout << iter << "  ";
		}

		std::cout << std::endl;
	}
};

// String interleaving problem
class StringInterleaver
{
private:
	const std::string& first_str;
	const std::string& second_str;
	int combinedLength;

public:
	StringInterleaver(const std::string& f, const std::string& s)
		: first_str(f), second_str(s)
	{
		combinedLength = first_str.length() + second_str.length();
	}

	void combine()
	{		
		std::string output;
		std::unordered_set<std::string> result;
		combineHelper(output, first_str, second_str, result);

		for (const std::string& iter : result)
		{
			std::cout << iter << std::endl;
		}
	}

private:

	void combineHelper(std::string result, const std::string first, const std::string second, std::unordered_set<std::string>& list)
	{
		//std::cout << "first: " << first << "    second:  " << second << std::endl;

		if (first.empty() && second.empty())
		{
			list.insert(result);
			return;
		}

		if (!first.empty())
			combineHelper(result + first[0], first.substr(1), second, list);

		if (!second.empty())
			combineHelper(result + second[0], first, second.substr(1), list);
	}
};

// Print all substrings of a string
class Substring
{
public:
	void compute(const std::string& str)
	{
		for (int i = 0; i < str.length(); ++i)
		{
			computeHelper(str.substr(i));
		}
	}

private:
	void computeHelper(std::string str)
	{
		if (str.empty())
			return;

		for (int i = 1; i <= str.length(); ++i)
		{
			std::cout << str.substr(0, i) << std::endl;			
		}
	}
};

// Combination of words from digits : https://www.techiedelight.com/possible-combinations-replacing-given-digits-corresponding-list/
class Combinations
{
private:
	const std::vector<std::vector<char>>& chars;
	const std::vector<int>& keys;
	std::unordered_map<int, char> map;

public:
	Combinations(const std::vector<std::vector<char>>& c, const std::vector<int>& k)
		: chars(c), keys(k)
	{
	}

	void compute()
	{
		std::string result;
		helper(0, result);		
	}

private:
	void helper(int start, std::string result)
	{
		if (start == keys.size())
		{
			std::cout << result << std::endl;
			return;
		}

		std::vector<char> current = chars[keys[start]];

		if (map.find(keys[start]) == map.end())
		{
			for (int i = 0; i < current.size(); ++i)
			{
				char curr = current[i];
				map[keys[start]] = curr;
				helper(start + 1, result + curr);
				// Backtrack
				map.erase(keys[start]);				
			}				
		} else {
			helper(start + 1, result + map[keys[start]]);
		}		
	}
};

// String reversal
class ReverseString
{
private:
	std::string& str;

public:
	ReverseString(std::string& s)
		: str(s)
	{

	}

	void performWithStack()
	{
		std::stack<std::string> stack;
		int low = 0;
		int high = 0;

		for (int i = 0; i < str.length(); ++i)
		{
			if (str[i] == ' ')
			{
				// Word separator
				if (low == 0)
				{
					// Add space before first word
					stack.push(" " + str.substr(low, high - low + 1));
				} else {
					stack.push(str.substr(low, high - low + 1));
				}
				
				low = i;
				high = i;
			} else {
				high = i;
			}
		}

		// Last word (remove the first space and then append)
		stack.push(str.substr(low + 1, high - low));

		int len = str.length();
		std::string str1;
		str1.reserve(len);

		while (!stack.empty())
		{
			str1.append(stack.top());
			stack.pop();
		}

		std::cout << "Reversed string is: " << std::endl;
		std::cout << str1 << std::endl;
	}

	void performWithoutStack()
	{
		int low = 0;
		int high = 0;

		for (int i = 0; i < str.length(); ++i)
		{
			// Reverse each word
			if (str[i] == ' ')
			{
				std::reverse(str.begin() + low, str.begin() + high + 1);
				low = i + 1;
				high = i + 1;				
			} else {
				high = i;
			}
		}

		// Reverse last word
		std::reverse(str.begin() + low, str.begin() + high + 1);

		// Reverse whole string
		std::reverse(str.begin(), str.end());

		std::cout << "Reversed string is: " << std::endl;
		std::cout << str << std::endl;
	}
};

// Combinatios of numbers of certain length
class NumericCombinations
{
private:
	const std::vector<int>& arr;
	int r;

public:
	NumericCombinations(const std::vector<int>& a, int length)
		: arr(a), r(length)
	{

	}

	void find()
	{
		std::vector<int> combinations;
		helper(combinations, 0);
	}

private:
	void helper(std::vector<int> combinations, int start)
	{
		if (combinations.size() == r)
		{
			for (int j : combinations)
			{
				std::cout << j << "  ";
			}

			std::cout << std::endl;
			return;
		}

		for (int i = start; i < arr.size(); ++i)
		{
			combinations.push_back(arr[i]);
			helper(combinations, i + 1);
			if (!combinations.empty())
				combinations.pop_back();
		}
	}
};

// Maximize value of expression: 
// A[s] - A[r] + A[q] - A[p]
// s > r > q > p
class ValueMaximizer
{
private:
	const std::vector<int>& arr;

public:

	ValueMaximizer(const std::vector<int>& a)
		: arr(a)
	{

	}

	int compute()
	{
		// Compute maximum value for A[s]
		std::vector<int> A_S(arr.size(), 0);
		A_S[0] = arr[0];

		for (int i = 1; i < A_S.size(); ++i)
			A_S[i] = std::max(arr[i], A_S[i - 1]);

		int max_A_S = A_S[A_S.size() - 1];

		// Compute maximum value for maxAs - A[r] = maxAsMinusAr
		// We shrink the size by 1 because, (A[s]) - A[r] can only be done 
		// for all values less than s. 
		std::vector<int> A_R(arr.size() - 1, 0);
		A_R[0] = arr[0] - max_A_S;

		for (int i = 1; i < A_R.size(); ++i)
			A_R[i] = std::max(A_R[i - 1], max_A_S - arr[i]);

		int max_A_R = A_R[A_R.size() - 1];

		// Compute maximum value for maxAsMinusAr + A[q] = maxAsMinusArPlusAq
		// We shrink the size by 1 because, (A[s] - A[r]) + A[q] can only be done 
		// for all values less than r
		std::vector<int> A_Q(arr.size() - 2, 0);
		A_Q[0] = max_A_R + arr[0];

		for (int i = 1; i < A_Q.size(); ++i)
			A_Q[i] = std::max(A_Q[i - 1], max_A_R + arr[i]);

		int max_A_Q = A_Q[A_Q.size() - 1];

		// Compute maximum value for maxAsMinusArPlusAq - A[p] = maxAsMinusArPlusAqMinusAp
		std::vector<int> A_P(arr.size() - 3, 0);
		A_P[0] = max_A_Q - arr[0];

		for (int i = 1; i < A_P.size(); ++i)
			A_P[i] = std::max(A_P[i - 1], max_A_Q - arr[i]);

		return A_P[A_P.size() - 1];
	}
};

// String decoding
class StringDecoder
{
private:
	const std::string& pattern;
	std::string result;

public:
	StringDecoder(const std::string& p)
		: pattern(p)
	{
	}

	std::string compute()
	{
		int curr_indx = 0;

		while (curr_indx < pattern.size())
		{
			if (isNumber(curr_indx))
			{
				std::string substr;
				curr_indx = processNum(curr_indx, substr);
				result.append(substr);
			} else {
				result.append(1, pattern[curr_indx]);
				++curr_indx;
			}
		}

		return result;
	}	

private:

	int processNum(int curr_indx, std::string &substr)
	{
		std::string numstr;
		int times = 0;

		while (pattern[curr_indx] >= '0' && pattern[curr_indx] <= '9')
		{
			numstr.append(1, pattern[curr_indx++]);
		}

		times = std::stoi(numstr);

		return replicate(curr_indx + 1, times, substr);
	}

	bool isNumber(int curr_index)
	{
		return pattern[curr_index] >= '0' && pattern[curr_index] <= '9';
	}

	int endParen(int curr, std::string& substr)
	{
		if (pattern[curr] == ']')
			return curr + 1;

		if (isNumber(curr))
		{
			std::string sub;
			int stop_indx = processNum(curr, sub);
			substr.append(sub);
			return endParen(stop_indx, substr);
		} else {
			substr.append(1, pattern[curr]);
			return endParen(curr + 1, substr);
		}		
	}

	int replicate(int curr, int times, std::string& substr)
	{		
		int end = endParen(curr, substr);
		int count = 0;
		int len = substr.length();

		while (count < times - 1)
		{
			substr.append(substr.substr(0, len));			
			++count;
		}			

		return end;
	}
};

// Circular rotations
class CircularRotations
{
private:
	const std::vector<int>& arr;

public:
	CircularRotations(const std::vector<int>& a)
		: arr(a)
	{

	}

	int compute()
	{
		// We need to find index of smallest element. This element
		// will have previous and next values greater than it
		int low = 0;
		int high = arr.size() - 1;

		while (low <= high)
		{
			if (arr[low] <= arr[high])
				return low;

			int mid = low + (high - low) / 2;
			int next = (mid + 1) % arr.size();
			int prev = (mid - 1 + arr.size()) % arr.size();

			if ((arr[mid] <= arr[prev]) && (arr[mid] <= arr[next]))
			{
				return mid;
			} else if (arr[mid] >= arr[low]) {
				// Left side is sorted, so look at right
				low = mid + 1;
			} else if (arr[mid] <= arr[high]) {
				// Right side is sorted
				high = mid - 1;
			}
				
		}

		return -1;
	}
};

//  Fibonacci
int fibonacci(int n)
{
	int first = 1;
	int second = 1;
	int third = 0;

	for (int i = 2; i < n; ++i)
	{
		// 1, 1, 2, 3, 5, 8, ...
		// f = 1 and s = 1
		// third = f + s
		// For the next number, f will be
		// current third and s will be current
		// f
		third = first + second;
		second = first;
		first = third;
	}

	return third;
}

// kth smallest element in BST
class Node1 {
public:
	int data;
	Node1* left;
	Node1* right;
};
class BinarySearchTree1
{
private:
	Node1* root;

public:
	BinarySearchTree1()
		: root(nullptr)
	{
		std::vector<int> arr{15, 10, 8, 12, 20, 16, 25};

		for (auto iter : arr)
		{
			insert(iter);
		}
	}

	~BinarySearchTree1()
	{
		cleanup(root);
	}

	void insert(int data)
	{
		insertHelper(root, data);
	}

	int kthSmallest(int k)
	{
		Node1* temp = nullptr;
		int foundIndex = 0;
		kthSmallestHelper(temp, foundIndex, root, k);

		if (temp == nullptr)
			return -1;

		return temp->data;
	}

	int kthLargest(int k)
	{
		Node1* temp = nullptr;
		int foundIndex = 0;
		kthLargestHelper(temp, foundIndex, root, k);

		if (temp == nullptr)
			return -1;

		return temp->data;
	}

private:

	void kthLargestHelper(Node1*&found, int& foundIndex, Node1* current, int target)
	{
		if (current == nullptr)
			return;

		// Traverse right subtree
		kthLargestHelper(found, foundIndex, current->right, target);

		// Now we have the largest element
		foundIndex = foundIndex + 1;

		if (foundIndex == target)
		{
			found = current;
		}

		// If we have found the node, stop recursing
		if (found != nullptr)
			return;

		// Traverse left subtree
		kthLargestHelper(found, foundIndex, current->left, target);
	}

	void kthSmallestHelper(Node1*&found, int& foundIndex, Node1* current, int target)
	{
		if (current == nullptr)
			return;

		// Traverse left subtree
		kthSmallestHelper(found, foundIndex, current->left, target);

		// Now we have the smallest element
		foundIndex = foundIndex + 1;

		if (foundIndex == target)
		{
			found = current;
		}

		// If we have found the node, stop recursing
		if (found != nullptr)
			return;

		// Traverse right subtree
		kthSmallestHelper(found, foundIndex, current->right, target);		
	}

	void insertHelper(Node1*& currnode, int data)
	{
		if (currnode == nullptr)
		{
			currnode = new Node1({ data, nullptr, nullptr });
		} else {
			if (data < currnode->data)
			{
				insertHelper(currnode->left, data);
			} else {
				insertHelper(currnode->right, data);
			}
		}
	}

	void cleanup(Node1*& currnode)
	{
		if (currnode)
		{
			cleanup(currnode->left);
			cleanup(currnode->right);
			//std::cout << "Deleting " << currnode->data << std::endl;
			delete currnode;
			currnode = nullptr;
		}
	}
};

// Duplicate element finder
// https://www.geeksforgeeks.org/find-duplicates-constant-array-elements-0-n-1-o1-space/
class DuplicateElementFinder
{
private:
	const std::vector<int>& arr;

public:
	DuplicateElementFinder(const std::vector<int>& a)
		: arr(a)
	{
		// Every array value correspons to element link
	}

	int find()
	{
		int slow = arr[0];
		int fast = arr[arr[0]];

		// Check if cycle exists
		while (slow != fast)
		{
			slow = arr[slow];
			fast = arr[arr[fast]];
		}

		// Check entry point
		fast = 0;
		while (slow != fast)
		{
			slow = arr[slow];
			fast = arr[fast];
		}

		return fast;
	}
};

// Left view of binary tree
class LeftViewBinaryTree
{
private:
	Node1* root;

public:
	LeftViewBinaryTree()
		: root(nullptr)
	{
		create(root, 1);
		create(root->left, 2);
		create(root->left->right, 4);
		create(root->right, 3);
		create(root->right->left, 5);
		create(root->right->right, 6);
		create(root->right->left->left, 7);
		create(root->right->left->right, 8);
	}

	~LeftViewBinaryTree()
	{
		cleanup(root);
	}

	void view()
	{
		std::queue<Node1*> queue;
		queue.push(root);

		while (!queue.empty())
		{			
			size_t count = queue.size();			
			size_t idx = count;

			while (idx > 0)
			{
				Node1* top = queue.front();
				queue.pop();

				if (idx == count)
					std::cout << top->data << "  ";

				if (top->left)
					queue.push(top->left);

				if (top->right)
					queue.push(top->right);
				
				--idx;
			}
		}

		std::cout << std::endl;
	}

private:	

	void create(Node1*& curr, int data)
	{
		curr = new Node1({data, nullptr, nullptr});
	}

	void cleanup(Node1*& curr)
	{
		if (curr)
		{
			cleanup(curr->left);
			cleanup(curr->right);
			delete curr;
			curr = nullptr;
		}
	}
};

// Combinations of words with english alphabets
class EnglishAlphabetWords
{
private:
	const std::string alphabets;
	std::vector<int>& digits;

public:
	EnglishAlphabetWords(std::vector<int>& d)
		: alphabets("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), digits(d)
	{
	}

	void compute()
	{
		std::string output;
		helper(0, output);
	}

private:
	void helper(int start, std::string result)
	{
		if (start == digits.size())
		{
			std::cout << result << std::endl;
			return;
		}			

		int length = 1;
		int dig_count = 0;
		int pow_of_ten = 0;

		for (int i = start; i < digits.size(); ++i)
		{			
			// Only combinations of 1 and 2 are allowed because alphabets only range from
			// 1 to 26
			if (length <= 2)
			{
				dig_count = std::pow(10, pow_of_ten)*dig_count + digits[i];

				if (dig_count >= 1 && dig_count <= 26)
				{								
					helper(i + 1, result + alphabets[dig_count - 1]);
				}				
			}

			++length;
			++pow_of_ten;
		}
	}
};

// Linked list reversal
struct Node2
{
	int data;
	Node2* right;
};

class LinkedListReversal
{
private:
	Node2* head;

public:
	LinkedListReversal()
		: head(nullptr)
	{
		const std::vector<int> arr{ 1, 2, 3, 4, 5 };
		for (int j : arr)
		{
			insert(head, j);
		}
	}

	~LinkedListReversal()
	{
		cleanup(head);
	}

	void print()
	{
		Node2* temp = head;

		while (temp)
		{
			std::cout << temp->data << "  ";
			temp = temp->right;
		}

		std::cout << std::endl;
	}

	void reverse()
	{		
		Node2* prev = nullptr;
		reverseHelper(head, prev);
	}

private:

	void reverseHelper(Node2*& curr, Node2*& prev)
	{
		if (curr)
		{
			Node2* current = curr;
			Node2* next = current->right;
			reverseHelper(next, current);

			if (next == nullptr) // We have reached the last element which will become the new head
				head = current;

			current->right = prev;
		}
	}

	void insert(Node2*& curr, int data)
	{
		if (curr == nullptr)
		{
			create(curr, data);
		} else {
			insert(curr->right, data);
		}
	}

	void create(Node2*& curr, int data)
	{
		curr = new Node2({data, nullptr});
	}

	void cleanup(Node2*& curr)
	{
		if (curr)
		{
			cleanup(curr->right);
			delete curr;
			curr = nullptr;
		}
	}
};

// Preorder traversal of binary tree
class PreorderTreeTraversal
{
private:
	Node1* root;

public:
	PreorderTreeTraversal()
		: root(nullptr)
	{
		create(root, 1);
		create(root->left, 2);
		create(root->left->left, 4);
		create(root->right, 3);
		create(root->right->left, 5);
		create(root->right->right, 6);
		create(root->right->left->left, 7);
		create(root->right->left->right, 8);
	}

	~PreorderTreeTraversal()
	{
		cleanup(root);
	}

	void print()
	{
		std::stack<Node1*> stack;
		stack.push(root);

		while (!stack.empty())
		{
			Node1* top = stack.top(); 
			stack.pop();
			std::cout << top->data << "  ";

			// Push in the opposite direction in which you want to traverse
			// This is because, if you insert left first and then right, the
			// top of the stack will contain the most recently inserted - the previous
			// right position and that is not what you want
			if (top->right)
				stack.push(top->right); 				

			if (top->left)
				stack.push(top->left);
		}

		std::cout << std::endl;
	}

private:

	void create(Node1*& curr, int data)
	{
		curr = new Node1({ data, nullptr, nullptr });
	}

	void cleanup(Node1*& curr)
	{
		if (curr)
		{
			cleanup(curr->left);
			cleanup(curr->right);
			delete curr;
			curr = nullptr;
		}
	}
};

// Quick sort
class QuickSorter
{
private:
	std::vector<int>& arr;

public:
	QuickSorter(std::vector<int>& a)
		: arr(a)
	{

	}

	void sort()
	{
		helper(0, arr.size() - 1);
	}

	void print()
	{
		for (int j : arr)
		{
			std::cout << j << "  ";
		}

		std::cout << std::endl;
	}

private:
	int sortAndReturn(int low, int high)
	{
		int low_indx = low;
		int high_indx = high - 1;

		while (low_indx <= high_indx)
		{
			if (arr[low_indx] < arr[high])
			{
				++low_indx;
			} else if (arr[high_indx] > arr[high]) {
				--high_indx;
			} else if (arr[low_indx] > arr[high_indx]) {
				std::swap(arr[low_indx], arr[high_indx]);
				++low_indx;
				--high_indx;
			}
		}

		std::swap(arr[low_indx], arr[high]);
		return low_indx;
	}

	void helper(int low, int high)
	{
		if (low <= high)
		{
			int indx = sortAndReturn(low, high);
			helper(low, indx - 1);
			helper(indx + 1, high);
		}
	}
};

// IterativeGraphDFS
struct Edge
{
	int src;
	int dest;
};

class IterativeGraphDFS
{
private:
	std::vector<std::vector<int>> adj;
	int nodes;

public:
	IterativeGraphDFS(const std::vector<Edge>& edges, int n)
		: nodes(n)
	{
		adj.resize(nodes);

		for (const auto& iter : edges)
		{
			adj[iter.src].push_back(iter.dest);
			adj[iter.dest].push_back(iter.src);
		}
	}

	void traverse()
	{
		std::vector<bool> visited(nodes, false);
		
		for (int i = 0; i < nodes; ++i)
		{
			if (!visited[i])
			{
				traverseHelper(i, visited);
			}
		}

		std::cout << std::endl;		
	}

private:
	void traverseHelper(int start, std::vector<bool>& visited)
	{
		std::stack<int> stack;
		stack.push(start);
		visited[start] = true;

		while (!stack.empty())
		{
			int top = stack.top();
			stack.pop();
			std::cout << top << "  ";

			for (auto iter = adj[top].rbegin(); iter != adj[top].rend(); ++iter)
			{
				if (!visited[*iter])
				{
					visited[*iter] = true;
					stack.push(*iter);
				}
			}
		}
	}
};

// Multiply upto previous n elements
class Multiplier
{
private:
	std::vector<int> elems;
	int n;
	int element_count;
	int pdt;
	int start_element_index;
	int result;

public:
	Multiplier(int number)
		: n(number), element_count(0), pdt(1), start_element_index(0), result(1)
	{
		elems = std::vector<int>(n, 0);
	}

	int find(int value)
	{		
		if (element_count < n) {
			pdt *= value;					
			result = result == 0 ? 0 : value;
		} else {
			pdt /= elems[start_element_index];
			pdt *= value;
			result = pdt;
		}		

		if (pdt == 0)
		{
			result = 0;
			pdt = 1;
			element_count = 0;
			elems[start_element_index] = 1;
		} else {
			elems[start_element_index] = value;			
		}
		
		start_element_index = (++start_element_index) % n;
		++element_count;
		return result;
	}
};

int main()
{
	// Dutch national flag problem
	/*std::vector<int> arr1{ 0, 1, 2, 2, 1, 0, 0, 2, 0, 1, 1, 0 };
	DutchSorter obj1(arr1);
	std::cout << "Before sorting" << std::endl;
	obj1.print();
	obj1.sort();
	std::cout << "After sorting" << std::endl;
	obj1.print();*/

	// String interleaving problem
	/*const std::string first("AB");
	const std::string second("CD");
	StringInterleaver obj(first, second);
	obj.combine();*/

	// Substrings of a string
	/*const std::string str("abcd");
	Substring obj;
	obj.compute(str);*/

	// Combination of words from digits
	/*std::vector<std::vector<char>> list{
		{'A', 'B', 'C', 'D'},
		{'E', 'F', 'G', 'H', 'I', 'J', 'K'},
		{'L', 'M', 'N', 'O', 'P', 'Q'},
		{'R', 'S', 'T'},
		{'U', 'V', 'W', 'X', 'Y', 'Z'}
	};

	std::vector<int> keys{ 0, 2, 0 };
	Combinations obj(list, keys);
	obj.compute();*/

	// String reversal
	/*std::string str("preparation Interview Technical IT for material good provide We");;
	ReverseString obj(str);
	obj.performWithStack();
	obj.performWithoutStack();*/

	// Combinatios of numbers of certain length
	/*std::vector<int> arr{ 1, 2, 3 };
	int k = 2;
	NumericCombinations obj(arr, k);
	obj.find();*/

	// Maximize value of expression
	/*const std::vector<int> arr{ 3, 9, 10, 1, 30, 40 };
	ValueMaximizer obj(arr);
	int result = obj.compute();
	std::cout << "Maximum value is " << result << std::endl;*/

	// String decoder
	/*std::string str1("3[a]2[bc]");
	StringDecoder obj1(str1);
	std::string result1 = obj1.compute();
	std::cout << "Pattern:  " << str1 << "  Result:  " << result1 << std::endl;*/

	/*std::string str2("2[ab3[c]]2[bc]ef");
	StringDecoder obj2(str2);
	std::string result2 = obj2.compute();
	std::cout << "Pattern:  " << str2 << "  Result:  " << result2 << std::endl;*/

	// Circular rotations
	/*const std::vector<int> arr{ 8, 9, 10, 2, 5, 6 };
	CircularRotations obj(arr);
	int result = obj.compute();
	std::cout << "Number of circular rotations is " << result << std::endl;*/

	// Fibonacci
	//std::cout << "Fibonacii of 9 is " << fibonacci(9) << std::endl;

	// Kth smallest element in a BST
	/*BinarySearchTree1 obj;
	for (int i = 1; i <= 7; ++i)
	{
		std::cout << i << " smallest element is " << obj.kthSmallest(i) << std::endl;		
	}
	std::cout << std::endl;
	for (int i = 1; i <= 7; ++i)
	{		
		std::cout << i << " largest element is " << obj.kthLargest(i) << std::endl;
	}*/

	// Duplicate element finder
	/*const std::vector<int> arr{ 1, 2, 3, 4, 5, 6, 3 };
	DuplicateElementFinder obj(arr);
	int result = obj.find();
	std::cout << "Duplicate element is " << result << std::endl;*/

	// Left view of binary tree
	/*LeftViewBinaryTree obj;
	obj.view();*/

	// Combination of english alphabet words
	/*std::vector<int> digits{ 1, 2, 2, 1 };
	EnglishAlphabetWords obj(digits);
	obj.compute();*/

	// Linked list reversal
	/*LinkedListReversal obj;
	obj.print();
	obj.reverse();
	obj.print();*/

	// Iterative preorder traversal of tree
	/*PreorderTreeTraversal obj;
	obj.print();*/

	// Quick sort on an array
	/*std::vector<int> arr{ 9, -3, 5, 2, 6, 8, -6, 1, 3 };
	QuickSorter obj(arr);
	obj.print();
	obj.sort();
	obj.print();*/


	// Iterative graph DFS
	/*const std::vector<Edge> edges {
		{1, 2}, {1, 7}, {1, 8}, {2, 3},
		{2, 6}, {3, 4}, {3, 5}, {8, 9},
		{8, 12}, {9, 10}, {9, 11}
	};

	IterativeGraphDFS obj(edges, 13);
	obj.traverse();*/

	// Multiplier
	Multiplier obj1(3);
	int x1 = obj1.find(1);
	int x2 = obj1.find(2);
	int x3 = obj1.find(3);
	int x4 = obj1.find(5);
	int x5 = obj1.find(6);
	int x6 = obj1.find(0);
	int x7 = obj1.find(0);
	int x8 = obj1.find(2);
	int x9 = obj1.find(3);
	int x10 = obj1.find(5);
	int x11 = obj1.find(4);
	std::cout << "find(1)  :  " << x1 << std::endl;
	std::cout << "find(2)  :  " << x2 << std::endl;
	std::cout << "find(3)  :  " << x3 << std::endl;
	std::cout << "find(5)  :  " << x4 << std::endl;
	std::cout << "find(6)  :  " << x5 << std::endl;
	std::cout << "find(0)  :  " << x6 << std::endl;
	std::cout << "find(0)  :  " << x7 << std::endl;
	std::cout << "find(2)  :  " << x8 << std::endl;
	std::cout << "find(3)  :  " << x9 << std::endl;
	std::cout << "find(5)  :  " << x10 << std::endl;
	std::cout << "find(4)  :  " << x11 << std::endl;

	/*Multiplier obj2(4);
	int x12 = obj2.find(1);
	int x13 = obj2.find(3);
	int x14 = obj2.find(4);
	int x15 = obj2.find(5);
	int x16 = obj2.find(2);
	int x17 = obj2.find(3);
	std::cout << "find(1)  :  " << x12 << std::endl;
	std::cout << "find(3)  :  " << x13 << std::endl;
	std::cout << "find(4)  :  " << x14 << std::endl;
	std::cout << "find(5)  :  " << x15 << std::endl;
	std::cout << "find(2)  :  " << x16 << std::endl;
	std::cout << "find(3)  :  " << x17 << std::endl;
	std::cout << "find(0)  :  " << obj2.find(0) << std::endl;
	std::cout << "find(2)  :  " << obj2.find(2) << std::endl;
	std::cout << "find(2)  :  " << obj2.find(2) << std::endl;
	std::cout << "find(2)  :  " << obj2.find(2) << std::endl;
	std::cout << "find(3)  :  " << obj2.find(3) << std::endl;
	std::cout << "find(4)  :  " << obj2.find(4) << std::endl;*/
	return 0;
}