#include <iostream>
#include <string>
#include <vector>

using namespace std;

int T, J, N;
pair<int, int> startPoint, endPoint;
vector< pair<int, int> > pointList;


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

bool checkReachable()
{
	DisjointSet sets(N + 2);

	for(int idxA = 0; idxA < N + 2; idxA++)
	{
		for(int idxB = 0; idxB < N + 2; idxB++)
		{
			if(idxA != idxB)
			{
				int distanceFirst = pointList[idxA].first - pointList[idxB].first;
				int distanceSecond = pointList[idxA].second - pointList[idxB].second;
				int distanceSquare = distanceFirst * distanceFirst + distanceSecond * distanceSecond;
				if (distanceSquare <= J * J)
				{
					sets.merge(idxA, idxB);
				}
			}
		}
	}

	return (sets.find(0) == sets.find(1));
}

int main()
{
	cin >> T;

	for(int idxTestCase = 0; idxTestCase < T; idxTestCase++)
	{
		cin >> J;
		cin >> startPoint.first >> startPoint.second;
		cin >> endPoint.first >> endPoint.second;
		cin >> N;

		pointList.clear();
		pointList.push_back(startPoint);
		pointList.push_back(endPoint);

		for(int idxPoint = 0; idxPoint < N; idxPoint++)
		{
			pair<int, int> point;
			cin >> point.first >> point.second;
			pointList.push_back(point);
		}

		if(checkReachable() == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
