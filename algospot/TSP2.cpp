#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<long double>> tspTable;

long double minTsp(vector<vector<long double>> &graph, int currentNode, int currentDepth, int totalDepth, vector<bool> &visited, int currentKey)
{
	long double resultMin = -1.0;
	int n = graph.size();
	int key = (currentKey << 4) + currentNode;

	if(currentDepth == totalDepth)
		return 0.0;
	else
	{
		if(currentNode >= 0 && tspTable[currentNode][currentKey] > 0.0)
		{
			return tspTable[currentNode][currentKey];
		}
	}

	for(int idxNode = 0; idxNode < n; idxNode++)
	{
		if(currentNode == idxNode || visited[idxNode] == true)
			continue;

		long double tspValue;
		visited[idxNode] = true;
		tspValue = minTsp(graph, idxNode, currentDepth + 1, totalDepth, visited, currentKey + (1 << idxNode));
		if(currentNode >= 0)
			tspValue += graph[currentNode][idxNode];
		visited[idxNode] = false;
		if(resultMin < 0 || tspValue < resultMin)
			resultMin = tspValue;
	}

	if(currentNode >= 0)
		tspTable[currentNode][currentKey] = resultMin;

	return resultMin;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int c, n;

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		vector<vector<long double>> graph;
		vector<bool> visited;
		cin >> n;

		graph.assign(n, vector<long double>(n, 0.0));
		visited.assign(n, false);
		tspTable.clear();
		tspTable.assign(15, vector<long double>(1 << 15, -1.0));
		for(int idxRow = 0; idxRow < n; idxRow++)
		{
			for(int idxCol = 0; idxCol < n; idxCol++)
			{
				cin >> graph[idxRow][idxCol];
			}
		}

		cout << fixed << setprecision(10);
		cout << minTsp(graph, -1, 0, n, visited, 0) << endl;
	}

	return 0;
}
