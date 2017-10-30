#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


int main()
{
	std::ios::sync_with_stdio(false);

	int c, n, d, p;

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		vector<vector<int>> graph;
		vector<vector<double>> probTable;

		cin >> n >> d >> p;
		graph.assign(n, vector<int>(0));
		probTable.assign(d + 1, vector<double>(n, 0.0));
		probTable[0][p] = 1.0;
		for(int idxRow = 0; idxRow < n ; idxRow++)
		{
			for(int idxCol = 0; idxCol < n; idxCol++)
			{
				int exist;
				cin >> exist;
				if(exist == 1)
					graph[idxRow].push_back(idxCol);
			}
		}

		for(int idxDay = 0; idxDay < d; idxDay++)
		{
			for(int idxNode = 0; idxNode < n; idxNode++)
			{
				if(probTable[idxDay][idxNode] > 0.0)
				{
					int nodeCount = graph[idxNode].size();
					for(int idxNext = 0; idxNext < nodeCount; idxNext++)
					{
						int nextNode = graph[idxNode][idxNext];
						probTable[idxDay + 1][nextNode] += probTable[idxDay][idxNode] / (double)nodeCount;
					}
				}
			}
		}

		cin >> n;
		for(int idxNode = 0; idxNode < n; idxNode++)
		{
			int nodeNum;
			cin >> nodeNum;
			cout << fixed << setprecision(8);
			cout << probTable[d][nodeNum] << " ";
		}
		cout << endl;
	}

	return 0;
}
