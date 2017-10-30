#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

map<vector<int>, int> cache;


vector<int> ratings(vector<int> &nums)
{
	int n = nums.size();
	vector<int> result(n);

	for(int idxA = 0; idxA < n; idxA++)
	{
		for(int idxB = 0; idxB < n; idxB++)
		{
			if(nums[idxA] > nums[idxB])
				result[idxA]++;
		}
	}

	return result;
}

void preCache(int n)
{
	vector<int> completes;
	queue<pair<vector<int>, int>> que;

	for(int idx = 0; idx < n ; idx++)
		completes.push_back(idx);

	cache.insert(make_pair(completes, 0));
	que.push(make_pair(completes, 0));

	while(que.empty() == false)
	{
		pair<vector<int>, int> cur = que.front();
		que.pop();

		for(int idxA = 0; idxA < n - 1; idxA++)
		{
			for(int idxB = idxA + 1; idxB < n; idxB++)
			{
				reverse(cur.first.begin() + idxA, cur.first.begin() + idxB + 1);
				if(cache.find(cur.first) == cache.end())
				{
					cache.insert(make_pair(cur.first, cur.second + 1));
					que.push(make_pair(cur.first, cur.second + 1));
				}
				reverse(cur.first.begin() + idxA, cur.first.begin() + idxB + 1);
			}
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	cin >> tc;

	for(int i = 1; i <= 8; i++)
		preCache(i);

	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> nums;
		vector<int> completes;
		cin >> n;
		nums.assign(n, 0);

		for(int idx = 0; idx < n ; idx++)
			cin >> nums[idx];
		cout << cache.find(ratings(nums))->second << endl;
	}

	return 0;
}
