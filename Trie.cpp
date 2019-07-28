#include <iostream>
#include <string>

constexpr size_t ALPHABETS = 26;
constexpr size_t asciiastarts = 97;

class Trie
{
private:
	Trie* character[ALPHABETS];
	bool isLeaf;

private:
	void deleteHelper(Trie*& curr)
	{
		if (curr)
		{
			for (size_t i = 0; i < ALPHABETS; ++i)
			{
				deleteHelper(curr->character[i]);
				delete curr->character[i];
				curr->character[i] = nullptr;
			}
		}
	}

	bool deleteHelper(Trie*& curr, std::string str)
	{
		if (curr == nullptr)
			return false;

		if (str.length())
		{
			if (curr &&
				curr->character[str[0] - asciiastarts] != nullptr &&
				deleteHelper(curr->character[str[0] - asciiastarts], str.substr(1)) &&
				curr->isLeaf == false)
			{
				if (!haveChildren(curr))
				{
					delete curr;
					curr = nullptr;
					return true;
				} else {
					return false;
				}
			}
		}

		if (str.length() == 0 && curr->isLeaf)
		{
			if (!haveChildren(curr))
			{
				delete curr;
				curr = nullptr;
				return true;
			} else {
				curr->isLeaf = false;
				return false;
			}
		}
	}


public:
	Trie()
		: isLeaf(false)
	{
		for (size_t i = 0; i < ALPHABETS; ++i)
			character[i] = nullptr;
	}

	~Trie()
	{
		for (size_t i = 0; i < ALPHABETS; ++i)
		{
			if (character[i])
				deleteHelper(character[i]);
		}
	}

	void insert(std::string str)
	{		
		Trie* curr = this;

		for (size_t i = 0; i < str.length(); ++i)
		{
			// Creating a node at n'th position
			if (curr->character[str[i] - asciiastarts] == nullptr)
				curr->character[str[i] - asciiastarts] = new Trie;

			// Pointing to the node at n'th position
			curr = curr->character[str[i] - asciiastarts];
		}

		curr->isLeaf = true;
	}

	bool deletion(std::string str)
	{
		Trie* curr = this;
		return deleteHelper(curr, str);
	}

	bool search(std::string str)
	{
		Trie* curr = this;

		for (size_t i = 0; i < str.length(); ++i)
		{
			if (curr->character[str[i] - asciiastarts] == nullptr)
				return false;

			curr = curr->character[str[i] - asciiastarts];
		}

		return curr->isLeaf;
	}

	bool haveChildren(Trie* node)
	{
		for (size_t i = 0; i < ALPHABETS; ++i)
		{
			if (character[i] != nullptr)
				return true;
		}

		return false;
	}
};

int main()
{
	Trie obj;
	obj.insert("hello");
	std::cout << obj.search("hello") << std::endl;

	obj.insert("helloworld");
	std::cout << obj.search("helloworld") << std::endl;

	std::cout << obj.search("helll") << std::endl;

	obj.insert("hell");
	std::cout << obj.search("hell") << std::endl;

	obj.insert("h");
	std::cout << obj.search("h") << std::endl;

	obj.deletion("hello");
	std::cout << obj.search("hello") << std::endl;

	std::cout << obj.search("helloworld") << std::endl;
	std::cout << obj.search("hell") << std::endl;

	obj.deletion("h");
	std::cout << obj.search("h") << std::endl;
	std::cout << obj.search("hell") << std::endl;
	std::cout << obj.search("helloworld") << std::endl;

	obj.deletion("helloworld");
	std::cout << obj.search("helloworld") << std::endl;
	std::cout << obj.search("hell") << std::endl;

	obj.deletion("hell");
	std::cout << obj.search("hell") << std::endl;
	std::cout << obj.search("hell") << std::endl;
	return 0;
}