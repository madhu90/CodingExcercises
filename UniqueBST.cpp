#include <iostream>
#include <vector>

// QUESTION: https://leetcode.com/problems/unique-binary-search-trees/
// REFERENCE: http://www.zrzahid.com/number-of-unique-binary-search-trees/
//            https://www.quora.com/Given-n-how-many-structurally-unique-BSTs-binary-search-trees-that-store-values-1-to-n-are-there-How-would-I-come-up-with-the-solution-Can-you-explain-the-thought-process-that-leads-to-the-solution
//            https://www.geeksforgeeks.org/construct-all-possible-bsts-for-keys-1-to-n/
//            https://www.geeksforgeeks.org/number-of-unique-bst-with-a-given-key-dynamic-programming/

/**
 * Let C(root) be the total of ways in which we can create a binary tree with "root" as the root. It is:
 * C(root) = C(root)*C(root.left)*C(root.right)
 * This can be recursively computed. Let's consider {1,2,3}:
 * a) Choose 1 as root (number of ways = 1). There are (1 - 1) possible left subtress and (3 - 1) possible right subtrees
 * b) Choose 2 as root (number of ways = 1). There are (2 - 1) possible left subtrees and (3 - 2) possible right subtrees
 * c) Choose 3 as root (number of ways = 1). There are (3 - 1) possible left subtress and (3 - 3) possible right subtrees
 *
 * We sum up the results of a), b) and c) and the number of ways to pick a root or an empty tree is 1. This can be expressed as:
 *
 * C(n) = C(0)*C(n - 1) + C(1)*C(n - 2) + ... + C(n - 1)*C(0)
 * C(n) = summation from i = 1 to n C(i - 1)*C(n - i) => Catalan numbers
 */

struct Node
{
	int data;
	Node* left;
	Node* right;	
};

class BinaryTree
{
private:
	Node* root;

public:
	void insert(int data)
	{
		helper(root, data);
	}

	void insertLeft(Node*& left)
	{
		root->left = left;
	}

	void insertRight(Node*& right)
	{
		root->right = right;
	}

	~BinaryTree()
	{
		cleanup(root);
	}

	BinaryTree(int dat)
		: root(nullptr)
	{
		insert(dat);
	}

	BinaryTree(Node*& ptr)
		: root(ptr)
	{

	}

	void preorder() const
	{
		preorderHelper(root);
		std::cout << std::endl;
	}

private:

	void preorderHelper(Node* curr) const
	{
		if (curr)
		{
			std::cout << curr->data << "  ";
			preorderHelper(curr->left);			
			preorderHelper(curr->right);
		}
	}

	void cleanup(Node*& curr)
	{
		if (curr)
		{
			cleanup(curr->left);
			cleanup(curr->right);
			delete curr;
			curr = nullptr;
		}
	}

	void helper(Node*& curr, int data)
	{
		if (curr == nullptr)
		{
			curr = new Node({data, nullptr, nullptr});
			return;
		} else {
			if (data < curr->data)
			{
				helper(curr->left, data);
			} else {
				helper(curr->right, data);
			}
		}
	}
};

class BinaryTreesViewer
{
private:
	std::vector<BinaryTree*> trees;
	int N;

public:
	BinaryTreesViewer(int n)
		: N(n)
	{

	}

	~BinaryTreesViewer()
	{
		for (size_t i = 0; i < trees.size(); ++i)
		{
			delete trees[i];
		}
	}

	void generate()
	{
		std::vector<Node*> result = generateHelper(1, N);

		for (size_t i = 0; i < result.size(); ++i)
		{
			trees.emplace_back(new BinaryTree(result[i]));
		}

		print();
	}

	void print()
	{
		for (const auto& iter : trees)
		{
			iter->preorder();
		}
	}

private:
	std::vector<Node*> generateHelper(int start, int end)
	{
		std::vector<Node*> list;

		if (start > end)
		{
			list.push_back(nullptr);
			return list;
		}

		for (int i = start; i <= end; ++i)
		{
			std::vector<Node*> leftTrees = generateHelper(start, i - 1);
			std::vector<Node*> rightTrees = generateHelper(i + 1, end);

			// Now we know left and right subtrees for i
			for (int j = 0; j < leftTrees.size(); ++j)
			{
				Node* currLeft = leftTrees[j];

				for (int k = 0; k < rightTrees.size(); ++k)
				{
					Node* currRight = rightTrees[k];
					Node* newNode = new Node({ i, nullptr, nullptr });
					newNode->left = currLeft;
					newNode->right = currRight;
					list.push_back(newNode);					
				}		

			}
		}

		return list;
	}
};

class BruteForceBinaryTreeCounter
{
private:
	int N;

public:

	BruteForceBinaryTreeCounter(int n)
		: N(n)
	{

	}

	int find()
	{
		return findHelper(N);
	}

private:
	int findHelper(int root)
	{
		if (root <= 1)
			return 1;

		int count = 0;
		int leftTrees = 0;
		int rightTrees = 0;

		for (int i = 1; i <= root; ++i)
		{
			leftTrees = findHelper(i - 1);
			rightTrees = findHelper(root - i);
			count = count + leftTrees*rightTrees;
		}

		return count;
	}
};

class DPTreeCounter
{
private:
	int N;

public:
	DPTreeCounter(int n)
		: N(n)
	{

	}

	int result()
	{
		std::vector<int> dp(N + 1, 0);
		dp[0] = 1;
		dp[1] = 1;

		for (int i = 2; i <= N; ++i)
		{
			// Let's look at all the left subtrees from 1 to i
			for (int j = 1; j <= i; ++j)
			{
				//      rooted at i + left subtrees*right subtrees
				dp[i] = dp[i] + (dp[j - 1] * dp[i - j]);
			}
		}

		return dp[N];
	}
};

int main()
{
	BruteForceBinaryTreeCounter obj1(3);
	std::cout << "Number of unique binary trees are " << obj1.find() << std::endl;

	BinaryTreesViewer obj2(3);
	obj2.generate();

	DPTreeCounter obj3(3);
	std::cout << "Number of unique binary trees are " << obj3.result() << std::endl;
	return 0;
}