#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;

map<string, int> weeks;
map<int, int> months;

void init()
{
	weeks.insert(make_pair("Sunday", 0));
	weeks.insert(make_pair("Monday", 1));
	weeks.insert(make_pair("Tuesday", 2));
	weeks.insert(make_pair("Wednesday", 3));
	weeks.insert(make_pair("Thursday", 4));
	weeks.insert(make_pair("Friday", 5));
	weeks.insert(make_pair("Saturday", 6));

	months.insert(make_pair(1, 31));
	months.insert(make_pair(2, 28));
	months.insert(make_pair(3, 31));
	months.insert(make_pair(4, 30));
	months.insert(make_pair(5, 31));
	months.insert(make_pair(6, 30));
	months.insert(make_pair(7, 31));
	months.insert(make_pair(8, 31));
	months.insert(make_pair(9, 30));
	months.insert(make_pair(10, 31));
	months.insert(make_pair(11, 30));
	months.insert(make_pair(12, 31));
}

void solve(int m, int d, string s)
{
	vector<int> days(7, 0);
	int pos = weeks.find(s)->second;
	int dd = d;
	int totalDay = months.find(m)->second;
	int prevM = m - 1;
	if(prevM <= 0)
		prevM += 12;

	days[pos] = dd;
	for(int i = pos - 1; i >= 0; i--)
	{
		dd--;
		if(dd <= 0)
			dd = months.find(prevM)->second;
		days[i] = dd;
	}

	dd = d;
	for(int i = pos + 1; i < 7; i++)
	{
		dd++;
		if(dd > totalDay)
			dd = 1;
		days[i] = dd;
	}

	for(int i = 0; i < days.size(); i++)
		cout << days[i] << " ";
	cout << endl;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, m, d;
	string s;

	init();
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> m >> d >> s;
		solve(m, d, s);
	}

	return 0;
}
