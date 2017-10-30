#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;

	cout << fixed << setprecision(10);

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<double>> probability;
		cin >> n >> m;
		probability.assign(m + 1, vector<double>(n + 1, 0.0));

		probability[0][0] = 1.0;

		for(int idxDay = 0; idxDay < m; idxDay++)
		{
			for(int idxHeight = 0; idxHeight <= n; idxHeight++)
			{
				int rain = min(idxHeight + 2, n);
				int sunny = min(idxHeight + 1, n);
				probability[idxDay + 1][rain] += probability[idxDay][idxHeight] * 0.75;
				probability[idxDay + 1][sunny] += probability[idxDay][idxHeight] * 0.25;
			}
		}

		cout << probability[m][n] << endl;
	}

	return 0;
}
