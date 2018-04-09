#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

vector<int> makeTable(int n)
{
	vector<int> table(n + 1, 0);
	vector<int> digits(10, 0);
	int p = 0, k = 1;

	while(p < n)
	{
		int remain = k;
		bool valid = true;

		while(remain > 0)
		{
			int cur = remain % 10;
			digits[cur]++;
			if(digits[cur] >= 2)
			{
				valid = false;
				break;
			}
			remain /= 10;
		}

		if(valid == true)
			table[++p] = k;

		k++;

		for(int i = 0; i < 10; i++)
		{
			digits[i] = 0;
		}
	}

	return table;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int n;
	vector<int> table = makeTable(1000000);

	while(true)
	{
		cin >> n;
		if(n == 0)
			break;
		cout << table[n] << endl;
	}

	return 0;
}
