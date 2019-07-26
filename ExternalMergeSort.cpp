// This program creates 10 files named input1.txt ... input10.txt and adds
// 1000 numbers in each of them. It then does a sort on each of these files
// Finally, it attempts to merge the sort results from all these files and
// create one output file with 10*1000 numbers
// QUESTION: https://www.techiedelight.com/external-merge-sort/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <limits>

class FileData
{
public:
	int data;
	int array_index;
	
	bool operator()(const FileData& a, const FileData& b) const
	{
		return a.data > b.data;
	}
};

class GenerateInputFiles
{
private:
	int numberOfFiles;
	int sizeOfEach;
	std::vector<std::ofstream> fileOutputHandles;
	std::vector<std::ifstream> fileInputHandles;
	std::vector<std::string> fileNames;
	std::ofstream outputFile;

private:
	void populateFile(int indx)
	{
		std::vector<int> arr;		
		arr.resize(sizeOfEach);

		// Generate data
		for (int i = 0; i < sizeOfEach; ++i)
		{
			arr[i] = std::rand() % sizeOfEach;
		}

		// Sort data
		std::sort(arr.begin(), arr.end());

		// Write data to file
		for (int i = 0; i < sizeOfEach; ++i)
		{
			fileOutputHandles[indx] << arr[i] << std::endl;
		}		
	}

	void closeOuputFileHandles()
	{
		for (auto& iter : fileOutputHandles)
		{
			if (iter.is_open())
			{
				iter.close();
			}			
		}
	}

	void closeInputFileHandles()
	{
		for (auto& iter : fileInputHandles)
		{
			if (iter.is_open())
			{
				iter.close();
			}
		}
	}

	int readFromFile(std::ifstream& str)
	{
		int result = std::numeric_limits<int>::min();
		std::string data;

		if (std::getline(str, data))
		{
			result = std::stoi(data);
		}

		return result;
	}

public:
	GenerateInputFiles(int num, int sz)
		: numberOfFiles(num), sizeOfEach(sz)
	{
		std::string fileName("input");
		std::string fileExtension(".txt");
		fileNames.resize(numberOfFiles);
		fileOutputHandles.resize(numberOfFiles);

		for (size_t i = 0; i < numberOfFiles; ++i)
		{
			fileNames[i] = fileName + std::to_string(i) + fileExtension;
			fileOutputHandles[i] = std::ofstream(fileNames[i]);			
			populateFile(i);
		}

		closeOuputFileHandles();
	}

	void externalMerge()
	{
		std::cout << "External merge sort" << std::endl;
		std::string outputFileName("output.txt");
		std::priority_queue<FileData, std::vector<FileData>, FileData> pq;		
		fileInputHandles.resize(numberOfFiles);
		
		// Get file handles
		for (size_t i = 0; i < numberOfFiles; ++i)
		{			
			fileInputHandles[i] = std::ifstream(fileNames[i]);			
		}

		// Add first element from each file in queue
		for (int i = 0; i < numberOfFiles; ++i)
		{
			if (fileInputHandles[i].is_open())
			{			
				int num = readFromFile(fileInputHandles[i]);
				pq.push({num, i});
			}
		}

		// Create output file
		outputFile = std::ofstream(outputFileName);
		while (!pq.empty())
		{
			FileData top = pq.top();
			pq.pop();
			outputFile << top.data << std::endl;
			int nextElement = readFromFile(fileInputHandles[top.array_index]);

			if (nextElement != std::numeric_limits<int>::min())
			{
				pq.push({nextElement, top.array_index});
			}
		}		
	}

	~GenerateInputFiles()
	{
		closeOuputFileHandles();
		closeInputFileHandles();		

		if (outputFile.is_open())
		{
			outputFile.close();
		}
	}
};

int main()
{
	int numFiles = 10;
	int sz = 1000;
	GenerateInputFiles obj(numFiles, sz);
	obj.externalMerge();
	return 0;
}
