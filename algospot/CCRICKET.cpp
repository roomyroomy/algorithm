/*
1. P_1 * 2 <= P_2 이면, 무조건 모두 P_1으로 채우는 것이 정답
2. P_1 * 2 > P_2 일 경우, 가급적 P_2를 최대화 하는 것이 정답. 아래와 같이 구한다.
  1) 격자를 상하좌우 중 도달 가능한 부분에 대하여 graph로 구성
  2) 해당 graph에 대하여 최대 matching을 만족하는 값을 구한다.
  3) 최대 matching 값이 P_2 값, 나머지는 P_1을 채우도록 하여 결과값을 계산한다.
3. 시간 복잡도는 O(N^4)
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int INFINITY_INT = 2100000000;

void connectNodes(vector<vector<int>> &graph, int u, int v)
{
	vector<int>::iterator it;

	it = graph[u].begin();
	while(it != graph[u].end() && *it != v)	it++;
	if(it == graph[u].end())
		graph[u].push_back(v);

	it = graph[v].begin();
	while(it != graph[v].end() && *it != u)	it++;
	if(it == graph[v].end())
		graph[v].push_back(u);
}

bool dfs(int now, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &backMatch)
{
    if (visited[now])
		return false;
    visited[now] = true;

    for(int idxNode = 0; idxNode < graph[now].size(); idxNode++)
	{
        int next = graph[now][idxNode];
        if(backMatch[next] == -1 || dfs(backMatch[next], graph, visited, backMatch))
		{
            backMatch[next] = now;
            return true;
        }
    }

    return false;
}

int bipatiteMatching(vector<vector<int>> &graph)
{
	vector<int> backMatch(graph.size(), -1);
    int matched = 0;
    for (int idxNode = 0; idxNode < graph.size() ; idxNode++)
	{
		vector<bool> visited(graph.size(), false);
        if(dfs(idxNode, graph, visited, backMatch))
			matched++;
    }

    return matched / 2;
}

vector<vector<int>> convertGraph(vector<vector<bool>> &grid, int row, int col)
{
	vector<vector<int>> resultGraph(col * row);

	for(int idxRow = 0; idxRow < row; idxRow++)
	{
		for(int idxCol = 0; idxCol < col; idxCol++)
		{
			if(idxRow > 0)
			{
				int u = idxRow * col + idxCol;
				int v = (idxRow - 1) * col + idxCol;
				if(grid[idxRow][idxCol] == false && grid[idxRow - 1][idxCol] == false)
					connectNodes(resultGraph, u, v);
			}

			if(idxCol > 0)
			{
				int u = idxRow * col + idxCol;
				int v = idxRow * col + (idxCol - 1);
				if(grid[idxRow][idxCol] == false && grid[idxRow][idxCol - 1] == false)
					connectNodes(resultGraph, u, v);
			}
		}
	}

	return resultGraph;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int t, n, m, p1, p2;

	cin >> t;
	for(int idxCase = 0; idxCase < t; idxCase++)
	{
		int emptyTileCount = 0;
		vector<vector<bool>> tileGrid;
		cin >> n >> m >> p1 >> p2;

		for(int idxRow = 0; idxRow < n; idxRow++)
		{
			string strLine;
			cin >> strLine;
			const char *str = strLine.c_str();

			tileGrid.push_back(vector<bool>(0));
			for(int idxCol = 0; idxCol < m; idxCol++)
			{
				if(str[idxCol] == '1')
				{
					tileGrid.back().push_back(true);
				}
				else
				{
					tileGrid.back().push_back(false);
					emptyTileCount++;
				}
			}
		}
		
		if(p1 * 2 < p2)
		{
			cout << emptyTileCount * p1 << endl;
		}
		else
		{
			vector<vector<int>> graph = convertGraph(tileGrid, n, m);
			int matching = bipatiteMatching(graph);
			int result = p2 * matching + p1 * (emptyTileCount - matching * 2);
			cout << result << endl;
		}
	}

	return 0;
}

/*
4
3 4 5 8
0100
0101
0000
3 4 7 10
0000
0000
0000
4 3 2 3
101
010
101
010
3 4 30 40
0100
0101
0000
*/