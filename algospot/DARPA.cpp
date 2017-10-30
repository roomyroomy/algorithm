#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

bool available(vector<int> &boxes, int n, int value)
{
	int previous = boxes[0];
	n--;

	for(int idx = 1; idx < boxes.size(); idx++)
	{
		if(boxes[idx] - previous >= value)
		{
			previous = boxes[idx];
			if(--n <= 0)
				return true;
		}
	}

	return false;
}

int solve(vector<int> &boxes, int n)
{
	int minBound = 0, maxBound = 24000;

	while(minBound + 1 < maxBound)
	{
		int midBound = (maxBound + minBound) / 2;
		bool availMin = available(boxes, n, midBound);
		if(availMin == true)
			minBound = midBound;
		else
			maxBound = midBound;
	}

	return minBound;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cout << fixed << setprecision(2);

	int tc, n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> boxes;
		cin >> n >> m;

		for(int idx = 0; idx < m; idx++)
		{
			double d;
			cin >> d;
			boxes.push_back((int)((d + 0.005) * (double)100.00));
		}

		cout << (double)solve(boxes, n) / (double) 100.0 << endl;
	}

	return 0;
}
