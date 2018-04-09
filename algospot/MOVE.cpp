#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int INFINITY_INT = 2100000000;

int shortestPath(vector<vector<pair<int, int>>> &graph)
{
	vector<int> pathLength;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> bfsQueue;
	int graphSize = graph.size();
	int resultCost = 0;
	int startNode = 0, endNode = graph.size() - 1;

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
		vector<pair<int, int>> neightborList = graph[currentNode];

		for(vector<pair<int, int>>::iterator it = neightborList.begin(); it != neightborList.end(); it++)
		{
			int nextNode = it->first;
			int distance = it->second;
			int newDistance = pathLength[currentNode] + distance;
			if(newDistance < pathLength[nextNode])
			{
				pathLength[nextNode] = newDistance;
				bfsQueue.push(make_pair(pathLength[nextNode], nextNode));
			}
		}
	}

	resultCost = pathLength[endNode];

	return resultCost;	
}


int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m, u, v, w;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<pair<int, int>>> graph;
		cin >> n >> m;

		graph.assign(n, vector<pair<int, int>>(0));

		for(int e = 0; e < m; e++)
		{
			cin >> u >> v >> w;
			graph[u].push_back(make_pair(v, w));
			graph[v].push_back(make_pair(u, w));
		}

		cout << shortestPath(graph) << endl;
	}

	return 0;
}
