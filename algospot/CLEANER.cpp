#include <iostream>
#include <vector>

const int mod = 1000000007;

using namespace std;

int arrow[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int cleaner(vector<vector<int>> &position, int current, int c, int r)
{
	int backupValue = position[c][r];
	int n = position.size();
	int m = position[0].size();
	int result = 0;

	if(position[c][r] >= 0 && position[c][r] != current)
		return 0;
	else if(current == 0)
		return 1;

	position[c][r] = current;

	for(int idx = 0 ;idx < 4; idx++)
	{
		int newC = c + arrow[idx][0];
		int newR = r + arrow[idx][1];
		if(newC >= 0 && newC < n && newR >= 0 && newR < m) {
			result += cleaner(position, current - 1, newC, newR);
			result %= mod;
		}
	}

	position[c][r] = backupValue;
	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		int result = 0;
		vector<vector<int>> position;
		cin >> n >> m;

		position.assign(n, vector<int>(m, -1));

		for(int col = 0; col < n; col++)
		{
			for(int row = 0; row < m; row++)
			{
				int t;
				cin >> t;
				position[col][row] = t;
			}
		}

		cout << cleaner(position, n * m - 1, n - 1, m - 1) << endl;
	}

	return 0;
}
