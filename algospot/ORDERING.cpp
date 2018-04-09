#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

string solve(vector<vector<int>> graph, vector<int> inDegree)
{
	string result = "";
	vector<bool> visited(graph.size(), false);

	while(result.size() < graph.size())
	{
		int node = 0;

		for(int i = 0; i < graph.size(); i++)
		{
			if(visited[i] == false && inDegree[i] == 0)
			{
				node = i;
				break;
			}
		}

		result += (char)(node + 'A');
		visited[node] = true;

		for(int i = 0; i < graph[node].size(); i++)
		{
			inDegree[graph[node][i]]--;
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
		vector<int> inDegree;
		vector<vector<int>> graph;
		cin >> n >> m;

		graph.assign(n, vector<int>(0));
		inDegree.assign(n, 0);

		for(int i = 0; i < m; i++)
		{
			int a, b;
			string str;
			cin >> str;
			a = str[0] - 'A';
			b = str[1] - 'A';
			graph[a].push_back(b);
			inDegree[b]++;
		}

		cout << solve(graph, inDegree) << endl;
	}

	return 0;
}
