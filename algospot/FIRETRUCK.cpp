#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INFINITY_INT = 2100000000;

int minCost(vector<vector<pair<int, int>>> &graph, vector<int> &fireSpot, vector<int> &fireStation)
{
	vector<int> pathLength;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> bfsQueue;
	int graphSize = graph.size();
	int spotSize = fireSpot.size();
	int stationSize = fireStation.size();
	int resultCost = 0;

	pathLength.assign(graphSize, INFINITY_INT);

	for(int idxStation = 0; idxStation < stationSize; idxStation++)
	{
		bfsQueue.push(make_pair(0, fireStation[idxStation]));
		pathLength[fireStation[idxStation]] = 0;
	}

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

	for(int idxSpot = 0; idxSpot < spotSize; idxSpot++)
	{
		resultCost += pathLength[fireSpot[idxSpot]];
	}

	return resultCost;	
}

int main()
{
	int c, v, e, n, m;

	cin >> c;

	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		vector<vector<pair<int, int>>> graph;
		vector<int> fireSpot, fireStation;

		cin >> v >> e >> n >> m;

		graph.assign(v + 1, vector<pair<int, int>>(0));

		for(int idxEdge = 0; idxEdge < e; idxEdge++)
		{
			int a, b, t;
			cin >> a >> b >> t;
			graph[a].push_back(make_pair(b, t));
			graph[b].push_back(make_pair(a, t));
		}

		for(int idxSpot = 0; idxSpot < n; idxSpot++)
		{
			int spot;
			cin >> spot;
			fireSpot.push_back(spot);
		}

		for(int idxStation = 0; idxStation < m; idxStation++)
		{
			int station;
			cin >> station;
			fireStation.push_back(station);
		}

		cout << minCost(graph, fireSpot, fireStation) << endl;
	}

	return 0;
}
