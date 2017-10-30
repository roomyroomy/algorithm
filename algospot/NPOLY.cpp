/*
1. Dynamic Programming으로 해결한다.
  - Dynamic Programming 해법을 사용할 수 있는 이유는, 모든 폴리오미노는 부분 폴리오미노의 합으로 구성되기 때문이다.
2. poly[a][b] 값의 정의 : 총 a개의 블럭 중, 최상단 블럭이 b개일 때 경우의 수
3. N-폴리오미노 nPoly[a] = poly[a][1] + poly[a][2] + ... + poly[a][b]
 - a와 b의 값이 같으면 poly[a][b]의 값은 1이 된다.
 - 이외의 경우 poly[a][b] 값은 poly[a - 1]에 포함된 모든 값에 맞닿은 블럭의 경우의 수의 곱의 합이다.
4. symPoly[a] 값의 정의 : 총 a개의 블럭 중, 최상단 블럭이 b개일 때 세로 대칭 폴리오미노
 - a가 짝수일 때 : 중간에 끼인 블럭의 개수가 0, 2, 4, ... a개일 때까지의 합을 구해 나간다.
 - a가 홀수일 때 : 중간에 끼인 블럭의 개수가 1, 2, 5, ... a개일 때까지의 합을 구해 나간다.
 - symPoly[a] = 
	짝수일 경우 nPoly[a / 2] + poly[(a - 2) / 2 + 2][2] + poly[(a - 4) / 2 + 4][4] + ...
	홀수일 경우 poly[(a - 1) / 2 + 1][1] + poly[(a - 3) / 2 + 3][3] + ... 
5. nPoly[a] - symPoly[a] 값이 정답이 된다. 단, 음수일 경우 20090711을 더한다.
6. 시간 복잡도는 O(N ^ 3)
*/

#include <iostream>
#include <vector>

using namespace std;

const int modNum = 20090711;
const int maxPoly = 100;

vector<int> initPolyTable()
{
	vector<int> polyResultTable(maxPoly + 1, 0);
	vector<vector<int>> polyTable;
	vector<int> symPolyTable(maxPoly + 1, 0);
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

	for(int idxRow = 1; idxRow <= maxPoly; idxRow++)
	{
		if(idxRow % 2 == 0)
			symPolyTable[idxRow] = polyResultTable[idxRow / 2];

		for(int idxCol = idxRow % 2; idxCol <= idxRow; idxCol += 2)
		{
			symPolyTable[idxRow] += polyTable[(idxRow - idxCol) / 2 + idxCol][idxCol];
			symPolyTable[idxRow] %= modNum;
		}
	}

	for(int idxRow = 1; idxRow <= maxPoly; idxRow++)
	{
		polyResultTable[idxRow] -= symPolyTable[idxRow];
		if(polyResultTable[idxRow] < 0)
			polyResultTable[idxRow] += modNum;
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

/*
3
2
4
92
*/