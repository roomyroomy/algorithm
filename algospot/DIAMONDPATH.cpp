#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

int solve(vector<vector<int>> &path, int n)
{
	int result = 0;
	vector<vector<int>> maximum(path.size(), vector<int>(path[0].size(), 0));

	maximum[0][0] = path[0][0];

	for(int row = 1; row < n * 2 - 1; row++)
	{
		int bound = 0;
		if(row < n)
			bound = row + 1;
		else
			bound = (n * 2 - 1) - row;

		for(int col = 0; col < bound; col++)
		{
			if(row < n)
				maximum[row][col] = max(maximum[row - 1][col], col > 0 ? maximum[row - 1][col - 1] : 0) + path[row][col];
			else
				maximum[row][col] = max(maximum[row - 1][col], maximum[row - 1][col + 1]) + path[row][col];

			if(row == n * 2 - 2)
				result = max(result, maximum[row][col]);
		}
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<int>> path;
		cin >> n;
		path.assign(n * 2 - 1, vector<int>(n, 0));

		for(int row = 0; row < n * 2 - 1; row++)
		{
			int bound = 0;
			if(row < n)
				bound = row + 1;
			else
				bound = (n * 2 - 1) - row;

			for(int col = 0; col < bound; col++)
			{
				cin >> path[row][col];
			}
		}

		cout << solve(path, n) << endl;
	}

	return 0;
}
