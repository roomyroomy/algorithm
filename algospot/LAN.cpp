#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int T, N, M;
vector<pair<double, double>> vecPoint;
vector<pair<double, pair<int, int>>> edges;
int pickedEdgeCount;

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

bool connectEdge(int firstNode, int secondNode, DisjointSet &sets)
{
	if(sets.find(firstNode) != sets.find(secondNode))
	{
		sets.merge(firstNode, secondNode);
		pickedEdgeCount++;
		return true;
	}

	return false;
}

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

double getMinimumEdges(DisjointSet &sets)
{
	double result = 0.0;
	int length = edges.size();

	for(int idxEdge = 0; idxEdge < length; idxEdge++)
	{
		if(pickedEdgeCount >= N - 1)
			return result;

		double weight = edges[idxEdge].first;
		pair<int, int> edge = edges[idxEdge].second;
		if(connectEdge(edge.first, edge.second, sets))
			result += weight;
	}

	return result;
}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(10);

	cin >> T;

	for(int idxCase = 0; idxCase < T; idxCase++)
	{
		cin >> N >> M;
		DisjointSet sets(N);

		vecPoint.clear();
		pickedEdgeCount = 0;

		for(int idxX = 0; idxX < N; idxX++)
		{
			pair<double, double> point = make_pair(0.0, 0.0);
			cin >> point.first;

			vecPoint.push_back(point);
		}

		for(int idxY = 0; idxY < N; idxY++)
		{
			cin >> vecPoint[idxY].second;
		}

		makeEdges();

		for(int idxEdge = 0; idxEdge < M; idxEdge++)
		{
			int first, second;
			cin >> first >> second;
			connectEdge(first, second, sets);
		}

		cout << getMinimumEdges(sets) << endl;
	}

	return 0;
}