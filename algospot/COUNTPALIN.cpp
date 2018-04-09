#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

typedef long long llong;


string addsharp(string &str)
{
	string result = "";

	for(int s = 0; s < str.size() - 1; s++)
	{
		result += str.c_str()[s];
		result += '#';
	}
	result += str[str.size() - 1];

	return result;
}
 
vector<int> manachers(string &str)
{
	string strSharp = addsharp(str);
	vector<int> table(strSharp.size(), 0);
	const string cStr = strSharp.c_str();
    int r = 0, p = 0;

	for(int i = 0; i < table.size(); i++)
	{
        if (i <= r)
			table[i] = min(table[2 * p - i], r - i);
        else
			table[i] = 0;
		while(i - table[i] - 1 >= 0
			&& i + table[i] + 1 < table.size()
			&& cStr[i - table[i] - 1] == cStr[i + table[i] + 1])
		{
			table[i]++;
		}
        if(r < i + table[i])
			r = i + table[i], p = i;
    }

	return table;
}

llong solve(string &str)
{
	llong result = 0;
	vector<int> table = manachers(str);

	for(int idx = 0; idx < table.size(); idx++)
	{
		if(idx % 2 == 0 && table[idx] > 1)
		{
			result += (llong)(table[idx] / 2);
		}
		else if(idx % 2 == 1 && table[idx] > 0)
		{
			result += (llong)((table[idx] + 1) / 2);
		}
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;
	string str;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> str;
		cout << solve(str) << endl;
	}

	return 0;
}
