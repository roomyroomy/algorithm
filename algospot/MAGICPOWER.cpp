#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int solve(priority_queue<int> items, int m)
{
	int result = 0;

	for(int idx = 0; idx < m; idx++)
	{
		int t = items.top();
		items.pop();

		result += t;

		if(t - 1 > 0)
			items.push(t - 1);

		if(items.empty() == true)
			break;
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
		priority_queue<int> items;
		cin >> n >> m;
		for(int idx = 0; idx < n; idx++)
		{
			int a;
			cin >> a;
			items.push(a);
		}

		cout << solve(items, m) << endl;
	}

	return 0;
}
