#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

double solve(vector<int> scores)
{
	double result = 0.0;
	int n = scores.size();
	int s = 0, e = n - 1;

	sort(scores.begin(), scores.end());

	while(s <= e)
	{
		double sc = (double)(scores[s] + scores[e]) / (double)2.0;
		result = max(sc, result);
		s++; e--;
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> scores;
		cin >> n;
		scores.assign(n, 0);
		for(int i = 0; i < n; i++)
			cin >> scores[i];
		cout << fixed << setprecision(1) << solve(scores) << endl;
	}

	return 0;
}
