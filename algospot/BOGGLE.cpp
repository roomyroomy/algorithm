#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int GRID_SIZE = 5;

bool existWord(vector<vector<char>> &table, string word)
{
	vector<vector<vector<bool>>> compTable;		// compTable[row][col][w] : w번째 index에 "word"가 존재하는가?
	int wordLength = word.size();
	bool result = false;
	vector<pair<int, int>> neighbor;

	neighbor.push_back(make_pair(-1, -1));
	neighbor.push_back(make_pair(0, -1));
	neighbor.push_back(make_pair(1, -1));
	neighbor.push_back(make_pair(-1, 0));
	neighbor.push_back(make_pair(1, 0));
	neighbor.push_back(make_pair(-1, 1));
	neighbor.push_back(make_pair(0, 1));
	neighbor.push_back(make_pair(1, 1));

	compTable.assign(wordLength, vector<vector<bool>>(GRID_SIZE, vector<bool>(GRID_SIZE, false)));

	for(int idxLetter = 0; idxLetter < wordLength; idxLetter++)
	{
		char currentChar = word.c_str()[idxLetter];
		int candidateCount = 0;
		for(int idxRow = 0; idxRow < GRID_SIZE; idxRow++)
		{
			for(int idxCol = 0; idxCol < GRID_SIZE; idxCol++)
			{
				if(idxLetter == 0)
				{
					char c = table[idxRow][idxCol];
					if(table[idxRow][idxCol] == currentChar)
					{
						compTable[idxLetter][idxRow][idxCol] = true;
						candidateCount++;
					}
				}
				else
				{
					for(int idxNeighbor = 0; idxNeighbor < neighbor.size(); idxNeighbor++)
					{
						int prevRow = idxRow + neighbor[idxNeighbor].first;
						int prevCol = idxCol + neighbor[idxNeighbor].second;

						if(prevRow >= 0 && prevRow < GRID_SIZE && prevCol >= 0 && prevCol < GRID_SIZE)
						{
							if(compTable[idxLetter - 1][prevRow][prevCol] == true && table[idxRow][idxCol] == currentChar)
							{
								compTable[idxLetter][idxRow][idxCol] = true;
								candidateCount++;
							}
						}
					}
				}
			}
		}
		if(candidateCount == 0)
			break;
		if(candidateCount > 0 && idxLetter == wordLength - 1)
			result = true;
	}

	return result;
}

int main()
{
	int c, n;
	
	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		vector<vector<char>> table;
		for(int idxStr = 0; idxStr < GRID_SIZE; idxStr++)
		{
			string str;
			cin >> str;

			table.push_back(vector<char>(0));
			for(int idxChar = 0; idxChar < GRID_SIZE; idxChar++)
			{
				table[idxStr].push_back(str.c_str()[idxChar]);
			}
		}

		cin >> n;

		for(int idxWord = 0; idxWord < n; idxWord++)
		{
			string word;
			cin >> word;
			cout << word << " ";
			if(existWord(table, word) == true)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}

	return 0;
}

/*
2
URLPM
XPRET
GIAET
XTNZY
XOQRS
6
PRETTY
GIRL
REPEAT
KARA
PANDORA
GIAZAPX
URLPM
XPRET
GIAET
XTNZY
XOQRS
5
GIRL
REPEAT
KARA
PANDORA
GIAZAPX
*/