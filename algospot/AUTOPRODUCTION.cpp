/*
1. 문제에 주어진 10개의 칸을 차례로 선택하되, 아래의 규칙을 따른다.
  1) 생산물의 개수를 최대로 하기 위하여, 같은 재료 중에서 가장 양이 많은 칸을 고른다.
  2) 여러 재료 중에서는, 생산물을 만들기 위한 숫자가 가장 부족한 것을 먼저 고른다.
  3) 2번 조건에서, 생산물을 만들기 위한 숫자가 동일하다면, 무엇을 선택해도 무방하다.
2. 같은 재료 중에서 가장 양이 많은 것을 고르기 위하여, 동일 재료는 정렬하여 큰 것부터 취한다.
3. 여러 재료 중에서 생산물을 만들기 위한 숫자가 부족한 것을 먼저 고르기 위하여 우선순위 큐를 사용한다.
4. 최종적으로, 각 재료별 선택된 값을 가지고, 최소 생산물 값을 찾으면 문제의 답이 된다.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int solve(vector<vector<int>> &materials, vector<int> &needs)
{
	int result = 1e16;
	int n = needs.size();
	vector<int> totals(n, 0);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;	// first: 재료로 만들수 있는 숫자, second: 인덱스

	for(int idxMat = 0; idxMat < n; idxMat++)
	{
		que.push(make_pair(0, idxMat));
	}

	for(int idx = 0; idx < 10; idx++)
	{
		pair<int, int> current = que.top();
		que.pop();
		totals[current.second] += materials[current.second].back();
		materials[current.second].erase(materials[current.second].end() - 1);
		if(materials[current.second].size() > 0)
			que.push(make_pair(totals[current.second] / needs[current.second], current.second));
		
		if(que.empty() == true)
			break;
	}

	for(int idxMat = 0; idxMat < n; idxMat++)
	{
		if(totals[idxMat] / needs[idxMat] < result)
			result = totals[idxMat] / needs[idxMat];
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, r, c, item;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<int>> materials;
		vector<int> needs;
		cin >> n;
		materials.assign(n, vector<int>(0));

		for(int idxMat = 0; idxMat < n; idxMat++)
		{
			cin >> r >> c;
			needs.push_back(r);
			for(int idxCell = 0; idxCell < c; idxCell++)
			{
				cin >> item;
				materials[idxMat].push_back(item);
			}
			sort(materials[idxMat].begin(), materials[idxMat].end());
		}

		cout << solve(materials, needs) << endl;
	}

	return 0;
}
