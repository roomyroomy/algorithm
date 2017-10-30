#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const double INFINITE_DOUBLE = 10000000.0;
int T, N, L;
vector<int> costTable;
vector<int> accumulatedTable;

double solve()
{
	double minCost = INFINITE_DOUBLE;

	for(int idxStart = 0; idxStart < N - L + 1; idxStart++)
	{
		for(int idxEnd = idxStart + L - 1; idxEnd < N; idxEnd++)
		{
			int currentCost = accumulatedTable[idxEnd] - accumulatedTable[idxStart] + costTable[idxStart];
			double currentAvg = (double)currentCost / (idxEnd - idxStart + 1);
			if(currentAvg < minCost)
				minCost = currentAvg;
		}
	}

	return minCost;
}

int main()
{
	cin >> T;
	cout << std::fixed;

	for(int idxCase = 0; idxCase < T; idxCase++)
	{
		cin >> N >> L;
		costTable.clear();
		accumulatedTable.clear();

		for(int idxDay = 0; idxDay < N; idxDay++)
		{
			int cost = 0, lastCost = 0;

			if(idxDay > 0)
				 lastCost = accumulatedTable.back();

			cin >> cost;
			costTable.push_back(cost);
			accumulatedTable.push_back(lastCost + cost);
		}

		cout << std::setprecision(9) << solve() << endl;
	}

	return 0;
}
