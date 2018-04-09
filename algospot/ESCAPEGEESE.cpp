#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int mod = 1000000007;


// table[t][a][b] : 0부터 t까지를 a개 포함, n으로 나눈 나머지가 b인 경우의 수

int solve(int n, int k)
{
	int result = 0;
	vector<vector<vector<int>>> table(n, vector<vector<int>>(0));

	table[0].assign(k + 1, vector<int>(n, 0));
	table[0][0][0] = 1;
	table[0][1][0] = 1;

	for(int t = 0; t < n - 1; t++)
	{
		table[t + 1] = table[t];

		for(int a = 0; a < k; a++)
		{
			for(int b = 0; b < n; b++)
			{
				if(table[t][a][b] > 0)
				{
					int next = (b + t + 1) % n;
					table[t + 1][a + 1][next] += table[t][a][b];
					table[t + 1][a + 1][next] %= mod;
				}
			}
		}

		table[t].clear();
	}

	result = table[n - 1][k][0];

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, k;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> k;
		cout << solve(n, k) << endl;
	}

	return 0;
}
