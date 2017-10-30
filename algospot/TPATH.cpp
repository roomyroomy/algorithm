#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class DisjointSet
{
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n): parent(n), rank(n, 1)
    {
        for (int idx = 0; idx < n; idx++)
        {
            parent[idx] = idx;
        }
    }

    int find(int n)
    {
        if (n == parent[n])
        {
            return n;
        }
        else
        {
            parent[n] = find(parent[n]);
            return parent[n];
        }
    }

    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
            return;
        if (rank[u] < rank[v])
            parent[u] = v;
        else
            parent[v] = u;
        if (rank[u] == rank[v])
            rank[v]++;
    }
};

int solve(vector<pair<int, pair<int, int>>> &edges, int n)
{
	int result = 0;
	sort(edges.begin(), edges.end());
	result = edges[edges.size() - 1].first - edges[0].first;

	for(int start = 0; start < edges.size(); start++)
	{
		DisjointSet ds(n);

		for(int end = start; end < edges.size(); end++)
		{
			ds.merge(edges[end].second.first, edges[end].second.second);
			if(edges[end].first - edges[start].first > result)
				break;
			if(ds.find(0) == ds.find(n - 1))
			{
				result = edges[end].first - edges[start].first;
				break;
			}
		}
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<pair<int, pair<int, int>>> edges;
		cin >> n >> m;

		for(int edge = 0; edge < m; edge++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			edges.push_back(make_pair(c, make_pair(a, b)));
		}

		cout << solve(edges, n) << endl;
	}

	return 0;
}
