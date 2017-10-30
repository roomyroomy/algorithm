#include <iostream>
#include <vector>
#include <set>

using namespace std;

int C, N, M;
vector<set<int>> studentList(10);

int maskingCount = 0;
bool masking[10];

int traverseCase(int start = 0)
{
	int result = 0;

	if(start == 0)
	{
		for(int idxMask = 0; idxMask < 10; idxMask++)
			masking[idxMask] = 0;
		maskingCount = 0;
	}

	if(maskingCount >= N)
		return 1;

	for(int idxStudent = start; idxStudent < N; idxStudent++)
	{
		if(masking[idxStudent] == 0)
		{
			for(set<int>::iterator it = studentList[idxStudent].begin(); it != studentList[idxStudent].end(); it++)
			{
				if(masking[*it] == 0)
				{
					masking[idxStudent] = 1;
					masking[*it] = 1;
					maskingCount += 2;
					result += traverseCase(idxStudent + 1);
					masking[idxStudent] = 0;
					masking[*it] = 0;
					maskingCount -= 2;
				}
			}
		}
	}

	return result;
}

int main()
{
	cin >> C;

	for(int idxCase = 0; idxCase < C; idxCase++)
	{
		for(int idxStudent = 0; idxStudent < 10; idxStudent++)
			studentList[idxStudent].clear();

		cin >> N >> M;

		for(int idxPair = 0; idxPair < M; idxPair++)
		{
			int firstStudent, secondStudent;
			int minStudent, maxStudent;
			cin >> firstStudent >> secondStudent;
			minStudent = min(firstStudent, secondStudent);
			maxStudent = max(firstStudent, secondStudent);
			studentList[minStudent].insert(maxStudent);
		}
		cout << traverseCase() << endl;
	}

	return 0;
}
