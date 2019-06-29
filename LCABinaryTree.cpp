/** Construct the following binary tree:
  * 
  *			    1
  *			  /  \
  *			 /    \
  *		    2	   3
  *			\	  / \
  *			 4	 5   6
  *			    / \
  *			   7   8
  * For this tree, find the lowest common ancestors of the following
  * pairs of nodes:
  * LCA(6,7) = 3
  * LCA(5,8) = 5
  * LCA(3,6) = 3
  * LCA(2,5) = 1
  */
#include <iostream>
#include <memory>

class Node {
public:
	int data;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

public:
	Node(int value)
		: data(value), left(nullptr), right(nullptr)
	{
		//std::cout << "Constructing node with data: " << data << std::endl;
	}

	~Node() {
		//std::cout << "Destroying node with data: " << data << std::endl;
	}
};

class BinaryTree
{
private:
	std::unique_ptr<Node> root;

public:
	BinaryTree()
		: root(nullptr)
	{
		construct();
	}

	int findLCA(int x, int y)
	{
		Node* LCANode = nullptr;
		bool found = findLCAHelper(root.get(), LCANode, x, y);
		return found ? LCANode->data : std::numeric_limits<int>::max();
	}

private:
	void construct()
	{
		root = std::make_unique<Node>(1);
		root.get()->left = std::make_shared<Node>(2);
		root.get()->left.get()->right = std::make_shared<Node>(4);
		root.get()->right = std::make_shared<Node>(3);
		root.get()->right.get()->left = std::make_shared<Node>(5);
		root.get()->right.get()->right = std::make_shared<Node>(6);
		root.get()->right.get()->left.get()->left = std::make_shared<Node>(7);
		root.get()->right.get()->left.get()->right = std::make_shared<Node>(8);
	}	

private:
	bool findLCAHelper(Node* rootnode, Node*& LCA, int x, int y)
	{
		if (rootnode == nullptr)
			return false;

		if (rootnode->data == x || rootnode->data == y)
		{
			LCA = rootnode;
			return true;
		}

		bool left = findLCAHelper(rootnode->left.get(), LCA, x, y);
		bool right = findLCAHelper(rootnode->right.get(), LCA, x, y);

		if (left && right)
		{
			LCA = rootnode;
			return true;
		}

		return left || right;			
	}
};


int main()
{
	BinaryTree obj;
	std::cout << "LCA(6,7) = " << obj.findLCA(6,7) << std::endl;
	std::cout << "LCA(5,8) = " << obj.findLCA(5,8) << std::endl;
	std::cout << "LCA(3,6) = " << obj.findLCA(3,6) << std::endl;
	std::cout << "LCA(2,5) = " << obj.findLCA(2,5) << std::endl;
	return 0;
}