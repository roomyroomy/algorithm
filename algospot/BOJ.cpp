#include <iostream>
#include <iomanip>
#include <list>
#include <vector>

using namespace std;

const int INFINITY = 2000000000;

list<pair<int, int>> queue;
vector<vector<int>> map;
vector<vector<int>> pathTable;
int N, M;

int shortestPathLength()	// bfs
{
	int nextTable[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	pathTable.assign(M, vector<int>(N, INFINITY));
	queue.push_back(make_pair(0, 0));
	pathTable[0][0] = 0;

	while(queue.size() > 0)
	{
		int currentValue;
		pair<int, int> currentPoint = queue.front();
		queue.pop_front();
		currentValue = pathTable[currentPoint.first][currentPoint.second];

		for(int idxArrow = 0; idxArrow < 4; idxArrow++)
		{
			pair<int, int> nextPoint;
			nextPoint.first = currentPoint.first + nextTable[idxArrow][0];
			nextPoint.second = currentPoint.second + nextTable[idxArrow][1];

			if(nextPoint.first >= 0 && nextPoint.first < M
				&& nextPoint.second >= 0 && nextPoint.second < N)
			{
				int nextValue = currentValue + map[nextPoint.first][nextPoint.second];
				if(nextValue < pathTable[nextPoint.first][nextPoint.second])
				{
					pathTable[nextPoint.first][nextPoint.second] = nextValue;
					queue.push_back(nextPoint);
				}
			}
		}
	}

	return pathTable[M-1][N-1];
}

int main()
{
	char ch;
	cin >> N >> M;
	map.assign(M, vector<int>(N, 0));

	for(int idxRow = 0; idxRow < M; idxRow++)
	{
		for(int idxCol = 0; idxCol < N; idxCol++)
		{
			cin >> ch;
			map[idxRow][idxCol] = ch - '0';
		}
	}

	cout << shortestPathLength() << endl;

	return 0;
}
