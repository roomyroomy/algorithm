#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

double solve(double m, double d, string &turn)
{
	vector<pair<double, double>> table(turn.size(), make_pair(0.0, 0.0));
	vector<double> prob(turn.size(), 0.0);
	double result = 0.0;

	for(int i = 0; i < turn.size(); i++)
	{
		if(i == 0)
			prob[i] = 1.0;
		else
			prob[i] = prob[i - 1] * d;
	}

	for(int i = turn.size() - 1; i >= 0; i--)
	{
		if(turn[i] == 'C')
		{
			if(i == turn.size() - 1)
			{
				table[i].first = prob[i];
				table[i].second = 0.0;
			}
			else
			{
				table[i].first = prob[i] - table[i + 1].second;
				table[i].second = table[i + 1].second;
			}
		}
		else if(turn[i] == 'U')
		{
			if(i == turn.size() - 1)
			{
				table[i].first = 0.0;
				table[i].second = prob[i];
			}
			else
			{
				table[i].first = table[i + 1].first;
				table[i].second = prob[i] - table[i + 1].first;
			}
		}
	}

	result = table[0].first;
	return result * m * (double)10000.0;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	double m, d;
	string turn;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> m >> d;
		cin >> turn;
		cout << setprecision(1) << fixed << solve(m, ((double)100.0 - d) / (double)100.0, turn) << endl;
	}

	return 0;
}
