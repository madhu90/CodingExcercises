#include <iostream>
#include <vector>

struct Node
{
	int data;
	Node* next;

	Node()
		: data(0), next(nullptr)
	{

	}
};

class LinkedList
{
private:
	Node* head;

public:
	LinkedList()
		: head(nullptr)
	{

	}

	~LinkedList()
	{
		cleanup(head);
	}

	void create()
	{
		std::vector<int> arr{ 1, 2, 3, 4, 5 };

		for (auto iter : arr)
		{
			insert(head, iter);
		}

		head->next->next->next->next->next = head->next->next;
	}

	bool hasCycle()
	{
		Node* slow = head;
		Node* fast = head;

		while (slow && fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast)
				return true;
		}

		return false;
	}

private:

	void cleanup(Node*& root)
	{
		if (root && root->data != 5)
		{
			cleanup(root->next);
			std::cout << "Destroying " << root->data << std::endl;
			delete root;
			root = nullptr;
		} else if (root->data == 5) {
			std::cout << "Destroying " << root->data << std::endl;
			delete root;
			root = nullptr;
		}
	}

	void insert(Node*& root, int dat)
	{
		if (root == nullptr)
		{
			root = new Node();
			root->data = dat;
			root->next = nullptr;
			return;
		} else {
			insert(root->next, dat);
		}
	}
};

int main()
{
	LinkedList obj;
	obj.create();
	std::cout << "Has cycle : " << obj.hasCycle() << std::endl;
	return 0;
}