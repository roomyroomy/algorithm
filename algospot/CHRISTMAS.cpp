#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long llong;

const int modNum = 20091101;

int solve1(vector<int> &doll, int k)
{
	int result = 0;
	llong acc = 0;
	vector<int> mods(k, 0);

	for(int idx = 0; idx < doll.size(); idx++)
	{
		mods[doll[idx]]++;
	}

	for(int idx = 0; idx < mods.size(); idx++)
	{
		llong num = (llong)mods[idx];
		if(num >= 2)
		{
			result += (int)((num * (num - 1) / 2) % (llong)modNum);
			result %= modNum;
		}
	}

	return result % modNum;
}

int solve2(vector<int> &doll, int k)
{
	vector<int> mods(k, -1);
	vector<int> table(doll.size(), 0);

	mods[doll[0]] = 0;
	for(int idx = 1; idx < doll.size(); idx++)
	{
		int prevIdx = mods[doll[idx]];

		table[idx] = table[idx - 1];
		if(mods[doll[idx]] != -1)
		{
			table[idx] = max(table[idx], table[prevIdx] + 1);
		}
		mods[doll[idx]] = idx;
	}

	return table[table.size() - 1];
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, k;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> doll;
		int acc = 0;
		cin >> n >> k;

		doll.push_back(0);
		for(int idx = 0; idx < n; idx++)
		{
			int d;
			cin >> d;

			acc += d;
			acc = acc % k;
			doll.push_back(acc);
		}
		cout << solve1(doll, k) << " " << solve2(doll, k)  << endl;
	}

	return 0;
}

/*
3
6 4
1 2 3 4 5 6
2 2
1 1
4 2
2 2 2 2
*/
