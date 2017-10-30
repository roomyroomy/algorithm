/*
1. Dynamic Programming으로 해결한다.
  - Dynamic Programming 해법을 사용할 수 있는 이유는, 모든 폴리노미오는 부분 폴리노미오의 합으로 구성되기 때문이다.
2. poly[a][b] 값의 정의 : 총 a개의 블럭 중, 최상단 블럭이 b개일 때 경우의 수
3. N-폴리노미오는 poly[a][1] + poly[a][2] + ... + poly[a][b]
 - a와 b의 값이 같으면 poly[a][b]의 값은 1이 된다.
 - 이외의 경우 poly[a][b] 값은 poly[a - 1]에 포함된 모든 값에 맞닿은 블럭의 경우의 수의 곱의 합이다.
4. 시간 복잡도는 O(n ^ 3)
*/

#include <iostream>
#include <vector>

using namespace std;

const int modNum = 10000000;
const int maxPoly = 100;

vector<int> initPolyTable()
{
	vector<int> polyResultTable(maxPoly + 1);
	vector<vector<int>> polyTable;
	polyTable.assign(maxPoly + 1, vector<int>(maxPoly + 1, 0));
	// polyTable[a][b] = 총 a개의 블럭 중, 최상단 블럭이 b개일 때 경우의 수

	for(int idxRow = 1; idxRow <= maxPoly; idxRow++)
	{
		for(int idxCol = 1; idxCol <= idxRow; idxCol++)
		{
			if(idxCol == idxRow)
			{
				polyTable[idxRow][idxCol] = 1;
			}
			else
			{
				// 최상단 블럭의 수에 대하여 계산
				for(int idxTop = 1; idxTop <= idxRow - idxCol; idxTop++)
				{
					polyTable[idxRow][idxCol] += (idxCol + idxTop - 1) * polyTable[idxRow - idxCol][idxTop];
					polyTable[idxRow][idxCol] %= modNum;
				}
			}

			polyResultTable[idxRow] += polyTable[idxRow][idxCol];
			polyResultTable[idxRow] %= modNum;
		}
	}

	return polyResultTable;
}

int main()
{
	int c, n;
	vector<int> polyResultTable = initPolyTable();

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		cin >> n;
		cout << polyResultTable[n] << endl;
	}

	return 0;
}
