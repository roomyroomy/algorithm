#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

typedef unsigned int uint;

vector<vector<uint>> makeSumTable(vector<vector<uint>> &grid)
{
	int r = grid.size();
	int c = grid[0].size();
	vector<vector<uint>> table(r, vector<uint>(c, 0));

	for(int row = 0; row < r; row++)
	{
		for(int col = 0; col < c; col++)
		{
			if(row > 0)
				table[row][col] += table[row - 1][col];
			if(col > 0)
				table[row][col] += table[row][col - 1];
			if(row > 0 && col > 0)
				table[row][col] -= table[row - 1][col - 1];
			table[row][col] += grid[row][col];
		}
	}

	return table;
}

uint rangeSum(vector<vector<uint>> &table, int sRow, int sCol, int eRow, int eCol)
{
	int result = 0;
	result += table[eRow][eCol];
	if(sRow > 0 && sCol > 0)
		result += table[sRow - 1][sCol - 1];
	if(sRow > 0)
		result -= table[sRow - 1][eCol];
	if(sCol > 0)
		result -= table[eRow][sCol - 1];
	return result;
}

uint solve2(vector<vector<uint>> &grid, vector<vector<uint>> &table, uint m)
{
	int r = grid.size();
	int c = grid[0].size();
	uint result = 0;

	for(int sRow = 0; sRow < r; sRow++)
	{
		for(int sCol = 0; sCol < c; sCol++)
		{
			for(int eRow = sRow; eRow < r; eRow++)
			{
				for(int eCol = sCol; eCol < c; eCol++)
				{
					uint range = rangeSum(table, sRow, sCol, eRow, eCol);
					if(range % m == 0 && range > result)
						result = range;
				}
			}
		}
	}

	return result;
}

uint solve(vector<vector<uint>> &grid, vector<vector<uint>> &table, uint m)
{
	int r = grid.size();
	int c = grid[0].size();
	uint result = 0;

	for(int sCol = 0; sCol < c; sCol++)
	{
		for(int eCol = sCol; eCol < c; eCol++)
		{
			vector<int> accRow;
			vector<pair<uint, int>> modTable;

			accRow.push_back(0);
			for(int row = 0; row < r; row++)
			{
				uint range = rangeSum(table, row, sCol, row, eCol);
				accRow.push_back(range + accRow.back());
			}

			for(int idx = 0; idx < accRow.size(); idx++)
			{
				modTable.push_back(make_pair(accRow[idx] % m, idx));
			}
			sort(modTable.begin(), modTable.end());

			int lower = 0, upper = 0;
			for(int row = 0; row < modTable.size(); row++)
			{
				if(row == modTable.size() - 1 || modTable[row].first != modTable[row + 1].first)
				{
					upper = row;
					uint range = 0;
					range = accRow[modTable[upper].second];
					range -= accRow[modTable[lower].second];
					if(range % m == 0 && upper != lower)
						result = max(result, range);
					lower = upper = row + 1;
				}
			}
		}
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, r, c;
	uint m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<uint>> grid;
		vector<vector<uint>> table;
		cin >> r >> c >> m;

		grid.assign(r, vector<uint>(c, 0));
		for(int row = 0; row < r; row++)
		{
			for(int col = 0; col < c; col++)
			{
				cin >> grid[row][col];
			}
		}

		table = makeSumTable(grid);
		int result = solve(grid, table, m);
		cout << result << endl;
	}

	return 0;
}
