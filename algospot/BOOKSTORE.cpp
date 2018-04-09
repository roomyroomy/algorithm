#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int solve(vector<vector<pair<int, int>>> pros)
{
	int result = 0, m = pros.size(), n = pros[0].size();

	for(int s = 0; s < m; s++)
	{
		int curPrice = 0, curPoint = 0;
		sort(pros[s].begin(), pros[s].end());
		for(int b = 0; b < n; b++)
		{
			int price = -pros[s][b].second, point = -pros[s][b].first;
			int use = min(price, curPoint);
			curPrice += price - use;
			curPoint += point;
			curPoint -= use;
		}

		if(s == 0 || curPrice < result)
			result = curPrice;
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<pair<int, int>>> pros;
		cin >> n >> m;

		pros.assign(m, vector<pair<int, int>>(n, make_pair(0, 0)));
		for(int	b = 0; b < n; b++)
		{
			for(int s = 0; s < m; s++)
			{
				cin >> pros[s][b].second >> pros[s][b].first;
				pros[s][b].second *= -1;
				pros[s][b].first *= -1;
			}
		}
		cout << solve(pros) << endl;
	}

	return 0;
}
