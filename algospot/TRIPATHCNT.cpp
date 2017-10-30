/*
Ư�� ���� h, v�� ���Ͽ�, ������ �־��� �Ͱ� �� �������� �� ���� ���Ͽ� ��Ҹ� ���� ������.
  1. path[h][v]�� ���Ͽ�, path[h-1][v-1]�� path[h-1][v]�� ��,
   1) ���� ���� �Ǵ� ���� ���� ū ���, �ش� ���� ���簪�� ���Ͽ� �����ϰ�, path�� ������ ����
   2) ���� �� ���� ������ ���, �ش� ���� ���簪�� ���Ͽ� �����ϰ�, path�� ������ �� ���� ���Ͽ� ����
  2. ����� �Ϸ�Ǹ�, ������ �ٿ� ���Ͽ� �ִ밪�� ��츸 count �� 

2���� �迭 ��� 1���� �迭 2���� ����ϸ� �޸� ������ ������,
n�� �ִ밪�� 100���� ȿ���� �̹��ϴ�. ����, ������ ���� 2���� �迭�� �����Ѵ�.
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