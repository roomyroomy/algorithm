#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;

vector<int> solve(vector<vector<int>> &game)
{
	vector<int> result;
	vector<bool> winner(game.size(), false);
	int lastPerson = -1;

	for(int t = 0; t < game[0].size(); t++)
	{
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

		for(int p = 0; p < game.size(); p++)
		{
			if(winner[p] == false)
			{
				pq.push(make_pair(game[p][t], p));
			}
		}

		if(pq.size() > 0)
		{
			int top = pq.top().first;
			while(pq.empty() == false && pq.top().first == top)
			{
				pair<int, int> cur = pq.top();
				pq.pop();
				winner[cur.second] = true;
				result.push_back(cur.second);
				lastPerson = cur.second;
			}
			if(result.size() > 1)
				break;
			else
				result.clear();
		}
		else
		{
			result.push_back(lastPerson);
			break;
		}
	}

	if(result.size() == 0)
	{
		for(int p = 0; p < game.size(); p++)
		{
			if(winner[p] == false)
				result.push_back(p);
		}
	}

	sort(result.begin(), result.end());
	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, k;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<int>> game;
		cin >> n >> k;
		game.assign(n, vector<int>(k, 0));
		for(int p = 0; p < n; p++)
		{
			for(int t = 0; t < k; t++)
			{
				cin >> game[p][t];
			}
		}

		vector<int> result = solve(game);
		for(int idx = 0; idx < result.size(); idx++)
		{
			cout << result[idx] + 1 << " ";
		}
		cout << endl;
	}

	return 0;
}

/*
3
4 3
0 1 3
7 0 1
5 1 3
1 2 3
3 2
1 1
1 2
1 3
5 3
0 1 2
2 0 1
1 2 0
1 2 3
1 1 1
*/
