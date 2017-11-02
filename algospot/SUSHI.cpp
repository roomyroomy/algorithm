#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int solve(vector<pair<int, int>> foods, int m)
{
	vector<int> result(m + 1, 0);
	
	for(int idx = 1; idx < m + 1; idx++)
	{
		result[idx] = result[idx - 1];
		for(int f = 0; f < foods.size(); f++)
		{
			int c = idx - foods[f].first;
			if(c >= 0)
			{
				int v = result[c] + foods[f].second;
				result[idx] = max(result[idx], v);
			}
		}
	}

	return result.back();
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<pair<int, int>> foods;
		cin >> n >> m;
		m /= 100;
		for(int idx = 0; idx < n; idx++)
		{
			int price, value;
			cin >> price >> value;
			price /= 100;
			foods.push_back(make_pair(price, value));
		}

		cout << solve(foods, m) << endl;
	}

	return 0;
}

/*
3
6 10000
2500 7
3000 9
4000 10
5000 12
10000 20
15000 1
6 543975612
2500 7
3000 9
4000 10
5000 12
10000 20
15000 1 
6 2147483647
2500 7
3000 9
4000 10
5000 12
10000 20
15000 1 
*/