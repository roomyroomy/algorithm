#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INFINITY_INT = 2100000000;

int T, N, M, Q;

int getPathCaseNum(vector<vector<pair<int, int>>> &graph, int startNode, int endNode)
{
	vector<int> pathLength;
	vector<int> pathCaseNum(graph.size(), 0);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> bfsQueue;
	int graphSize = graph.size();

	pathLength.assign(graphSize, INFINITY_INT);

	bfsQueue.push(make_pair(0, startNode));
	pathLength[startNode] = 0;
	pathCaseNum[startNode] = 1;

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
				pathCaseNum[nextNode] = pathCaseNum[currentNode];
			}
			else if(newDistance == pathLength[nextNode])
			{
				pathCaseNum[nextNode] += pathCaseNum[currentNode];
				if(pathCaseNum[nextNode] > 2)
					pathCaseNum[nextNode] = 2;
			}
		}
	}

	return pathCaseNum[endNode];
}

int main()
{
	cin >> T;

	while(T-- > 0)
	{
		vector<vector<pair<int, int>>> graph;

		cin >> N >> M >> Q;
		graph.assign(N + 1, vector<pair<int, int>>(0));

		for(int idxEdge = 0; idxEdge < M; idxEdge++)
		{
			int u, v, weight;
			cin >> u >> v >> weight;
			graph[u].push_back(make_pair(v, weight));
			graph[v].push_back(make_pair(u, weight));
		}

		for(int idxBus = 0; idxBus < Q; idxBus++)
		{
			int startNode, endNode;
			cin >> startNode >> endNode;
			switch(getPathCaseNum(graph, startNode, endNode))
			{
			case 0:
				cout << "no" << endl;
				break;
			case 1:
				cout << "only" << endl;
				break;
			default:
				cout << "many" << endl;
			}
		}
	}

	return 0;
}
/*
1
5 5 1
1 2 1
1 4 1
2 3 1
3 4 1
3 5 2
1 5
*/
/*
2
3 1 3
1 2 50
1 3
2 3
2 1
5 5 5
1 2 5
2 3 4
3 4 2
1 4 10
2 4 5
1 4
2 4
3 4
3 1
2 5
*/
/*
1
8 10 3
1 2 1
1 3 1
2 4 2
3 4 2
4 5 3
4 6 3
5 7 4
6 7 4
1 8 7
7 8 3
1 7
2 3
4 1
*/