#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


bool isPalin(string &str)
{
	int front = 0, rear = str.size() - 1;

	while(rear > front)
	{
		if(str[front] != str[rear])
			return false;
		front++; rear--;
	}

	return true;
}

bool isSeti(string &str)
{
	string local = "";
	int last = -1, check = 0;
	
	while(check < (int)(str.size()) && last < (int)(str.size()))
	{
		if(local.size() > 1 && local.size() % 2 == 0 && isPalin(local) == true)
		{
			last = check - 1;
			local = "";
		}
		else
		{
			local += str[check];
			check++;
		}
	}

	return (local.size() > 1 && local.size() % 2 == 0 && isPalin(local) == true);
}

bool isAlien(string &str, int digits, vector<int> &g, int depth = 0)
{
	if(digits == depth)
	{
		string deStr = "";
		for(int idx = 0; idx < str.size(); idx++)
		{
			deStr += ((str[idx] - 'a') + g[idx % g.size()]) % 4 + 'a';
		}

		return isSeti(deStr);
	}

	for(int d = 0; d <= 3; d++)
	{
		g.push_back(d);
		if(isAlien(str, digits, g, depth + 1) == true)
			return true;
		g.pop_back();
	}

	return false;
}

string solve(string &str)
{	
	for(int d = 1; d <= 4; d++)
	{
		vector<int> v;
		if(isAlien(str, d, v) == true)
			return "Alien!";
	}

	return "noise";
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		string str;
		cin >> str;
		cout << solve(str) << endl;
	}

	return 0;
}
