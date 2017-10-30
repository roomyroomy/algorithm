/*
 소인수 분해를 통해 N = x_1 ^ s_1 + x_2 ^ s_2 + ... 이라고 할 때, 
 N의 약수의 개수 = (s_1 + 1) * (s_2 + 1) * ... 이다.
 이를 이용하여 약수의 개수를 구한다.

 또한, 계산 시간을 줄이기 위하여 아래 사항을 이용한다.
 1. 소인수 분해는 미리 구해둔 소수로만 나누어 본다.
 2. 소인수 분해는 N에 대하여 sqrt(N)까지만 수행한다.
 3. 하나의 숫자에 대하여 소인수 분해를 하면 계산 중복이 발생한다.
   --> 문제에 주어진 메모리가 충분하므로, table을 활용하여 소인수에 해당하는 숫자만 나누어 본다.
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> primeList;

void initPrimeTable()
{
	for(int idxNum = 2; idxNum * idxNum < 100000000 ;idxNum++)
	{
		int devideCount = 0;
		for(int idxComp = 2; idxComp * idxComp <= idxNum; idxComp++)
		{
			if(idxNum % idxComp == 0)
				devideCount++;
		}

		if(devideCount == 0)
			primeList.push_back(idxNum);
	}
}

int numOfPassNum(int n, int lo, int hi)
{
	int delta = hi - lo;
	int rootValue = (int)sqrt((double)hi);
	int resultCount = 0;
	vector<pair<int, int>> factorTable;

	for(int idxNum = 0; idxNum <= delta; idxNum++)
	{
		factorTable.push_back(make_pair(lo + idxNum, 1));
	}

	for(int idxPrime = 0; primeList[idxPrime] <= rootValue; idxPrime++)
	{
		int firstCompNum = lo;
		int mod = lo % primeList[idxPrime];

		if(mod > 0)
			firstCompNum += (primeList[idxPrime] - mod);

		for(int idxNum = firstCompNum - lo; idxNum <= delta; idxNum += primeList[idxPrime])
		{
			int devideCount = 0;
			while(factorTable[idxNum].first % primeList[idxPrime] == 0)
			{
				factorTable[idxNum].first /= primeList[idxPrime];
				devideCount++;
			}
			if(factorTable[idxNum].second == 1)
				factorTable[idxNum].second = (devideCount + 1);
			else
				factorTable[idxNum].second *= (devideCount + 1);
		}
	}

	for(int idxNum = 0; idxNum <= delta; idxNum++)
	{
		if(factorTable[idxNum].first > 1)
		{
			factorTable[idxNum].second *= 2;
		}

		if(factorTable[idxNum].second == 1)
			factorTable[idxNum].second = 2;

		if(factorTable[idxNum].second == n)
			resultCount++;
	}

	return resultCount;
}

//#include <time.h>
int main()
{
    //clock_t begin, end;
    //begin = clock();
	int c, n, lo, hi;

	initPrimeTable();

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		cin >> n >> lo >> hi;
		cout << numOfPassNum(n, lo, hi) << endl;
	}

	//end = clock();
    //cout<<"Elasped Time : "<< (end-begin) <<endl;

	return 0;
}
