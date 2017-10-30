#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>


using namespace std;


int gcd(int u, int v)
{
    int t;
    while (v)
	{
        t = u % v;
        u = v;
        v = t;
    }
    return u;
}

void print(vector<int> &list)
{
	int size = list.size();
	cout << size << endl;
	for(int idx = 0; idx < size; idx++)
		cout << list[idx] << endl;
}

bool isNonblockPath(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> end)
{
	int cx = abs(start.first - end.first);
	int cy = abs(start.second - end.second);
	int g = gcd(cx, cy);
	int dx = 0, dy = 0;

	if(g > 0)
	{
		dx = (start.first > end.first) ? -(cx / g) : (cx / g);
		dy = (start.second > end.second) ? -(cy / g) : (cy / g);
	}
	else
	{
		if(start.first == end.first)
			dy = 1;
		if(start.second == end.second)
			dx = 1;
	}


	start.first += dx;
	start.second += dy;

	while(start.first != end.first || start.second != end.second)
	{
		if(grid[start.first][start.second] > 0)
			return false;
		start.first += dx;
		start.second += dy;
	}

	return true;
}

vector<int> solve(int n, int m, int s)
{
	vector<int> result;
	vector<pair<int, int>> path(n * m + 1, make_pair(-1, -1));
	vector<vector<int>> grid(n, vector<int>(m, 0));

	for(int idxRow = 0; idxRow < n; idxRow++)
	{
		for(int idxCol = 0; idxCol < m; idxCol++)
		{
			int num;
			cin >> num;
			if(num > 0)
				path[num] = make_pair(idxRow, idxCol);
			grid[idxRow][idxCol] = num;
		}
	}

	for(int idxPath = s; idxPath < n * m + 1; idxPath++)
	{
		if(path[idxPath].first == -1 && path[idxPath].second == -1)
			break;

		int dx = abs(path[idxPath].first - path[idxPath - s + 1].first);
		int dy = abs(path[idxPath].second - path[idxPath - s + 1].second);

		if((dx == 1 || dy == 1)
			|| (isNonblockPath(grid, path[idxPath], path[idxPath - s + 1])))
			result.push_back(idxPath - s + 1);
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int n, m, s;

	cin >> n >> m >> s;
	vector<int> result = solve(n, m, s);
	print(result);

	return 0;
}

/*
Example 1
3 4 6
1 2 3 0
0 5 4 0
0 6 7 8

Example 2
3 4 7
1 2 3 0
0 5 4 0
0 6 7 8

Example 3
3 4 5
1 8 9 10
2 7 6 11
3 4 5 12

Example 4
5 3 5
1 2 3
0 0 4
7 6 5
8 0 0
9 10 11

9 9 2
0 0 0 0 4 0 0 0 0
0 0 0 3 0 0 0 0 0
0 0 2 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0

*/