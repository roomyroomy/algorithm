#include <iostream>
#include <algorithm>
#include <vector>


#define REP(i,a,b) for(int i = a; i < b; i++)
#define FOR(i,n) REP(i,0,n)

using namespace std;

int solve(vector<pair<int, int>> &candles)
{
	int result = 0;

	for(int s = 0; s < candles.size(); s++)
	{
		int minBound = candles[s].first;
		int maxBound = candles[s].second;

		for(int e = s; e < candles.size(); e++)
		{
			if(minBound < candles[e].first)
				minBound = candles[e].first;
			if(maxBound > candles[e].second)
				maxBound = candles[e].second;
			if(result < (maxBound - minBound) * (e - s + 1))
				result = (maxBound - minBound) * (e - s + 1);
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
		vector<pair<int, int>> candles;
		cin >> n;
		for(int idx = 0; idx < n; idx++)
		{
			int a, b;
			cin >> a >> b;
			candles.push_back(make_pair(a, b));
		}

		cout << solve(candles) << endl;
	}

	return 0;
}
