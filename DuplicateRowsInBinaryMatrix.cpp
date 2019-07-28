#include <iostream>
#include <vector>
#include <unordered_map>

// QUESTION: https://www.techiedelight.com/find-duplicate-rows-binary-matrix/


class DuplicateRowFinder
{
public:
	void compute(const std::vector<std::vector<int>>& vec)
	{
		std::unordered_map<int, bool> map;

		for (int i = 0; i < vec.size(); ++i)
		{
			int num = 0;

			// Decimal representation of number
			for (int j = vec[i].size() - 1; j >= 0; --j)
			{
				int exp = std::pow(2, vec[i].size() - 1 - j);
				num += vec[i][j] * exp;
			}				

			if (map.find(num) != map.end())
			{
				std::cout << "Duplicate row found at index " << i + 1 << std::endl;
			} else {
				map[num] = true;
			}
		}
	}
};

class BinaryTrie
{
private:
	BinaryTrie* character[2];
	bool isLeaf;

private:
	void deleteHelper(BinaryTrie*& curr)
	{
		if (curr)
		{
			deleteHelper(curr->character[0]);
			deleteHelper(curr->character[1]);
			delete curr;
			curr = nullptr;
		}
	}

	bool insert(const std::vector<int>& vec)
	{
		bool exists = true;
		BinaryTrie* curr = this;

		for (size_t i = 0; i < vec.size(); ++i)
		{
			if (curr->character[vec[i]] == nullptr)
			{
				exists = false;
				curr->character[vec[i]] = new BinaryTrie();
			}

			curr = curr->character[vec[i]];
		}

		return exists;
	}

public:
	BinaryTrie()
	{
		character[0] = nullptr;
		character[1] = nullptr;
		isLeaf = false;
	}

	~BinaryTrie()
	{
		if (character[0])
			deleteHelper(character[0]);

		if (character[1])
			deleteHelper(character[1]);
	}



	void isThereDuplicate(const std::vector<std::vector<int>>& mat)
	{
		for (size_t i = 0; i < mat.size(); ++i)
		{
			if (insert(mat[i]))
			{
				std::cout << "Duplicate row found at index " << i + 1 << std::endl;
			}
		}
	}
};

int main()
{
	std::vector<std::vector<int>> mat{
		{1, 0, 0, 1, 0},
		{0, 1, 1, 0, 0},
		{1, 0, 0, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 1, 1, 0, 0}
	};

	BinaryTrie obj;
	obj.isThereDuplicate(mat);
	DuplicateRowFinder obj1;
	obj1.compute(mat);
	return 0;
}