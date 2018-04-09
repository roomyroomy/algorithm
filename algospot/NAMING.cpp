#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>


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


vector<int> solve(string &str)
{
	vector<int> pi = getPi(str);
	vector<int> result;
	int p = str.size();

	while(p > 0)
	{
		result.push_back(p);
		p = pi[p - 1];
	}

	reverse(result.begin(), result.end());

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int len = 0;
	char str[400001];
	scanf("%s", str);
	len = strlen(str);
	scanf("%s", (str + len));
	string ss(str);
	vector<int> list = solve(ss);
	for(int i = 0; i < list.size(); i++)
		cout << list[i] << " ";
	cout << endl;

	return 0;
}
