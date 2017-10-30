#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int blockSize = 5;

vector<char> cache;

vector<vector<pair<int, int>>> makePieces()
{
	vector<vector<pair<int, int>>> pieces(6);

	pieces[0].push_back(make_pair(0, 0));
	pieces[0].push_back(make_pair(1, 0));

	pieces[1].push_back(make_pair(0, 0));
	pieces[1].push_back(make_pair(0, 1));

	pieces[2].push_back(make_pair(0, 0));
	pieces[2].push_back(make_pair(0, 1));
	pieces[2].push_back(make_pair(1, 1));

	pieces[3].push_back(make_pair(0, 0));
	pieces[3].push_back(make_pair(1, 0));
	pieces[3].push_back(make_pair(1, 1));

	pieces[4].push_back(make_pair(0, 0));
	pieces[4].push_back(make_pair(0, 1));
	pieces[4].push_back(make_pair(1, 0));

	pieces[5].push_back(make_pair(0, 1));
	pieces[5].push_back(make_pair(1, 0));
	pieces[5].push_back(make_pair(1, 1));

	return pieces;
}

int available(vector<vector<bool>> &block, vector<pair<int, int>> &piece, int col, int row)
{
	int result = 0;
	for(int idx = 0; idx < piece.size(); idx++)
	{
		int dCol = col + piece[idx].first;
		int dRow = row + piece[idx].second;

		if(dCol >= blockSize || dRow >= blockSize || block[dCol][dRow] == true)
		{
			return 0;
		}
		else
		{
			result |= (1 << (dCol * blockSize + dRow));
		}
	}
	return result;
}

void setPiece(vector<vector<bool>> &block, vector<pair<int, int>> &piece, int col, int row, bool b)
{
	for(int idx = 0; idx < piece.size(); idx++)
	{
		int dCol = col + piece[idx].first;
		int dRow = row + piece[idx].second;
		block[dCol][dRow] = b;
	}
}

int rotate(int bitFlag)
{
	int result = 0;
	// 시계 방향 회전
	for(int idxCol = 0; idxCol < blockSize; idxCol++)
	{
		for(int idxRow = 0; idxRow < blockSize; idxRow++)
		{
			if(bitFlag & (1 << (idxCol * blockSize + idxRow)))
				result |= (1 << (idxRow * blockSize + (blockSize - 1 - idxCol)));
		}
	}

	return result;
}

int mirror(int bitFlag)
{
	int result = 0;

	for(int idxCol = 0; idxCol < blockSize; idxCol++)
	{
		for(int idxRow = 0; idxRow < blockSize; idxRow++)
		{
			if(bitFlag & (1 << (idxCol * blockSize + idxRow)))
				result |= (1 << (idxCol * blockSize + (blockSize - 1 - idxRow)));
		}
	}

	return result;
}

void addCache(int bitFlag, int value)
{
	int calBitFlag = bitFlag;

	for(int idx = 0; idx < 4; idx++)
	{
		cache[calBitFlag] = value;
		calBitFlag = rotate(calBitFlag);
	}

	calBitFlag = mirror(bitFlag);

	for(int idx = 0; idx < 4; idx++)
	{
		cache[calBitFlag] = value;
		calBitFlag = rotate(calBitFlag);
	}
}

bool findWin(vector<vector<bool>> &block, vector<vector<pair<int, int>>> &pieces, int bitFlag, int depth = 0)
{
	int availCount = 0;

	if(cache[bitFlag] != -1)
	{
		return (cache[bitFlag] == 1);
	}

	for(int idxCol = 0; idxCol < blockSize; idxCol++)
	{
		for(int idxRow = 0; idxRow < blockSize; idxRow++)
		{
			for(int idxPiece = 0; idxPiece < pieces.size(); idxPiece++)
			{
				int addFlag = available(block, pieces[idxPiece], idxCol, idxRow);
				if(addFlag > 0)
				{
					setPiece(block, pieces[idxPiece], idxCol, idxRow, true);
					bool result = findWin(block, pieces, bitFlag | addFlag, depth + 1);
					setPiece(block, pieces[idxPiece], idxCol, idxRow, false);
					if(result == false)
					{
						addCache(bitFlag, 1);
						return true;
					}
					availCount++;
				}
			}
		}
	}

	addCache(bitFlag, 0);
	return false;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	vector<vector<pair<int, int>>> pieces = makePieces();
	cache.assign((1 << 25), -1);

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		int bitFlag = 0;
		vector<vector<bool>> block(blockSize, vector<bool>(blockSize, false));
		string str;
		for(int idxCol = 0; idxCol < blockSize; idxCol++)
		{
			cin >> str;
			for(int idxRow = 0; idxRow < blockSize; idxRow++)
			{
				if(str[idxRow] == '#')
				{
					bitFlag |= (1 << (idxCol * blockSize + idxRow));
					block[idxCol][idxRow] = true;
				}
			}
		}

		bool win = findWin(block, pieces, bitFlag);
		cout << (win ? "WINNING" : "LOSING") << endl;
	}

	return 0;
}

/*
3
.....
.##..
##..#
#.###
..#..
.....
.....
.....
.....
.....
#..##
##.##
##.##
#...#
##.##
*/