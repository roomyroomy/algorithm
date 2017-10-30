#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

string ppap;


void makePpap()
{
	while(ppap.size() < 1000000)
	{
		ppap += "pen-pineapple-apple-pen/";
	}
}

vector<int> getPi(string p)
{
	int m = (int)p.size(), j=0;
	vector<int> pi(m, 0);
	for(int i = 1; i< m ; i++)
	{
		while(j > 0 && p[i] != p[j])
			j = pi[j-1];
		
		if(p[i] == p[j])
			pi[i] = ++j;
	}
	return pi;
}

vector<int> kmp(string s, string p)
{
	vector<int> ans;
	auto pi = getPi(p);
	int n = (int)s.size(), m = (int)p.size(), j = 0;
	for(int i = 0 ; i < n ; i++)
	{
		while(j>0 && s[i] != p[j])
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
	return ans;
}


int main()
{
	std::ios::sync_with_stdio(false);

	int l, r;
	string p;

	cin >> l >> r >> p;
	makePpap();
	ppap = ppap.substr(l - 1, r - l + 1);
	vector<int> stringPos = kmp(ppap, p);
	cout << stringPos.size() << endl;

	return 0;
}
