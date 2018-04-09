#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<string> slist;
		string str;
		cin >> str;

		for(int idx = 0; idx < str.size(); idx+=2)
		{
			string sp = str.substr(idx, 2);
			slist.push_back(sp);
		}

		sort(slist.begin(), slist.end());
		
		for(int idx = 0; idx < slist.size(); idx++)
		{
			cout << slist[idx];
		}
		cout << endl;
	}

	return 0;
}
