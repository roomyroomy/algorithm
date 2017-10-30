// 다중집합 순열 : https://ko.wikipedia.org/wiki/%EC%88%9C%EC%97%B4#.EB.8B.A4.EC.A4.91.EC.A7.91.ED.95.A9_.EC.88.9C.EC.97.B4
// a를 한개 선택 후 나머지 string에 대하여 개수를 세고(left child), b를 한개 선택 후 나머지 string에 대하여 개수를 센다(right child).
// left 또는 right child에 대하여 k번째 단어를 찾아 나간다.
// 시간 복잡도 : O(n)

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#define INFINITY_NUM	200000000

using namespace std;


vector<vector<int>> perMutationTable;

void makePermutationMultisetTable()
{
	perMutationTable.assign(101, vector<int>(101, 0));

	for(int idxN = 0; idxN <= 100; idxN++)
	{
		for(int idxM = 0; idxM <= 100; idxM++)
		{
			if(idxN == 0 || idxM == 0)
				perMutationTable[idxN][idxM] = 1;
			else if(idxN == 1 || idxM == 1)
				perMutationTable[idxN][idxM] = idxN + idxM;
			else
				perMutationTable[idxN][idxM] = perMutationTable[idxN - 1][idxM] + perMutationTable[idxN][idxM - 1];

			if(perMutationTable[idxN][idxM] > INFINITY_NUM)
				perMutationTable[idxN][idxM] = INFINITY_NUM;
		}
	}
}

string kthString(int n, int m, int k)
{
	string result = "";

	if(k == 1)
	{
		for(int idx = 0; idx < n; idx++)
		{
			result += "a";
		}
		for(int idx = 0; idx < m; idx++)
		{
			result += "b";
		}
	}
	else
	{
		if(k > perMutationTable[n][m])
		{
			result = "NONE";
		}
		else if(k <= perMutationTable[n - 1][m])
		{
			// 'a'를 하나 뺐을 경우 다중 집합 순열 (left child)
			// factorial(n - 1 + m) / (factorial(n - 1) * factorial(m))
			result += "a";
			result += kthString(n - 1, m, k);
		}
		else
		{
			// 'b'를 하나 뺐을 경우 다중 집합 순열 (right child)
			// factorial(n + m - 1) / (factorial(n - 1) * factorial(m))
			result += "b";
			result += kthString(n, m - 1, k - perMutationTable[n - 1][m]);
		}
	}

	return result;
}

int main()
{
	int t, n, m, k;

	makePermutationMultisetTable();

	cin >> t;

	for(int idxCase = 0; idxCase < t; idxCase++)
	{
		cin >> n >> m >> k;
		cout << kthString(n, m, k) << endl;
	}
	return 0;
}
