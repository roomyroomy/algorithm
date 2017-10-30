/*
1. Dynamic Programming���� �ذ��Ѵ�.
  - Dynamic Programming �ع��� ����� �� �ִ� ������, ��� �������̳�� �κ� �������̳��� ������ �����Ǳ� �����̴�.
2. poly[a][b] ���� ���� : �� a���� �� ��, �ֻ�� ���� b���� �� ����� ��
3. N-�������̳� nPoly[a] = poly[a][1] + poly[a][2] + ... + poly[a][b]
 - a�� b�� ���� ������ poly[a][b]�� ���� 1�� �ȴ�.
 - �̿��� ��� poly[a][b] ���� poly[a - 1]�� ���Ե� ��� ���� �´��� ���� ����� ���� ���� ���̴�.
4. symPoly[a] ���� ���� : �� a���� �� ��, �ֻ�� ���� b���� �� ���� ��Ī �������̳�
 - a�� ¦���� �� : �߰��� ���� ���� ������ 0, 2, 4, ... a���� �������� ���� ���� ������.
 - a�� Ȧ���� �� : �߰��� ���� ���� ������ 1, 2, 5, ... a���� �������� ���� ���� ������.
 - symPoly[a] = 
	¦���� ��� nPoly[a / 2] + poly[(a - 2) / 2 + 2][2] + poly[(a - 4) / 2 + 4][4] + ...
	Ȧ���� ��� poly[(a - 1) / 2 + 1][1] + poly[(a - 3) / 2 + 3][3] + ... 
5. nPoly[a] - symPoly[a] ���� ������ �ȴ�. ��, ������ ��� 20090711�� ���Ѵ�.
6. �ð� ���⵵�� O(N ^ 3)
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
	// polyTable[a][b] = �� a���� �� ��, �ֻ�� ���� b���� �� ����� ��

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
				// �ֻ�� ���� ���� ���Ͽ� ���
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