#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

string isPdna(vector<string> &dna, vector<int> &order)
{
	string s;
	int low, high;

	for(int idx = 0; idx < dna.size(); idx++)
		s += dna[order[idx]];

	low = 0, high = s.length() - 1;

	while(low < high)
	{
		if(s[low] != s[high])
			return "";
		low++; high--;
	}

	return s;
}

string pdna(vector<string> &dna)
{
	int n = dna.size();
	string result = "";
	vector<int> order;

	for(int idx = 0; idx < n; idx++)
		order.push_back(idx);

	do
	{
		string current = isPdna(dna, order);
		if(current.length() > 0)
		{
			if(result > current || result.length() == 0)
			{
				result = current;
			}
		}	
	} while (next_permutation(order.begin(), order.end()));

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		string str;
		int sumLength = 0;
		vector<string> dna;
		cin >> n;
		for(int idxStr = 0; idxStr < n ; idxStr++)
		{
			cin >> str;
			dna.push_back(str);
		}

		sort(dna.begin(), dna.end());

		cout << pdna(dna) << endl;
	}

	return 0;
}
