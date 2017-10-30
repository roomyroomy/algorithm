/*
1. �̺� �׷����� matching�� ���� ���� ���Ѵ�.
2. �켱, �Ʒ� ��Ģ���� �̺� �׷����� �����.
 1) ü���ǿ� �������� ���ϴ����� ���ϴ� �缱��, ���ϴ����� ���ϴ� �缱�� ��ֹ��� �ִ� ������ �ߴ´�.
 2) �缱�� ������ id�� �ο��Ѵ�. ��ֹ��� ���� ������ ���� ��Ȯ�ϰ� �ΰ��� �缱�� ������.
 3) �� ������ �ο��� �� ������ �缱�� graph�� edge�� �߰��Ѵ�.
3. �̺� �׷����� ���� �ִ� ��Ī ���� ���Ѵ�.
 1) �ִ� ��Ī ���� ��� ��忡 ���� DFS�� �ݺ����� ���� �� �ִ�.
 2) �� ���� : http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220807541506
4. �� ������ �Ʒ��� ���� ������, �̺� �׷����� Ǯ �� �ִ�.
 1) ����� �ڱ� �ڽ��� �����ϴ� �� ���� �缱�� ������ �ش�.
 2) �ϳ��� ������ ������ ����� ���� �Ǹ�, �� ���� �缱�󿡴� �� �ٸ� ����� ������ �� ����.
 3) ����, �ִ�� ������ ����� ������ ���� ���Ͽ�, �缱 �ΰ��� �����ϴ� �ִ����� ��� ������ �˾Ƴ���, ���� ���� �� �ִ�.
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