#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


double calc(vector<double> &equation, double x)
{
	double result = 0.0;
	int n = equation.size();

	for(int idx = 0; idx < n; idx++)
	{
		result += pow(x, (n - idx - 1));
	}

	return result;
}

double solve(vector<double> &equation)
{
	double result = 0.0, low = -10.0, high = 10.0;

	double aaa = calc(equation, low);
	double bbb = calc(equation, high);

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<double> equation;

		cin >> n;
		for(int idxVal = 0; idxVal < n  + 1; idxVal++)
		{
			double d;
			cin >> d;
			equation.push_back(d);
		}
		
		cout << solve(equation) << endl;
	}

	return 0;
}

/*
2
3
1.00 -6.00 11.00 -6.00
2
1.00 -12.50 31.50
*/