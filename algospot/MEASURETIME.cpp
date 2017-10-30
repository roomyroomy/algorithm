#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int max_bound = 1000000;

typedef long long llong;

struct FenwickTree
{
	vector<int> tree;
	FenwickTree(int n) : tree(n+1){}

	int sum(int pos)
	{
		pos++;
		int ret = 0;
		while(pos > 0)
		{
			ret += tree[pos];
			pos &= (pos-1);
		}
		return ret;
	}

	void add(int pos, int val)
	{
		pos++;
		while(pos < tree.size())
		{
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};


llong solve()
{
	int n, a;
	llong result = 0;
	FenwickTree fenwick(max_bound);

	cin >> n;

	for(int idx = 0; idx < n; idx++)
	{
		cin >> a;
		result += (llong)(fenwick.sum(max_bound - 1) - fenwick.sum(a));
		fenwick.add(a, 1);
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cout << solve() << endl;
	}

	return 0;
}
