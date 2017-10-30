#include <iostream>
#include <deque>
#include <vector>

using namespace std;

const int	MAX = 100;
const int	CONNTECTED = 1;
const int	VISITED = 1;
const int	NOT_VISITED = 0;

int T, N, M;
vector<int> graphFriend[MAX];
vector<int> virusStudent;
deque<int> visitQueue;

int getVirusStudent()
{
	vector<int> visitedList(N);

	for(deque<int>::iterator it = visitQueue.begin(); it != visitQueue.end(); it++)
	{
		visitedList[*it] = VISITED;
	}

	while(visitQueue.size() > 0)
	{
		int currentStudent = visitQueue.front();
		visitQueue.pop_front();

		for(int idx = 0; idx < N; idx++)
		{
			if(graphFriend[currentStudent][idx] == CONNTECTED && visitedList[idx] == NOT_VISITED)
			{
				int infectionCount = 0;

				for(vector<int>::iterator it = virusStudent.begin(); it != virusStudent.end(); it++)
				{
					if(graphFriend[idx][*it] == CONNTECTED)
					{
						infectionCount++;
						if(infectionCount >= 2)
							break;
					}
				}

				if(infectionCount >= 2)
				{
					visitedList[idx] = VISITED;
					visitQueue.push_back(idx);
					virusStudent.push_back(idx);
				}
			}
		}
	}

	return virusStudent.size();
}

int main()
{
	cin >> T;
	for(int idxCase = 0; idxCase < T; idxCase++)
	{
		cin >> N;

		for(int idxInput = 0; idxInput < N; idxInput++)
		{
			graphFriend[idxInput].clear();
		}

		for(int idxI = 0; idxI < N; idxI++)
		{
			for(int idxJ = 0; idxJ < N; idxJ++)
			{
				int connected;
				cin >> connected;
				graphFriend[idxI].push_back(connected);
			}
		}

		cin >> M;

		for(int idxScenario = 0; idxScenario < M; idxScenario++)
		{
			int student1, student2;
			cin >> student1 >> student2;

			virusStudent.clear();
			visitQueue.clear();

			visitQueue.push_back(student1 - 1);
			visitQueue.push_back(student2 - 1);
			virusStudent.push_back(student1 - 1);
			virusStudent.push_back(student2 - 1);

			cout << getVirusStudent();
			if(idxScenario == M - 1)
				cout << endl;
			else
				cout << " ";
		}
	}

	return 0;
}
