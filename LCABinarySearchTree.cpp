/** Construct the following binary search tree:	    
*			  15
*			/    \
*		  10	  25
*		 /  \	  /  \
*		8	 12	 20   30
*	   / \		/  \		    
*	 6     9  18    22
* For this tree, find the lowest common ancestors of the following
* pairs of nodes:
* LCA(6,12) = 3
* LCA(10,12) = 5
* LCA(20,6) = 3
* LCA(18,22) = 20
* LCA(30,30) = 30
*/

#include <iostream>
#include <memory>

class Node {
public:
	int data;
	Node* left;
	Node* right;

public:
	Node(int value)
		: data(value), left(nullptr), right(nullptr)
	{		
	}
};

class BinarySearchTree
{
private:
	Node* root;

public:
	BinarySearchTree()
	{
		construct();
	}

	~BinarySearchTree()
	{
		destroy(root);
	}

	int findLCA(int x, int y)
	{		
		return findLCAHelper(root, x, y);
	}

private:

	void destroy(Node*& rootnode)
	{
		if (rootnode)
		{
			destroy(rootnode->left);
			destroy(rootnode->right);
			delete(rootnode);
			rootnode = nullptr;
		}
	}

	int findLCAHelper(Node* rootnode, int x, int y)
	{
		if (rootnode->data > x && rootnode->data > y)
		{
			return findLCAHelper(rootnode->left, x, y);
		} else if (rootnode->data < x && rootnode->data < y) {
			return findLCAHelper(rootnode->right, x, y);
		} else {
			return rootnode->data;
		}
	}

	void construct()
	{			
		root = addNode(root, 15);
		root = addNode(root, 10);		
		root = addNode(root, 8);
		root = addNode(root, 6);
		root = addNode(root, 9);
		root = addNode(root, 12);
		root = addNode(root, 25);
		root = addNode(root, 20);
		root = addNode(root, 18);
		root = addNode(root, 22);
		root = addNode(root, 30);
	}

	Node* addNode(Node*& rootnode, int data)
	{
		if (rootnode == nullptr) {
			return new Node(data);
		} else {			
			if (rootnode->data > data)
			{
				rootnode->left = addNode(rootnode->left, data);
			} else {
				rootnode->right = addNode(rootnode->right, data);
			}

			return rootnode;
		}
	}	
};

int main()
{
	BinarySearchTree obj;	
	std::cout << "LCA(6, 12) " << obj.findLCA(6, 12) << std::endl;
	std::cout << "LCA(10, 12) " << obj.findLCA(10, 12) << std::endl;
	std::cout << "LCA(20, 6) " << obj.findLCA(20, 6) << std::endl;
	std::cout << "LCA(18, 22) " << obj.findLCA(18, 22) << std::endl;
	std::cout << "LCA(30, 30) " << obj.findLCA(30, 30) << std::endl;
	return 0;
}