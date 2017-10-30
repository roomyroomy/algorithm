/*
sample input:
2
10 3
3 3 3 1 2 3 2 2 2 1
9 3
1 744 755 4 897 902 890 6 777

sample output:
0
651
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INFINITE_VALUE = 2000000000;
const int INVALID = -1;

int C, N, S;
int table[100][10];
vector<int> sequence;

double roundValue(double x)
{
   return floor(x + 0.5);
}

void initTable()
{
	for(int idxA = 0; idxA < 100; idxA++)
	{
		for(int idxB = 0; idxB < 10; idxB++)
		{
			table[idxA][idxB] = INVALID;
		}
	}
}

int getSum(int start, int length)
{
	int result = 0, sum = 0, average = 0;

	for(int idxNum = 0; idxNum < length; idxNum++)
	{
		sum += sequence[start + idxNum];
	}
	average = roundValue((double)sum / length);

	for(int idxNum = 0; idxNum < length; idxNum++)
	{
		int diff = sequence[start + idxNum] - average;
		result += diff * diff;
	}

	return result;
}

int getSumMinimum(int start, int separate)
{
	if(table[start][separate] != INVALID)
		return table[start][separate];
	else if(separate == 1)
	{
		table[start][separate] = getSum(start, sequence.size() - start);
		return table[start][separate];
	}
	else if(separate >= sequence.size() - start)
	{
		table[start][separate] = 0;
		return 0;
	}

	int minResult = INFINITE_VALUE;
	int length = sequence.size();

	for(int idxDivide = start; idxDivide < length; idxDivide++)
	{
		int value = getSum(start, idxDivide - start + 1) + getSumMinimum(idxDivide + 1, separate - 1);
		if(value < minResult)
			minResult = value;
	}

	table[start][separate] = minResult;
	return minResult;
}

int main()
{
	cin >> C;

	for(int idxTest = 0; idxTest < C; idxTest++)
	{
		cin >> N >> S;
		sequence.clear();
		initTable();
		
		for(int idxNumber = 0; idxNumber < N; idxNumber++)
		{
			int value;
			cin >> value;
			sequence.push_back(value);
		}

		sort(sequence.begin(), sequence.end());
		
		cout << getSumMinimum(0, S) << endl;
	}

	return 0;
}
