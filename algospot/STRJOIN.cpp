#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


int solve(priority_queue<int> &seq)
{
	int result = 0;

	while(seq.size() > 1)
	{
		int a, b;
		a = seq.top();
		seq.pop();
		b = seq.top();
		seq.pop();

		result += -(a + b);
		seq.push(a + b);
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, k;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		priority_queue<int> seq;
		cin >> n;
		for(int i = 0; i < n; i++)
		{
			cin >> k;
			seq.push(-k);
		}
		cout << solve(seq) << endl;
	}

	return 0;
}
