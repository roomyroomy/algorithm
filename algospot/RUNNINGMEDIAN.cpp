#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long llong;


int solve(int n, int a, int b)
{
	const int max_bound = 20090711;
	int result = 0, curNum = 1983;
	priority_queue<int, vector<int>, less<int>> leftQue;
	priority_queue<int, vector<int>, greater<int>> rightQue;

	for(int seq = 1; seq <= n; seq++)
	{
		leftQue.push(curNum);
		if(leftQue.size() > rightQue.size() + 1)
		{
			rightQue.push(leftQue.top());
			leftQue.pop();
		}
		if(rightQue.size() > 0 && leftQue.top() > rightQue.top())
		{
			int left = leftQue.top(); leftQue.pop();
			int right = rightQue.top(); rightQue.pop();

			leftQue.push(right);
			rightQue.push(left);
		}

		result += leftQue.top();
		result %= max_bound;

		curNum = (int)(((llong)curNum * (llong)a + (llong)b) % (llong)max_bound);
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, a, b;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> a >> b;
		cout << solve(n, a, b) << endl;
	}

	return 0;
}
