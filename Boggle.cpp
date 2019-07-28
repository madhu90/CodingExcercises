#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

// QUESTION: https://www.geeksforgeeks.org/boggle-find-possible-words-board-characters/ (DFS based solution)
//			 https://www.geeksforgeeks.org/boggle-set-2-using-trie/


/**
 * Using a memory efficient trie. Instead of storing an array of pointers to alphabets
 * in every node, we store the subsequent characters in a hash map => memory efficient. The process
 * of finding words in the board is different here:
 *
 * 1) Build a trie based on all strings in the dictionary
 * 2) For each character in the board, we need to know if that is a starting alphabet to any word
 *    in the dictionary. For this, the trie root must point to a map for the character. If this entry
 *    is null, we can discard the character in the board for being the starting alphabet
 * 3) If the root has an entry, pass that entry into a recursive helper function that will find all subsequent
 *    alphabets. Here again, we look at 8 different positions from the board. The next move is safe if the
 *    coordinate is valid, it is not visited AND the current trie has an entry for the next character. Instead
 *    of generating all moves from the board, we iterate over all entries in the current trie's map and check to see
 *    if moving in any of the 8 directions generates a potential subsequent character
 * 4) We need to keep track of visited nodes
 * 5) We have found a word if the trie passed to the recursive function is a leaf
 * 6) To avoid duplicate strings which are found, we store the results in an unordered_set
 */

class Trie
{
private:
	std::unordered_map<char, Trie*> character;
	bool isleaf;

private:
	void deleteHelper(Trie*& curr)
	{
		for (auto& iter : curr->character)
		{			
			Trie* toDel = iter.second;
			char c = iter.first;
			deleteHelper(toDel);	

			if (toDel->isleaf || !hasChildren(toDel))
			{
				std::cout << "Destroying " << c << std::endl;
				delete toDel;
				toDel = nullptr;
			}			
		}

		curr->character.clear();
	}

public:
	Trie()
		: isleaf(false)
	{

	}

	~Trie()
	{
		for (auto& iter : character)
		{
			Trie* temp = iter.second;
			deleteHelper(temp);
			std::cout << "Destroying " << iter.first << std::endl;
			delete temp;
			temp = nullptr;
		}
	}

	void insert(std::string str)
	{
		Trie* curr = this;

		for (int i = 0; i < str.length(); ++i)
		{
			if (curr->character.find(str[i]) == curr->character.end())
			{
				std::cout << "Inserting " << str[i] << std::endl;
				curr->character[str[i]] = new Trie();
			}				

			curr = curr->character[str[i]];
		}

		curr->isleaf = true;
	}

	bool hasChildren(Trie* curr)
	{
		return !curr->character.empty();
	}

	bool hasEntry(char c)
	{
		return character.find(c) != character.end();
	}

	Trie* getTrie(char c)
	{
		return character[c];
	}

	bool isLeaf() const
	{
		return isleaf;
	}

	const std::unordered_map<char, Trie*> getMap() const
	{
		return character;
	}
};

class MemoryEfficientBoggle
{
private:
	Trie root;
	const std::vector<std::vector<char>>& board;
	const std::vector<std::string>& dictionary;
	std::unordered_set<std::string> foundwords;
	std::vector<std::vector<bool>> visited;
	std::vector<int> xcoords;
	std::vector<int> ycoords;
	int rows;
	int cols;

private:

	bool isSafe(int x, int y, char c)
	{
		return x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y] && board[x][y] == c;
	}

	void searchBoard(Trie* curr, int x, int y, std::string str)
	{
		visited[x][y] = true;
		str += board[x][y];

		if (curr->isLeaf())
		{
			foundwords.insert(str);
		}		

		for (auto& iter : curr->getMap())
		{
			char ch = iter.first;
			Trie* adjmap = iter.second;

			for (int i = 0; i < xcoords.size(); ++i)
			{
				int newx = x + xcoords[i];
				int newy = y + ycoords[i];

				if (isSafe(newx, newy, ch))
					searchBoard(adjmap, newx, newy, str);
			}
		}

		visited[x][y] = false;
	}

public:
	MemoryEfficientBoggle(const std::vector<std::vector<char>>& b, const std::vector<std::string>& d)
		: root(Trie()), board(b), dictionary(d)
	{
		rows = b.size();
		cols = b[0].size();
		xcoords = { 1, -1, 0, 0, 1, 1, -1, -1 };
		ycoords = { 0, 0, 1, -1, 1, -1, 1, -1 };
		visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

		// Populate trie
		for (auto& iter : dictionary)
		{
			root.insert(iter);
		}
	}

	void find()
	{
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (root.hasEntry(board[i][j]))
				{
					std::string str;
					searchBoard(root.getTrie(board[i][j]), i, j, str);
				}
			}
		}

		std::cout << "Words in dictionary(using trie) are" << std::endl;
		for (auto iter : foundwords)
		{
			std::cout << iter << std::endl;
		}
	}
};

class WordFinder
{
private:
	const std::vector<std::vector<char>>& board;
	const std::vector<std::string>& dictionary;
	std::unordered_set<std::string> foundwords;
	std::vector<std::vector<bool>> visited;
	std::vector<int> xcoords;
	std::vector<int> ycoords;
	int rows;
	int cols;

private:
	bool isSafe(int x, int y)
	{
		return x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y];
	}

	bool isInDictionary(const std::string& str)
	{
		for (auto iter : dictionary)
		{
			if (strcmp(iter.c_str(), str.c_str()) == 0)
				return true;
		}

		return false;
	}

	void findHelper(int x, int y, std::string str)
	{
		visited[x][y] = true;
		str += board[x][y];
		foundwords.insert(str);		

		for (size_t i = 0; i < xcoords.size(); ++i)
		{
			int newx = x + xcoords[i];
			int newy = y + ycoords[i];
			
			if (isSafe(newx, newy))
				findHelper(newx, newy, str);
		}

		visited[x][y] = false;
	}

public:
	WordFinder(const std::vector<std::vector<char>>& b, const std::vector<std::string>& d)
		: board(b), dictionary(d)
	{
		rows = b.size();
		cols = b[0].size();
		xcoords = {1, -1, 0, 0, 1, 1, -1, -1};
		ycoords = {0, 0, 1, -1, 1, -1, 1, -1};
		visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
	}

	void find()
	{
		std::string str;		
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[0].size(); ++j) {
				findHelper(i, j, str);
			}
		}

		std::cout << "Words in dictionary are" << std::endl;
		for (auto iter : foundwords)
		{
			if (isInDictionary(iter))
				std::cout << iter << std::endl;
		}
	}
};

int main()
{
	std::vector<std::vector<char>> board
	{
		{'M', 'S', 'E', 'F'},
		{'R', 'A', 'T', 'D'},
		{'L', 'O', 'N', 'E'}
	};

	std::vector<std::string> dictionary{"START", "NOTE", "SAND", "STONED"};
	WordFinder obj1(board, dictionary);
	obj1.find();

	MemoryEfficientBoggle obj2(board, dictionary);
	obj2.find();
	return 0;
}