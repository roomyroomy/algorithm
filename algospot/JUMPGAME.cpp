/*
sample input:
2
7
2 5 1 6 1 4 1
6 1 1 2 2 9 3
7 2 3 2 1 3 1
1 1 3 1 7 1 2
4 1 2 3 4 1 2
3 3 1 2 3 4 1
1 5 2 9 4 7 0
7
2 5 1 6 1 4 1
6 1 1 2 2 9 3
7 2 3 2 1 3 1
1 1 3 1 7 1 2
4 1 2 3 4 1 3
3 3 1 2 3 4 1
1 5 2 9 4 7 0 

sample output:
YES
NO
*/
#include <iostream>
#include <deque>

using namespace std;

const int MAX_SIZE	= 100;

int C, N;
int table[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

bool bfs()
{
	deque<pair<int, int>> bfsQue;
	bfsQue.push_back(make_pair(0, 0));
	visited[0][0] = true;

	while(bfsQue.size() > 0 && visited[N - 1][N - 1] == false)
	{
		pair<int, int> currentPoint = bfsQue.front();
		int jumpValue = table[currentPoint.first][currentPoint.second];
		bfsQue.pop_front();
		if(currentPoint.first + jumpValue < N)
		{
			if(visited[currentPoint.first + jumpValue][currentPoint.second] == false)
			{
				bfsQue.push_back(make_pair(currentPoint.first + jumpValue, currentPoint.second));
				visited[currentPoint.first + jumpValue][currentPoint.second] = true;
			}
		}

		if(currentPoint.second + jumpValue < N)
		{
			if(visited[currentPoint.first][currentPoint.second + jumpValue] == false)
			{
				bfsQue.push_back(make_pair(currentPoint.first, currentPoint.second + jumpValue));
				visited[currentPoint.first][currentPoint.second + jumpValue] = true;
			}
		}
	}

	return visited[N - 1][N - 1];
}

int main()
{
	cin >> C;
	
	for(int idxTest = 0; idxTest < C; idxTest++)
	{
		cin >> N;
		for(int idxCol = 0; idxCol < N; idxCol++)
		{
			for(int idxRow = 0; idxRow < N; idxRow++)
			{
				cin >> table[idxCol][idxRow];
				visited[idxCol][idxRow]= false;
			}
		}
		if(bfs() == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
