#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

/** The binary tree used:
 * 
 *			 1
 *		   /  \
 *		  2      3	
 *	      \	    / \
 *           4 5   6
 *		     / \
 *          7   8
 *
 * LEFT_VIEW: 1,2,4,7
 * RIGHT_VIEW: 1,3,6,8
 * TOP_VIEW: 2,1,3,6
 * BOTTOM_VIEW: 4,7,8,6
 */


enum VIEW : int
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class Node
{
public:
	int data;
	int offset;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	Node(int value)
		: data(value), offset(0), left(nullptr), right(nullptr)
	{

	}
};

class BinaryTree
{
private:
	std::unique_ptr<Node> fRoot;

public:
	BinaryTree()
	{
		fRoot = std::make_unique<Node>(1);
		fRoot->left = std::make_shared<Node>(2);
		fRoot->left->right = std::make_shared<Node>(4);
		fRoot->right = std::make_shared<Node>(3);
		fRoot->right->left = std::make_shared<Node>(5);
		fRoot->right->right = std::make_shared<Node>(6);
		fRoot->right->left->left = std::make_shared<Node>(7);
		fRoot->right->left->right = std::make_shared<Node>(8);
	}

	void print(VIEW option)
	{
		switch (option)
		{
		case LEFT:
		{
			// 1st node in each level
			std::queue<const Node*> queue;
			queue.push(fRoot.get());
			std::cout << "Left view of binary tree" << std::endl;
			
			while (!queue.empty())
			{
				size_t sz = queue.size();
				int i = 0;

				while (i++ < sz)
				{
					const Node* front = queue.front();
					queue.pop();

					if (i == 1)
						std::cout << front->data << "  ";

					if (front->left != nullptr)					
						queue.push(front->left.get());

					if (front->right != nullptr)
						queue.push(front->right.get());
				}				
			}

			std::cout << std::endl;
		}
		break;

		case RIGHT:
		{
			// Last node in each level
			std::queue<const Node*> queue;
			queue.push(fRoot.get());
			std::cout << "Right view of binary tree" << std::endl;

			while (!queue.empty())
			{
				size_t sz = queue.size();
				int i = 0;

				while (i++ < sz)
				{
					const Node* front = queue.front();
					queue.pop();

					if (i == sz)
						std::cout << front->data << "  ";

					if (front->left != nullptr)
						queue.push(front->left.get());

					if (front->right != nullptr)
						queue.push(front->right.get());
				}
			}

			std::cout << std::endl;
		}
		break;

		case TOP:
		{
			// Key = Distance from root
			// Value = Vector of std::pair<int, int>, where first is
			// value of node and second is level number
			std::unordered_map<int, std::vector<std::pair<int, int>>> map;
			populateMap(map, fRoot.get(), 0, 0);
			std::cout << "Top view of binary tree" << std::endl;

			for (auto iter1 : map)
			{
				auto map_entry = iter1.second;
				// Find the smallest level for a given distance and print
				// the node
				auto result = *std::min_element(map_entry.cbegin(), map_entry.cend(), 
					[](const auto& lhs, const auto& rhs)
				{
					return lhs.second < rhs.second;
				});

				std::cout << result.first << "  ";
			}

			std::cout << std::endl;

			/*for (auto iter1 = map.begin(); iter1 != map.end(); ++iter1)
			{
				for (auto iter2 : iter1->second)
				{
					std::cout << "For distance:  " << iter1->first << "  Node value:  " << iter2.first << "  Level number:  " << iter2.second << std::endl;
				}				 
			}*/
		}
		break;

		case BOTTOM:
		{
			// Key = Distance from root
			// Value = Vector of std::pair<int, int>, where first is
			// value of node and second is level number
			std::unordered_map<int, std::vector<std::pair<int, int>>> map;
			populateMap(map, fRoot.get(), 0, 0);
			std::cout << "Bottom view of binary tree" << std::endl;

			for (auto iter1 : map)
			{
				auto map_entry = iter1.second;
				// Find the largest level for a given distance and print
				// the node
				auto result = *std::min_element(map_entry.begin(), map_entry.end(), 
					[](const auto& lhs, const auto& rhs)
				{
					return lhs.second > rhs.second;
				});

				std::cout << result.first << "  ";
			}
			std::cout << std::endl;
		}
		break;
		}		
	}

private:
	void populateMap(
		std::unordered_map<int, std::vector<std::pair<int, int>>>& map,
		Node* root, 
		int distance,
		int level)
	{
		if (root)
		{			
			// In-order traversal so that, we can print nodes from
			// left-to-right
			populateMap(map, root->left.get(), distance - 1, std::pow(2, level));			
			map[distance].push_back(std::make_pair(root->data, level));
			populateMap(map, root->right.get(), distance + 1, std::pow(2, level));
		}		
	}
};

int main()
{
	BinaryTree obj;
	obj.print(VIEW::LEFT);
	obj.print(VIEW::RIGHT);
	obj.print(VIEW::TOP);
	obj.print(VIEW::BOTTOM);
	return 0;
}