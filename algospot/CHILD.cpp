#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


const int INF = 1000000000;

struct MCMF 
{
	struct Edge 
	{
		int v, rev, cost, cap;
		Edge(int vv, int rr, int ccost, int ccap) :v(vv), rev(rr), cost(ccost), cap(ccap) {}
	};
	int s;
	vector<vector<Edge>> edge;
	MCMF(int size) :s(size + 2) { edge.resize(s + 1); }
	void add_edge(int u, int v, int cost, int cap)
	{
		edge[u].emplace_back(Edge(v, edge[v].size(), cost, cap));
		edge[v].emplace_back(Edge(u, edge[u].size() - 1, -cost, 0));
	}
	int getMCMF(int src, int sink)
	{
		int ret = 0;
		while (true)
		{
			queue<int> q;
			vector<bool> inQ(s + 1, false);
			vector<int> dist(s + 1, INF);
			vector<int> par(s + 1, -1), paridx(s + 1, -1);

			dist[src] = 0;
			inQ[src] = true;
			q.push(src);
			while (!q.empty())
			{
				int here = q.front();
				q.pop();
				inQ[here] = false;

				for (int n = 0;n < edge[here].size();++n)
				{
					int next = edge[here][n].v;
					int cap = edge[here][n].cap;
					if (cap && dist[next] > dist[here] + edge[here][n].cost)
					{
						dist[next] = dist[here] + edge[here][n].cost;
						par[next] = here;
						paridx[next] = n;
						if (!inQ[next])
						{
							inQ[next] = true;
							q.push(next);
						}
					}
				}
			}
			if (par[sink] == -1) break;
			int flow = INF;
			for (int i = sink;i != src;i = par[i])
			{
				int prev = par[i];
				int idx = paridx[i];
				flow = min(flow, edge[prev][idx].cap);
			}
			for (int i = sink; i != src; i = par[i])
			{
				int prev = par[i];
				int idx = paridx[i];
				edge[prev][idx].cap -= flow;
				edge[i][edge[prev][idx].rev].cap += flow;
				ret += flow * edge[prev][idx].cost;
			}
		}
		return ret;
	}
};

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, e, v1, v2, d;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> e;

		// 양방향 그래프로 변경하기 위하여 노드 k에 대하여 k * 2는 in-node, k * 2 + 1은 out-node로 간주
		MCMF mcmf(n * 2 + 1);

		for(int i = 0; i < n; i++)
		{
			mcmf.add_edge(i * 2, i * 2 + 1, 0, INF);
		}

		for(int i = 0; i < e; i++)
		{
			cin >> v1 >> v2 >> d;
			v1--; v2--;
			mcmf.add_edge(v1 * 2 + 1, v2 * 2, d, 1);
			mcmf.add_edge(v2 * 2 + 1, v1 * 2, d, 1);
		}
		mcmf.add_edge(0 * 2 + 1, n * 2, 0, 1);
		mcmf.add_edge((n - 1) * 2 + 1, n * 2, 0, 1);

		cout << mcmf.getMCMF(1 * 2 + 1, n * 2) << endl;
	}

	return 0;
}
