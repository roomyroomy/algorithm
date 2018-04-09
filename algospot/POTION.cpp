#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

inline int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

vector<int> solve(vector<pair<int, int>> &potions)
{
	vector<int> result(potions.size(), 0);
	int g = potions[0].first;
	int m = 0;
	
	for(int i = 0; i < potions.size(); i++)
		g = gcd(g, potions[i].first);

	for(int i = 0; i < potions.size(); i++)
	{
		int d = potions[i].second / (potions[i].first / g);
		if(potions[i].second % (potions[i].first / g) > 0)
			d++;
		if(d > m)
			m = d;
	}

	for(int i = 0; i < potions.size(); i++)
	{
		int d = (potions[i].first / g * m) - potions[i].second;
		result[i] = max(0, d);
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<pair<int, int>> potions;
		cin >> n;
		potions.assign(n, make_pair(0, 0));
		for(int i = 0; i < n; i++)
			cin >> potions[i].first;
		for(int i = 0; i < n; i++)
			cin >> potions[i].second;

		vector<int> result = solve(potions);
		for(int i = 0; i < n; i++)
			cout << result[i] << " ";
		cout << endl;
	}

	return 0;
}
