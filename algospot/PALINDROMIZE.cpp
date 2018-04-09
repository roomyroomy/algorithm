#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

vector<int> getPi(string p)
{
	int m = (int)p.size(), j = 0;
	vector<int> pi(m, 0);

	for(int i = 1; i < m ; i++)
	{
		while(j > 0 && p[i] != p[j])
			j = pi[j - 1];
		if(p[i] == p[j])
			pi[i] = ++j;
	}

	return pi;
}

int kmp_modify(string s, string p)
{
	vector<int> ans;
	auto pi = getPi(p);
	int n = (int)s.size(), m = (int)p.size(), j = 0;
	for(int i = 0 ; i < n ; i++)
	{
		while(j > 0 && s[i] != p[j])
			j = pi[j - 1];

		if(s[i] == p[j])
		{
			if(j == m - 1)
			{
				ans.push_back(i - m + 1);
				j = pi[j];
			}
			else
			{
				j++;
			}
		}
	}
	return j;
}


int solve(string &str)
{
	int result = 0;
	string rstr= str;
	
	reverse(rstr.begin(), rstr.end());
	int overlap = kmp_modify(str, rstr);

	if(str.compare(rstr) == 0)
		result = str.size();
	else
		result = str.size() * 2 - overlap;

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int n;
	string str;

	cin >> n;
	for(int tc = 0; tc < n; tc++)
	{
		cin >> str;
		cout << solve(str) << endl;
	}

	return 0;
}
