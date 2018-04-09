#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

void printDateTime(int n)
{
	int a = n / 1000000;
	int b = n / 100000 % 10;
	int c = n / 10000 % 10;
	int d = n / 1000 % 10;
	int e = n / 100 % 10;
	int f = n / 10 % 10;
	int g = n % 10;

	cout << a << b << c << d << "-" << e << f << "-" << g << g << " " << f << e << ":"  << d << c << ":" << b << a << endl;
}

void nextDigit(vector<int> &cur)
{
	int limit[] = {10, 6, 10, 6, 2, 3, 3};
	int toss = 0;

	cur[6]++;

	for(int i = 6; i >= 0; i--)
	{
		cur[i] += toss;
		toss = 0;

		if(cur[i] >= limit[i])
		{
			toss = 1;
			cur[i] = 0;
			if(i == 6)
				cur[i] = 1;
		}
	}

	if(cur[4] == 0 && cur[5] == 0)
		cur[5] = 1;
}

vector<int> makeTable(int n)
{
	vector<int> digits;
	vector<int> table;

	// ABCD - EF - GG   FE - DC - BA
	// A: 0 ~ 9
	// B: 0 ~ 5
	// C: 0 ~ 9
	// D: 0 ~ 5
	// E: 0 ~ 1
	// F: 0 ~ 1
	// G: 1 ~ 2
	table.push_back(1970011); // 1970-01-11 10-07-91
	table.push_back(2000011); 
	digits.push_back(2);
	digits.push_back(0);
	digits.push_back(0);
	digits.push_back(0);
	digits.push_back(0);
	digits.push_back(1);
	digits.push_back(1);

	for(int i = 2; i <= n; i++)
	{
		table.push_back(0);
		nextDigit(digits);

		for(int d = 0; d < 7; d++)
		{
			table[i] *= 10;
			table[i] += digits[d];
		}
	}

	return table;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	vector<int> table = makeTable(10000);

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n;
		printDateTime(table[n]);
	}

	return 0;
}
