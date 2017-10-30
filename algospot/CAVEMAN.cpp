#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>


#define REP(i,a,b) for(int i = a; i < b; i++)
#define FOR(i,n) REP(i,0,n)

using namespace std;

int solve(vector<pair<int, int>> &ranges)
{
	int result = 0;
	int pos = 0;
	int rangeIdx = 0;
	priority_queue<int> que;

	sort(ranges.begin(), ranges.end());

	while(pos < (int)ranges.size())
	{
		while(rangeIdx < (int)ranges.size() && ranges[rangeIdx].first <= pos)
			que.push(ranges[rangeIdx++].second);
		pos = que.top() + 1;
		que.pop();
		result++;
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
		vector<pair<int, int>> ranges;
		cin >> n;
		for(int ani = 0; ani < n; ani++)
		{
			int c;
			cin >> c;
			ranges.push_back(make_pair(ani - c + 1, ani + c - 1));
		}

		cout << solve(ranges) << endl;
	}

	return 0;
}
