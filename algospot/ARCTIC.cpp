#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int T, N;
vector<pair<double, double>> vecPoint;
vector<pair<double, pair<int, int>>> edges;

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

void makeEdges()
{
	edges.clear();

	for(int idxA = 0; idxA < N; idxA++)
	{
		for(int idxB = idxA + 1; idxB < N; idxB++)
		{
			double distX = vecPoint[idxA].first - vecPoint[idxB].first;
			double distY = vecPoint[idxA].second - vecPoint[idxB].second;
			double dist = sqrt((distX * distX) + (distY * distY));
			pair<int, int> oneEdge = make_pair(idxA, idxB);
			edges.push_back(make_pair(dist, oneEdge));
		}
	}

	sort(edges.begin(), edges.end());
}

double getMinimumDistance()
{
	int edgeLength = edges.size();
	int pickingCount = 0;
	DisjointSet sets(N);

	for(int idxEdge = 0; idxEdge < edgeLength; idxEdge++)
	{
		double weight = edges[idxEdge].first;
		pair<int, int> oneEdge = edges[idxEdge].second;

		if(sets.find(oneEdge.first) != sets.find(oneEdge.second))
		{
			sets.merge(oneEdge.first, oneEdge.second);
			pickingCount++;
		}

		if(pickingCount >= N - 1)
			return weight;
	}
}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);

	cin >> T;

	for(int idxCase = 0; idxCase < T; idxCase++)
	{
		cin >> N;
		vecPoint.clear();

		for(int idxPoint = 0; idxPoint < N; idxPoint++)
		{
			pair<double, double> point;
			cin >> point.first >> point.second;
			vecPoint.push_back(point);
		}

		makeEdges();
		cout << getMinimumDistance() << endl;
	}
}