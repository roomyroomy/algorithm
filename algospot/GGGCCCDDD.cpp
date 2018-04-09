#include <iostream>
#include <algorithm>
#include <vector>
#include <map>


using namespace std;

const int mod = 1000000007;
typedef long long llong;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int solve(int n, int m)
{
	int sum = 0;
	vector<vector<int>> table(m, vector<int>());
	vector<vector<int>> gcdCount(n + 1, vector<int>(n + 1, 0));
	vector<vector<pair<int, int>>> gcdList(n + 1, vector<pair<int, int>>());

	table[1].assign(n + 1, 0);
	for (int a = 1; a <= n; a++)
	{
		for (int b = 1; b <= n; b++)
		{
			int g = gcd(a, b);
			table[1][g]++;
			gcdCount[a][g]++;
		}
	}

	for (int a = 1; a <= n; a++)
	{
		for (int g = 1; g <= n; g++)
		{
			if(gcdCount[a][g] > 0)
			{
				gcdList[a].push_back(make_pair(g, gcdCount[a][g]));
			}
		}
	}
	
	for(int a = 1; a < m - 1; a++)
	{
		table[a + 1].assign(n + 1, 0);
		for(int k = 1; k <= n; k++)
		{
			for(int p = 0; p < gcdList[k].size(); p++)
			{
				pair<int, int> cur = gcdList[k][p];
				llong value = (llong)cur.second * (llong)table[a][k];
				value %= (llong)mod;
				table[a + 1][cur.first] += (int)value;
				table[a + 1][cur.first] %= mod;
			}
		}
		table[a].clear();
	}

	for(int c = 1; c <= n; c++)
	{
		llong k = (llong)c * (llong)table[m - 1][c];
		k %= (llong)mod;
		sum += (int)k;
		sum %= mod;
	}
	
	return sum;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> m;
		cout << solve(n, m) << endl;
	}

	return 0;
}
