/*
1. DS(Dominated Set)을 구하는 문제
2. Graph에서의 DS는 NP-Complete이다.
3. 하지만, 문제에서 주어진 Graph는 Tree 형태이므로, 아래 특성을 이용하여 DFS/BFS로 풀 수 있다.
  1) leaf node와 연결된 node는 반드시 DS에 포함되어야 한다.
  2) Dominated Set에 의해 지배받는 node를 제거하면, 또 다른 Tree의 집합이 구성된다. 이 Tree 또한 동일한 특성을 가진다.
4. 따라서, DFS/BFS를 통해 탐색을 하면서 non-leaf node에 연결된 node를 찾아 나가면서 답을 구한다.
5. 단, leaf node로만 tree가 구성될 수 있으므로, 이 경우에는 별도로 계산한다.
*/

#include <iostream>
#include <vector>

using namespace std;

const int NOT_VISITED = 0;
const int VISITED = 1;
const int DOMINATED = 2;

int lightCount = 0;

void addDominated(vector<vector<int>> &graph, vector<int> &visited, int here)
{
	int length = graph[here].size();

	visited[here] = DOMINATED;
	for(int idxEdge = 0; idxEdge < length; idxEdge++)
	{
		int there = graph[here][idxEdge];
		visited[there] = DOMINATED;
	}
	lightCount++;
}

void dfs(vector<vector<int>> &graph, vector<int> &visited, int here)
{
	int length = graph[here].size();
	bool needLighten = false;

	visited[here] = VISITED;

	for(int idxEdge = 0; idxEdge < length; idxEdge++)
	{
		int there = graph[here][idxEdge];
		if(visited[there] == NOT_VISITED)
		{
			dfs(graph, visited, there);
			if(visited[there] == VISITED)
				needLighten = true;
		}
	}

	if(needLighten == true)
	{
		addDominated(graph, visited, here);
	}
}

int solve(vector<vector<int>> &graph)
{
	int graphSize = graph.size();
	vector<int> visited(graphSize, NOT_VISITED);

	lightCount = 0;

	for(int idxNode = 0; idxNode < graphSize; idxNode++)
	{
		if(visited[idxNode] == NOT_VISITED && graph[idxNode].size() > 1)
		{
			dfs(graph, visited, idxNode);
		}
	}

	for(int idxNode = 0; idxNode < graphSize; idxNode++)
	{
		if(visited[idxNode] == VISITED || visited[idxNode] == NOT_VISITED)
		{
			addDominated(graph, visited, idxNode);
		}
	}

	return lightCount;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, g, h, a, b;

	cin >> tc;

	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<int>> graph;
		cin >> g >> h;

		graph.assign(g, vector<int>(0));

		for(int idxWay = 0; idxWay < h; idxWay++)
		{
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		cout << solve(graph) << endl;
	}

	return 0;
}


/*
5
6 5
0 1
1 2
1 3
2 5
0 4
4 2
0 1
2 3
1000 1
0 1
8 7
0 3
1 3
2 3
3 4
4 5
4 6
4 7
10 9
0 3
1 3
2 3
3 8
8 4
4 5
4 6
4 7
8 9
*/