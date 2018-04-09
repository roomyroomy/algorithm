#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long llong;
const llong modular = 1000000007;

vector<llong> makeTable()
{
	vector<llong> table(1001, 0);
	llong mm = 1, b = 2;

	table[1] = 2;
	for(int i = 2; i <= 1000; i++)
	{
		mm *= (i * 2 - 1); mm %= modular;
		b *= 4; b %= modular;
		table[i] = mm * b;
		table[i] %= modular;
	}

	return table;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int n;

	vector<llong> table = makeTable();
	while(true)
	{
		cin >> n;
		if(n == 0)
			break;
		cout << table[n] << endl;
	}

	return 0;
}
