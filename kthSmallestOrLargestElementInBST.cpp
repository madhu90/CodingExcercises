#include <iostream>

class Node {
public:
	int data;
	Node* left;
	Node* right;
};

class BinarySearchTree
{
private:
	Node* root;

public:
	BinarySearchTree()
		: root(nullptr)
	{

	}

	~BinarySearchTree()
	{
		cleanup(root);
	}

	void insert(int data)
	{
		insertHelper(root, data);
	}

	void print()
	{
		std::cout << "Printing BST..." << std::endl;
		printHelper(root);
	}

	int kthSmallest(int k)
	{
		int curr_idx = 0;
		return kthSmallestHelper(root, curr_idx, k);
	}

	int kthLargest(int k)
	{
		int curr_idx = 0;
		return kthLargestHelper(root, curr_idx, k);
	}

private:

	int kthLargestHelper(Node* currnode, int& curr_idx, int k)
	{
		if (currnode == nullptr)
			return std::numeric_limits<int>::max();

		int right = kthLargestHelper(currnode->right, curr_idx, k);

		if (right != std::numeric_limits<int>::max())
			return right;

		curr_idx += 1;
		if (curr_idx == k)
			return currnode->data;

		return kthLargestHelper(currnode->left, curr_idx, k);
	}

	int kthSmallestHelper(Node* currnode, int& curr_idx, int k)
	{
		if (currnode == nullptr)
			return std::numeric_limits<int>::min();

		int element = kthSmallestHelper(currnode->left, curr_idx, k);

		// We need to stop the recursion if we have found the node. If we
		// return std::numeric_limits<int>::min(), this means we have reached
		// the smallest node. If we receive any other value, we return it.
		// This return statement is important here to break the recurion after the
		// kth element is found. What we are saying is, if a reasonable number
		// is returned, it must be the smallest. So, don't continue to look
		// for it further
		if (element != std::numeric_limits<int>::min())
			return element;

		// After you return, you have the smallest element, Now, you need 
		// to find the kth smallest
		curr_idx += 1;
		if (curr_idx == k)
			return currnode->data;

		return kthSmallestHelper(currnode->right, curr_idx, k);
	}

	void printHelper(Node* currnode)
	{
		if (currnode)
		{
			printHelper(currnode->left);
			std::cout << currnode->data << std::endl;
			printHelper(currnode->right);
		}
	}

	void insertHelper(Node*& currnode, int data)
	{
		if (currnode == nullptr)
		{
			currnode = new Node({data, nullptr, nullptr});			
		} else {
			if (data < currnode->data)
			{
				insertHelper(currnode->left, data);
			} else {
				insertHelper(currnode->right, data);
			}				
		}		
	}

	void cleanup(Node*& currnode)
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

int main()
{
	BinarySearchTree bst;
	bst.insert(15);
	bst.insert(10);
	bst.insert(8);
	bst.insert(12);
	bst.insert(20);
	bst.insert(16);
	bst.insert(25);
	//bst.print();
	int k = 2;
	int element1 = bst.kthSmallest(k);
	std::cout << k << "th smallest element is " << element1 << std::endl;
	int element2 = bst.kthLargest(k);
	std::cout << k << "th largest element is " << element2 << std::endl;
	return 0;
}