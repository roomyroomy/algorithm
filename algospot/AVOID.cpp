/*
 1. 인접 리스트 형태로 그래프 구성
 2. 각 노드까지 도달하는 최단 경로 구성
 3. 최단 경로 구성 시, 출발지에서 해당 노드까지 최단 경로의 수를 함께 계산 ... (값1)
 4. 출발지/도착지를 반대로하여 최단 경로의 수를 계산 ... (값2)
 5. (값1) * (값2)는 해당 지점을 지나는 최단 경로의 수가 된다.
 6. 각 지점에 대하여, 전체 경로의 수를 분모, 5에서 계산한 값을 분자로 하여 답을 출력
 7. 주의할 점은, 최대공약수를 구하여 주어진 조건에 맞는 수를 계산해야 한다는 점과, 도달하지 못하는 지점은 0/1로 출력해야 한다는 것이다.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INFINITY_INT = 2100000000;

long long gcd(long long u, long long v)
{
    long long t;
    while (v)
	{
        t = u % v;
        u = v;
        v = t;
    }
    return u;
}

vector<long long> getPathCaseNum(vector<vector<pair<int, int>>> &graph, int startNode, int endNode, vector<int> &pathLength)
{
	vector<long long> pathCaseNum(graph.size(), 0);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> bfsQueue;	// first: 최단 경로 길이, second: 노드 번호
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
			}
		}
	}

	return pathCaseNum;
}

vector<pair<long long, long long>> findProfessorProbability(vector<vector<pair<int, int>>> &graph)
{
	vector<pair<long long, long long>> probability(graph.size());
	vector<int> pathLengthForward, pathLengthBackward;
	vector<long long> pathCaseNumForward, pathCaseNumBackward;
	int graphSize = graph.size();
	long long totalCase = 0;

	pathCaseNumForward = getPathCaseNum(graph, 1, graphSize - 1, pathLengthForward);
	pathCaseNumBackward = getPathCaseNum(graph, graphSize - 1, 1, pathLengthBackward);
	totalCase = max(pathCaseNumBackward[1], (long long)1);

	for(int idxNode = 1; idxNode < graphSize; idxNode++)
	{
		long long currentCase = pathCaseNumForward[idxNode] * pathCaseNumBackward[idxNode];
		if(pathLengthForward[idxNode] + pathLengthBackward[idxNode] != pathLengthForward[graphSize - 1])
			currentCase = 0;

		long long gcdNum = gcd(currentCase, totalCase);
		probability[idxNode].first = currentCase / gcdNum;
		probability[idxNode].second = totalCase / gcdNum;
	}

	return probability;
}

int main()
{
	int c;

	cin >> c;

	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		int v, e, n;
		vector<vector<pair<int, int>>> graph;

		cin >> v >> e >> n;

		graph.assign(v + 1, vector<pair<int, int>>(0));

		for(int idxEdge = 0; idxEdge < e; idxEdge++)
		{
			int a, b, t;
			cin >> a >> b >> t;

			graph[a].push_back(make_pair(b, t));
			graph[b].push_back(make_pair(a, t));
		}

		vector<pair<long long, long long>> probabilityTable = findProfessorProbability(graph);

		for(int idxNode = 0; idxNode < n; idxNode++)
		{
			int place;
			cin >> place;

			cout << probabilityTable[place].first << "/" << probabilityTable[place].second << endl;
		}
	}

	return 0;
}

/*
1
10 10 10
1 2 10
2 3 10
3 4 10
4 5 10
5 6 10
6 7 10
7 8 10
8 9 10
9 10 10
1 10 90
1 2 3 4 5 6 7 8 9 10
*/

/*
1
5 5 3
1 2 5
2 3 4
3 4 2
1 4 10
2 4 5
1 3 5
*/

/*
2
8 11 4
1 2 1
2 4 1
1 3 1
3 4 1
1 4 2
4 5 2
5 7 1
5 8 3
4 6 1
6 8 4
7 8 2
2 4 5 7
4 5 2
1 2 1
1 2 2
1 3 1
2 4 1
3 4 1
2 4
*/
/*
1
8 10 4
1 2 1
2 4 1
1 3 1
3 4 1
1 4 2
4 5 2
5 7 1
5 8 3
4 6 1
6 8 4
2 4 5 7
*/
/*
1
4 4 4
1 2 1
1 3 1
2 4 1
3 4 1
1 2 3 4
*/
