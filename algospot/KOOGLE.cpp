#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

typedef long double ldouble;


pair<int, int> count(string &str)
{
	pair<int, int> result = make_pair(0, 0);

	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
			result.first++;
		else if(str[i] >= '0' && str[i] <= '9')
			result.second++;
	}

	return result;
}

string solve(vector<string> &lists)
{
	ldouble convLog = log10((long double)26);
	ldouble maxCan = 0.0;
	string candi = "";
	vector<pair<int, int>> counts;

	sort(lists.begin(), lists.end());

	for(int i = 0; i < lists.size(); i++)
	{
		counts.push_back(count(lists[i]));
	}

	for(int i = 0; i < counts.size(); i++)
	{
		ldouble value = (ldouble)counts[i].first * convLog + (ldouble)counts[i].second;
		if(value > maxCan)
		{
			maxCan = value;
			candi = lists[i];
		}
	}

	return candi;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;
	string str;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<string> lists;
		string candi;

		cin >> n;
		
		for(int i = 0; i < n; i++)
		{
			cin >> str;
			lists.push_back(str);
		}

		cout << solve(lists) << endl;
	}

	return 0;
}
