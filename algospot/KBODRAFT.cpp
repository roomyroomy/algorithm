#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

const int INF = 2100000000;

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

int solve(vector<pair<int, int>> &persons, int k)
{
	int ans = 0;
	int n = persons.size();
	vector<MaxTree> trees(9, MaxTree(n));

	for(int i = 0; i < n; i++)
	{
		int idx = persons[i].first;
		int abil = persons[i].second;

		trees[idx - 1].update(i, abil);
	}

	for(int i = 0; i < n - k + 1; i++)
	{
		int cand = 0;
		bool use = true;

		for(int p = 0; p < 9; p++)
		{
			int q = trees[p].query(i, i + k - 1);
			if(q > 0)
				cand += q;
			else
			{
				use = false;
				break;
			}
		}

		if(use == true && cand > ans)
			ans = cand;
	}

	return ans;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, k;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<pair<int, int>> persons;
		cin >> n >> k;
		for(int i = 0; i < n; i++)
		{
			int a, b;
			cin >> a >> b;
			persons.push_back(make_pair(a, b));
		}
		cout << solve(persons, k) << endl;
	}

	return 0;
}
