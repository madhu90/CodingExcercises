#include <iostream>
#include <vector>

// QUESTION: https://www.techiedelight.com/replace-every-element-array-least-greater-element-right/

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
};

class BST
{
private:
	Node* root;
	std::vector<int>& arr;

private:
	void insert(Node*& curr,int dat, int& succesor)
	{
		if (curr == nullptr)
		{
			curr = new Node({dat, nullptr, nullptr});
			return;
		}

		if (dat < curr->data)
		{
			succesor = curr->data;
			insert(curr->left, dat, succesor);
		} else {
			insert(curr->right, dat, succesor);
		}
	}

	void cleanup(Node* curr)
	{
		if (curr)
		{
			cleanup(curr->left);
			cleanup(curr->right);
			std::cout << "Deleting " << curr->data << std::endl;
			delete curr;
			curr = nullptr;
		}
	}

	void printHelper(Node*curr)
	{
		if (curr)
		{
			printHelper(curr->left);
			std::cout << curr->data << std::endl;
			printHelper(curr->right);
		}
	}

public:
	BST(std::vector<int>& input)
		: root(nullptr), arr(input)
	{
		for (int i = arr.size() - 1; i >= 0; --i)
		{
			// We start from right because, we are suppose to replace an element
			// with the least greatest entry to its right - we should see everything
			// at the right for knowing the right placement for value at the left
			int succesor = -1;
			insert(root, arr[i], succesor);
			arr[i] = succesor;
		}
	}

	~BST()
	{
		cleanup(root);
	}

	void print()
	{
		std::cout << "Array contents are" << std::endl;
		for (auto iter : arr)
		{
			std::cout << iter << std::endl;
		}
	}
};

int main()
{
	std::vector<int> arr{10, 100, 93, 32, 35, 65, 80, 90, 94, 6};
	BST obj(arr);
	obj.print();
	return 0;
}