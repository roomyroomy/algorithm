#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int solve(string &s, int p, int q)
{
	int result = 0;
	int mid = 0;
	const char *c_str = s.c_str();

	mid = s.size() / 2;
	if(s.size() % 2 == 1)
		mid++;

	for(int idx = 0; idx < mid; idx++)
	{
		int rev = s.size() - 1 - idx;
		if(c_str[idx] != c_str[rev])
		{
			if(c_str[idx] == 'a' || c_str[rev] == 'a')
				result += p;
			if(c_str[idx] == 'b' || c_str[rev] == 'b')
				result += q;
		}
		else if(c_str[idx] == '?' && c_str[rev] == '?')
		{
			result += min(p, q);
			if(idx != rev)
				result += min(p, q);
		}
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, p, q;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		string str;
		cin >> n;
		cin >> str;
		cin >> p >> q;
		cout << solve(str, p, q) << endl;
	}

	return 0;
}
