#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

typedef struct _traceNode {
	int previousNode;
	int accumulatedCost;
	int edgeCost;
} TRACE_NODE;

vector<int> candidateList;
vector<pair<int, int>> graph[10000];

bool existEdge(vector<pair<int, int>> node, pair<int, int> p)
{
	vector<pair<int, int>>::iterator it;
	for (it = node.begin(); it != node.end(); it ++)
	{
		if (it->first == p.first && it->second == p.second)
			return true;
	}

	return false;
}

void printResult(int N, int M)
{
	int backtraceNode;
	string strResult;
	vector<TRACE_NODE> bfsGraph(10000);

	queue<int> queueTraverse;
	queueTraverse.push(0);

	while (queueTraverse.empty() == false)
	{
		int nodeNum = queueTraverse.front(); queueTraverse.pop();
		vector<pair<int, int>>::iterator it;
		for (it = graph[nodeNum].begin(); it != graph[nodeNum].end(); it ++)
		{
			TRACE_NODE node;
			node.accumulatedCost = bfsGraph[nodeNum].accumulatedCost + 1;
			node.edgeCost = it->second;
			node.previousNode = nodeNum;

			if (bfsGraph[it->first].accumulatedCost == 0
				|| bfsGraph[it->first].accumulatedCost > node.accumulatedCost
				|| (bfsGraph[it->first].accumulatedCost == node.accumulatedCost
					&& bfsGraph[it->first].edgeCost < node.edgeCost))
			{
				bfsGraph[it->first] = node;
				queueTraverse.push(it->first);
			}
		}
	}

	backtraceNode = M;
	while (backtraceNode != 0)
	{
		strResult.push_back(bfsGraph[backtraceNode].edgeCost + '0');
		backtraceNode = bfsGraph[backtraceNode].previousNode;
	}

	reverse(strResult.begin(), strResult.end());
	cout << strResult << endl;
}

void makeGraph(int N, int M)
{
	// N으로 나누어서 나머지가 M이 되는...
	queue<int> queueTraverse;
	queueTraverse.push(0);

	while (queueTraverse.empty() == false)
	{
		int nodeNum = queueTraverse.front(); queueTraverse.pop();
		vector<int>::iterator it;
		for (it = candidateList.begin(); it != candidateList.end(); it ++)
		{
			int nextNode = (nodeNum * 10 + *it) % N;
			int cost = *it;

			if (existEdge(graph[nodeNum], make_pair(nextNode, cost)) == false)
			{
				graph[nodeNum].push_back(make_pair(nextNode, cost));
				queueTraverse.push(nextNode);
			}
		}
	}
}

void main()
{
	int T, N, M;
	string D;

	cin >> T;
	for (int idxTestCase = 0; idxTestCase < T; idxTestCase ++)
	{
		candidateList.clear();

		cin >> D;
		cin >> N >> M;

		for (unsigned int idxStr = 0; idxStr < D.length(); idxStr ++)
		{
			candidateList.push_back(D.at(idxStr) - '0');
		}
		makeGraph(N, M);
		printResult(N, M);
	}
}