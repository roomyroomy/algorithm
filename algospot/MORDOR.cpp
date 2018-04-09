#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

const int INF = 1000000000;

struct MaxTree
{
	int first;
	vector<int> tree;
	MaxTree(int n)
	{
		for(first = 1; first < n; first <<= 1);
		tree = vector<int>(n << 2, 0);
	}

	void update(int pos, int val)
	{
		pos += first;
		tree[pos] = val;
		while(pos >> 1)
		{
			tree[pos >> 1] = max(tree[pos >> 1], tree[pos]);
			pos >>= 1;
		}
	}

	int query(int l, int r)
	{
		l += first;
		r += first;
		int ret = 0;
		while(l <= r)
		{
			ret = max(ret, max(tree[l], tree[r]));
			l = (l + 1) >> 1;
			r = (r - 1) >> 1;
		}
		return ret;
	}
};

struct MinTree
{
	int first;
	vector<int> tree;
	MinTree(int n)
	{
		for(first = 1; first < n; first <<= 1);
		tree = vector<int>(n << 2, INF);
	}

	void update(int pos, int val)
	{
		pos += first;
		tree[pos] = val;
		while(pos >> 1)
		{
			tree[pos >> 1] = min(tree[pos >> 1], tree[pos]);
			pos >>= 1;
		}
	}

	int query(int l, int r)
	{
		l += first;
		r += first;
		int ret = INF;
		while(l <= r)
		{
			ret = min(ret, min(tree[l], tree[r]));
			l = (l + 1) >> 1;
			r = (r - 1) >> 1;
		}
		return ret;
	}
};

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, q;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> q;

		MaxTree maxTree(n);
		MinTree minTree(n);

		for(int i = 0; i < n; i++)
		{
			int k;
			cin >> k;
			maxTree.update(i, k);
			minTree.update(i, k);
		}

		for(int e = 0; e < q; e++)
		{
			int a, b;
			cin >> a >> b;
			int maxQ = maxTree.query(a, b);
			int minQ = minTree.query(a, b);

			cout << maxQ - minQ << endl;
		}
	}

	return 0;
}
