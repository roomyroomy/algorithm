/*
1. 이분 그래프의 matching을 통해 답을 구한다.
2. 우선, 아래 규칙으로 이분 그래프를 만든다.
 1) 체스판에 가상으로 좌하단으로 향하는 사선과, 우하단으로 향하는 사선을 장애물이 있는 곳까지 긋는다.
 2) 사선에 가상의 id를 부여한다. 장애물이 없는 지점은 각각 정확하게 두개의 사선을 가진다.
 3) 각 지점에 부여된 두 가지의 사선을 graph에 edge로 추가한다.
3. 이분 그래프에 대한 최대 매칭 값을 구한다.
 1) 최대 매칭 값은 모든 노드에 대한 DFS의 반복으로 구할 수 있다.
 2) 상세 내용 : http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220807541506
4. 본 문제는 아래와 같은 이유로, 이분 그래프로 풀 수 있다.
 1) 비솝은 자기 자신이 존재하는 두 가지 사선에 영향을 준다.
 2) 하나의 지점에 존재할 비솝이 선택 되면, 두 가지 사선상에는 또 다른 비솝이 존재할 수 없다.
 3) 따라서, 최대로 존재할 비솝의 개수를 세기 위하여, 사선 두개를 연결하는 최대한의 비솝 개수를 알아내면, 답을 구할 수 있다.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum cell {EMPTY = -1, BLOCK = 999999};

inline bool isInRect(int row, int col, int n)
{
	if(row >= 0 && row < n && col >= 0 && col < n)
		return true;
	else
		return false;
}

void addLine(vector<vector<pair<int, int>>> &chess, int startRow, int startCol, int direction, int id)
{
	int n = chess.size();
	pair<int, int> arrow;
	if(direction == 0)
		arrow = make_pair(1, -1);
	else
		arrow = make_pair(1, 1);

	int currentRow = startRow, currentCol = startCol;
	
	while(true)
	{
		if(direction == 0)
			chess[currentRow][currentCol].first = id;
		else
			chess[currentRow][currentCol].second = id;
		currentRow += arrow.first;
		currentCol += arrow.second;

		if(isInRect(currentRow, currentCol, n) == false)
			break;
		else if(chess[currentRow][currentCol].first == BLOCK)
			break;
	}
}

vector<vector<int>> convertGraph(vector<vector<pair<int, int>>> &chess)
{
	int n = chess.size();
	int id = 0;
	vector<vector<int>> resultGraph;

	for(int idxRow = 0; idxRow < n; idxRow++)
	{
		for(int idxCol = 0; idxCol < n; idxCol++)
		{
			if(chess[idxRow][idxCol].first == EMPTY)
				addLine(chess, idxRow, idxCol, 0, id++);
			if(chess[idxRow][idxCol].second == EMPTY)
				addLine(chess, idxRow, idxCol, 1, id++);
		}
	}

	resultGraph.assign(id, vector<int>(0));

	for(int idxRow = 0; idxRow < n; idxRow++)
	{
		for(int idxCol = 0; idxCol < n; idxCol++)
		{
			int u = chess[idxRow][idxCol].first;
			int v = chess[idxRow][idxCol].second;
			if(u != BLOCK && v != BLOCK)
			{
				resultGraph[u].push_back(v);
				resultGraph[v].push_back(u);
			}
		}
	}

	return resultGraph;
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

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<pair<int, int>>> chess;
		cin >> n;
		chess.assign(n, vector<pair<int, int>>(0));
		for(int idxRow = 0; idxRow < n; idxRow++)
		{
			string str;
			cin >> str;
			const char *s = str.c_str();
			for(int idxCol = 0; idxCol < n; idxCol++)
			{
				if(s[idxCol] == '.')
					chess[idxRow].push_back(make_pair(EMPTY, EMPTY));
				else
					chess[idxRow].push_back(make_pair(BLOCK, BLOCK));
			}
		}

		vector<vector<int>> graph = convertGraph(chess);

		cout << bipatiteMatching(graph) << endl;
	}

	return 0;
}

/*
3
5
.....
.....
.....
.....
.....
8
..**.*.*
**.***.*
*.**...*
.*.**.**
*.**.*.*
..**.*.*
...*.*.*
**.*.*.*
8
*.*.*.*.
.*.*.*.*
*.*.*.*.
.*.*.*.*
*.*.*.*.
.*.*.*.*
*.*.*.*.
.*.*.*.*
*/