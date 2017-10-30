#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;

const int INFINITY_INT = 2100000000;

void shortestPath(vector<vector<int>> &graph, int startNode, int endNode, vector<int> &pathLength)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> bfsQueue;	// first: 최단 경로 길이, second: 노드 번호
	int graphSize = graph.size();

	pathLength.assign(graphSize, INFINITY_INT);

	bfsQueue.push(make_pair(0, startNode));
	pathLength[startNode] = 0;

	while(bfsQueue.empty() == false)
	{
		pair<int, int> currentNodePair = bfsQueue.top();
		bfsQueue.pop();

		if(currentNodePair.first > pathLength[currentNodePair.second])
			continue;

		int currentNode = currentNodePair.second;
		vector<int> neightborList = graph[currentNode];

		for(vector<int>::iterator it = neightborList.begin(); it != neightborList.end(); it++)
		{
			int nextNode = *it;
			int newDistance = pathLength[currentNode] + 1;
			if(newDistance < pathLength[nextNode])
			{
				pathLength[nextNode] = newDistance;
				bfsQueue.push(make_pair(pathLength[nextNode], nextNode));
			}
		}
	}
}

vector<int> nodeInWay(vector<vector<int>> &graph, int startNode, int endNode, vector<int> &pathLength)
{
	vector<int> result;
	queue<int> bfsQueue;
	vector<bool> visited(pathLength.size(), false);

	bfsQueue.push(endNode);
	visited[endNode] = true;
	result.push_back(endNode);

	while(bfsQueue.empty() == false)
	{
		int currentNode = bfsQueue.front();
		bfsQueue.pop();

		vector<int> neightborList = graph[currentNode];

		for(vector<int>::iterator it = neightborList.begin(); it != neightborList.end(); it++)
		{
			int nextNode = *it;
			int newDistance = pathLength[currentNode] - 1;
			if(newDistance == pathLength[nextNode] && visited[nextNode] == false)
			{
				result.push_back(nextNode);
				bfsQueue.push(nextNode);
				visited[nextNode] = true;
			}
		}
	}

	sort(result.begin(), result.end());

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<int>> graph;
		vector<vector<int>> graphReverse;
		vector<int> pathLength;

		cin >> n >> m;
		graph.assign(n, vector<int>(0));
		graphReverse.assign(n, vector<int>(0));

		for(int idxEdge = 0; idxEdge < m; idxEdge++)
		{
			int a, b;
			cin >> a >> b;
			graph[a - 1].push_back(b - 1);
			graphReverse[b - 1].push_back(a - 1);
		}

		shortestPath(graph, 0, n - 1, pathLength);
		vector<int> nodes = nodeInWay(graphReverse, 0, n - 1, pathLength);
		for(int idx = 0; idx < nodes.size(); idx++)
			cout << nodes[idx] + 1 << " ";
		cout << endl;
	}

	return 0;
}

/*
2
4 5
1 2
2 1
1 3
3 4
4 3
5 6
1 2
1 3
2 5
3 4
3 5
4 5
*/
