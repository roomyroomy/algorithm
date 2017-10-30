#include <iostream>
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

int getPassword(DisjointSet &bomb, int metalNum)
{
	vector<int> connectCount(metalNum + 1);
	int maxConnect = 0;

	for(int idxMetal = 1; idxMetal < metalNum + 1; idxMetal++)
	{
		int rootNum = bomb.find(idxMetal);
		connectCount[rootNum]++;

		if(connectCount[rootNum] > maxConnect)
			maxConnect = connectCount[rootNum];
	}

	return maxConnect;
}

int main()
{
	int t, n, m;

	cin >> t;

	for(int idxCase = 0; idxCase < t; idxCase++)
	{
		cin >> n >> m;
		DisjointSet bomb(n + 1);

		for(int idxMetal = 0; idxMetal < m; idxMetal++)
		{
			int x, y;
			cin >> x >> y;
			bomb.merge(x, y);
		}

		cout << getPassword(bomb, n) << endl;
	}

	return 0;
}
