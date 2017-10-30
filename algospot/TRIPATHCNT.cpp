/*
특정 지점 h, v에 대하여, 문제에 주어진 것과 역 방향으로 두 점에 대하여 대소를 비교해 나간다.
  1. path[h][v]에 대하여, path[h-1][v-1]와 path[h-1][v]를 비교,
   1) 만약 좌측 또는 우측 값이 큰 경우, 해당 값에 현재값을 더하여 저장하고, path의 개수를 취함
   2) 만약 두 값이 동일할 경우, 해당 값에 현재값을 더하여 저장하고, path의 개수는 두 값을 더하여 취함
  2. 계산이 완료되면, 마지막 줄에 대하여 최대값일 경우만 count 함 

2차원 배열 대신 1차원 배열 2개를 사용하면 메모리 절감이 있으나,
n의 최대값이 100으로 효과는 미미하다. 따라서, 구현이 편리한 2차원 배열을 선택한다.
*/
#include <iostream>
#include <vector>

using namespace std;

int maxTriPath(vector<vector<pair<int, int>>> &triPath)
{
	pair<int, int> maxPair;
	int triSize = triPath.size();

	triPath[0][0].second = 1;

	for(int idxHorizontal = 1; idxHorizontal < triSize; idxHorizontal++)
	{
		for(int idxVertical = 0; idxVertical < idxHorizontal + 1; idxVertical++)
		{
			pair<int, int> left, right;
			pair<int, int> current = triPath[idxHorizontal][idxVertical];
			if(idxVertical > 0)
				left = triPath[idxHorizontal - 1][idxVertical - 1];
			right = triPath[idxHorizontal - 1][idxVertical];

			if(left.first > right.first)
			{
				triPath[idxHorizontal][idxVertical] = make_pair(left.first + current.first, left.second);
			}
			else if(left.first < right.first)
			{
				triPath[idxHorizontal][idxVertical] = make_pair(right.first + current.first, right.second);
			}
			else
			{
				triPath[idxHorizontal][idxVertical] = make_pair(right.first + current.first, left.second + right.second);
			}
		}
	}

	for(int idxVertical = 0; idxVertical < triSize; idxVertical++)
	{
		if(triPath[triSize - 1][idxVertical].first > maxPair.first)
		{
			maxPair = triPath[triSize - 1][idxVertical];
		}
		else if(triPath[triSize - 1][idxVertical].first == maxPair.first)
		{
			maxPair.second += triPath[triSize - 1][idxVertical].second;
		}
	}

	return maxPair.second;
}

int main()
{
	int c;

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		int n;
		vector<vector<pair<int, int>>> tripath;
		cin >> n;

		tripath.assign(n, vector<pair<int, int>>(n, make_pair(0, 0)));

		for(int idxHorizontal = 0; idxHorizontal < n; idxHorizontal++)
		{
			for(int idxVertical = 0; idxVertical < idxHorizontal + 1; idxVertical++)
			{
				int num;
				cin >> num;
				tripath[idxHorizontal][idxVertical].first = num;
			}
		}

		cout << maxTriPath(tripath) << endl;
	}

	return 0;
}
/*
2
4
9
5 7
1 3 2
3 5 5 6
4
1
1 1 
1 1 1 
1 1 1 1 
*/