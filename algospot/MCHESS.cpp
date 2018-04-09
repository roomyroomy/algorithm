#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int INF = 2100000000;

class Move
{
public:
	pair<int, int> pos;
	int dist;
	int state;

	Move(pair<int, int> _pos, int _state, int _dist): pos(_pos), dist(_dist), state(_state)
	{
	}

	Move(int posR, int posC, int _state, int _dist): dist(_dist), state(_state)
	{
		pos = make_pair(posR, posC);
	}

	Move()
	{
	}
};


queue<Move> findNext(int r, int c, Move cur)
{
	queue<Move> q;
	if(cur.state == 1)
	{
		if(cur.pos.second - 1 >= 0)
		{
			Move next(cur.pos.first, cur.pos.second - 1, cur.state, cur.dist + 1);
			q.push(next);
		}
	}
	if(cur.state == 2 || cur.state == 5)
	{
		pair<int, int> pos = cur.pos;
		while(pos.first >= 0 && pos.second >= 0)
		{
			Move next(pos, cur.state, cur.dist + 1);
			pos.first--;
			pos.second--;
			q.push(next);
		}
		pos = cur.pos;
		while(pos.first >= 0 && pos.second < c)
		{
			Move next(pos, cur.state, cur.dist + 1);
			pos.first--;
			pos.second++;
			q.push(next);
		}
		pos = cur.pos;
		while(pos.first < r && pos.second >= 0)
		{
			Move next(pos, cur.state, cur.dist + 1);
			pos.first++;
			pos.second--;
			q.push(next);
		}
		pos = cur.pos;
		while(pos.first < r && pos.second < c)
		{
			Move next(pos, cur.state, cur.dist + 1);
			pos.first++;
			pos.second++;
			q.push(next);
		}
	}
	if(cur.state == 3)
	{
		int arr[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
		for(int i = 0; i < 8; i++)
		{
			Move next(cur.pos.first + arr[i][0], cur.pos.second + arr[i][1], cur.state, cur.dist + 1);
			if(next.pos.first >= 0 && next.pos.first < r && next.pos.second >= 0 && next.pos.second < c)
				q.push(next);
		}
	}
	if(cur.state == 4 || cur.state == 5)
	{
		for(int row = 0; row < r; row++)
		{
			Move next(row, cur.pos.second, cur.state, cur.dist + 1);
			if(next.pos.first != cur.pos.first)
				q.push(next);
		}
		for(int col = 0; col < c; col++)
		{
			Move next(cur.pos.first, col, cur.state, cur.dist + 1);
			if(next.pos.second != cur.pos.second)
				q.push(next);
		}
	}
	if(cur.state == 6)
	{
		int arr[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
		for(int i = 0; i < 8; i++)
		{
			Move next(cur.pos.first + arr[i][0], cur.pos.second + arr[i][1], cur.state, cur.dist + 1);
			if(next.pos.first >= 0 && next.pos.first < r && next.pos.second >= 0 && next.pos.second < c)
				q.push(next);
		}
	}
	return q;
}

int solve(pair<int, int> start, pair<int, int> end, vector<vector<int>> &chess)
{
	int r = chess.size(), c = chess[0].size();
	int result = 0;
	vector<vector<vector<int>>> table(r, vector<vector<int>>(c, vector<int>(7, -1)));
	queue<Move> q;

	q.push(Move(start, 6, 0));
	table[start.first][start.second][6] = 0;

	while(q.empty() == false)
	{
		Move m = q.front();
		q.pop();

		queue<Move> newer1 = findNext(r, c, m);
		while(newer1.empty() == false)
		{
			Move cur = newer1.front();
			int tValue = table[cur.pos.first][cur.pos.second][cur.state];
			newer1.pop();
			if(tValue == -1 || tValue > cur.dist)
			{
				table[cur.pos.first][cur.pos.second][cur.state] = cur.dist;
				q.push(cur);
				if(cur.pos.first == end.first && cur.pos.second == end.second)
					return cur.dist;
			}
		}
		
		if(chess[m.pos.first][m.pos.second] != 0 && chess[m.pos.first][m.pos.second] != m.state)
		{
			m.state = chess[m.pos.first][m.pos.second];
			queue<Move> newer2 = findNext(r, c, m);

			while(newer2.empty() == false)
			{
				Move cur = newer2.front();
				int tValue = table[cur.pos.first][cur.pos.second][cur.state];
				newer2.pop();
				if(tValue == -1 || tValue > cur.dist)
				{
					table[cur.pos.first][cur.pos.second][cur.state] = cur.dist;
					q.push(cur);
					if(cur.pos.first == end.first && cur.pos.second == end.second)
						return cur.dist;
				}
			}
		}
	}

	result = INF;
	for(int i = 1; i < 7; i++)
		if(table[end.first][end.second][i] != -1)
			result = min(result, table[end.first][end.second][i]);

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;
	pair<int, int> start, end;
	string str;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<int>> chess;
		cin >> n;
		cin >> start.first >> start.second >> end.first >> end.second;
		start.first--; start.second--; end.first--; end.second--;
		chess.assign(n, vector<int>(n, 0));
		for(int row = 0; row < n; row++)
		{
			cin >> str;
			for(int col = 0; col < str.size(); col++)
			{
				if(str[col] == '.')
					chess[n - row - 1][col] = 0;
				else if(str[col] == 'P')
					chess[n - row - 1][col] = 1;
				else if(str[col] == 'B')
					chess[n - row - 1][col] = 2;
				else if(str[col] == 'N')
					chess[n - row - 1][col] = 3;
				else if(str[col] == 'R')
					chess[n - row - 1][col] = 4;
				else if(str[col] == 'Q')
					chess[n - row - 1][col] = 5;
				else if(str[col] == 'K')
					chess[n - row - 1][col] = 6;
			}
		}
		cout << solve(start, end, chess) << endl;
	}

	return 0;
}
