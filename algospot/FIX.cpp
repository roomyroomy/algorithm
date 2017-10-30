#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int T, N;
	vector<int> problemList;
	vector<int> originList;

	cin >> T;
	for(int idxCase = 0; idxCase < T; idxCase++)
	{
		int weight = 0, result = 0;
		cin >> N;

		problemList.clear();
		originList.clear();

		for(int idxInput = 0; idxInput < N; idxInput++)
		{
			cin >> weight;
			problemList.push_back(weight);
			originList.push_back(weight);
		}

		sort(problemList.begin(), problemList.end());

		for(int idxProblem = 0; idxProblem < N; idxProblem++)
		{
			if(problemList[idxProblem] == originList[idxProblem])
				result++;
		}

		cout << result << endl;
	}

	return 0;
}
