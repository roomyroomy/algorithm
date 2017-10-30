#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DisjointSet
{
private:
    vector<int> parent, rank, size;
public:
    DisjointSet(int n): parent(n), rank(n, 1), size(n, 1)
    {
        for (int idx = 0; idx < n; idx++)
        {
            parent[idx] = idx;
        }
    }
    int find(int n)
    {
		if(n < 0 || n == parent[n])
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
		{
			size[find(u)] += size[v];
            parent[u] = v;
		}
        else
		{
			size[find(v)] += size[u];
            parent[v] = u;
		}
        if (rank[u] == rank[v])
            rank[v]++;
    }
	int getComponentSize(int n)
	{
		return size[n];
	}
};

int main()
{
	int c, n, m, a, b;

	cin >> c;

	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		int conflictA = -1, conflictB = -1;
		string strReply;
		int conflictAt = -1;

		cin >> n >> m;
		DisjointSet editorList(n + 1);

		for(int idxReply = 0; idxReply < m; idxReply++)
		{
			cin >> strReply >> a >> b;

			if(conflictAt >= 0)
				continue;

			if(strReply.compare("ACK") == 0)
			{
				int rootA = editorList.find(a);
				int rootB = editorList.find(b);
				int conflictRootA = editorList.find(conflictA);
				int conflictRootB = editorList.find(conflictB);

				if(rootA > rootB)
					swap(rootA, rootB);
				if(conflictRootA > conflictRootB)
					swap(conflictRootA, conflictRootB);

				if(conflictRootA != -1 && conflictRootB != -1
					&& rootA == conflictRootA && rootB == conflictRootB)
				{
					conflictAt = idxReply + 1;
				}
				else
				{
					editorList.merge(a, b);
				}
			}
			else
			{
				int rootA = editorList.find(a);
				int rootB = editorList.find(b);
				
				if(rootA == rootB)
				{
					conflictAt = idxReply + 1;
				}
				else
				{
					conflictA = rootA;
					conflictB = rootB;
				}
			}
		}

		if(conflictAt >= 0)
			cout << "CONTRADICTION AT " << conflictAt << endl;
		else if(conflictA == -1 && conflictB == -1)
			cout << "MAX PARTY SIZE IS " << n << endl;
		else
			cout << "MAX PARTY SIZE IS " << n - min(editorList.getComponentSize(conflictA), editorList.getComponentSize(conflictB)) << endl;
	}

	return 0;
}
/*
4
4 4
ACK 0 1
ACK 1 2
DIS 1 3
ACK 2 0
100 4
ACK 0 1
ACK 1 2
ACK 2 3
ACK 3 4
3 3
ACK 0 1
ACK 1 2
DIS 2 0
8 6
DIS 0 1
ACK 1 2
ACK 1 4
DIS 4 3
DIS 5 6
ACK 5 7
*/