#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;

using namespace std;

llong solve(llong n, llong m)
{
	llong winRatio = (m * 100) / n;
	llong minBound = 0, maxBound = 1;
	llong currentAdd = 1;

	if(winRatio > 98)
		return -1;

	while(((m + maxBound) * 100) / (n + maxBound) <= winRatio)
	{
		currentAdd *= 2;
		maxBound = minBound + currentAdd;
	}	

	while(maxBound > minBound + 1)
	{
		llong mid = (maxBound + minBound) / 2;
		llong midRatio = ((m + mid) * 100) / (n + mid);
		if(midRatio <= winRatio)
			minBound = mid;
		else
			maxBound = mid;
	}

	return maxBound;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	llong n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> m;
		cout << solve(n, m) << endl;
	}

	return 0;
}
