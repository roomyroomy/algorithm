#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int modNum = 1000000007;

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, m, c;

	cin >> tc;

	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> coins, caseNum;
		cin >> m >> c;

		caseNum.assign(m + 1, 0);
		for(int idxCoin = 0; idxCoin < c; idxCoin++)
		{
			int item;
			cin >> item;
			coins.push_back(item);
		}

		sort(coins.begin(), coins.end(), greater<int>());

		for(int idxCoin = 0; idxCoin < c; idxCoin++)
		{
			if(coins[idxCoin] <= m)
				caseNum[coins[idxCoin]]++;
			for(int idxCheck = coins[idxCoin]; idxCheck < m; idxCheck++)
			{
				int nextCheck = idxCheck + coins[idxCoin];
				if(nextCheck <= m)
				{
					caseNum[nextCheck] += caseNum[idxCheck];
					caseNum[nextCheck] %= modNum;
				}
			}
		}

		cout << caseNum[m] << endl;
	}

	return 0;
}
