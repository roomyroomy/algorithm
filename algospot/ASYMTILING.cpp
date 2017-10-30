#include <iostream>
using namespace std;

int symResult[101] = { 1, 1, 2, 0 };

int getSymTilingNum(int n)
{
    if ( symResult[n] != 0 )
	{
		return symResult[n];
	}
	else if ( symResult[n] == 0 )
	{
		int totalNum = getSymTilingNum(n - 1) + getSymTilingNum(n - 2);
		totalNum %= 1000000007;
		symResult[n] = totalNum;
		return symResult[n];
	}
}

int getTilingNum(int n)
{
	int result = getSymTilingNum(n);

	if ( n % 2 == 0 )
		result -= getSymTilingNum(n / 2 + 1);
	else
		result -= getSymTilingNum((n - 1) / 2);

	result %= 1000000007;

	if ( result < 0 )	result += 1000000007;

	return result;
}

int main()
{
	int caseNum;

	cin >> caseNum;

	for ( int index = 0 ; index < caseNum ; index ++ )
	{
		int n;
		cin >> n;
		cout << getTilingNum(n) << endl;
	}

	return 0;
}
