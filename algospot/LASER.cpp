#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>

using namespace std;

const double INF = 99999999.0;

double round(double value, int pos)
{
      double temp;
      temp = value * pow((double)10, (double)pos);
      temp = floor(temp + 0.5);
      temp *= pow((double)10, (double)-pos);
      return temp;
} 

pair<double, double> calcEquation(pair<double, double> pointA, pair<double, double> pointB)
{
	// y = ax + b 에서 a와 b를 리턴 함
	double x1 = pointA.first, y1 = pointA.second, x2 = pointB.first, y2 = pointB.second;
	double a = (y2 - y1) / (x2 - x1);
	double b = (x2 * y1 - x1 * y2) / (x2 - x1);

	if((x2 - x1) != 0.0)
	{
		a = (y2 - y1) / (x2 - x1);
		b = (x2 * y1 - x1 * y2) / (x2 - x1);
	}
	else
	{
		a = INF;
		b = x2;
	}

	return make_pair(round(a, 6), round(b, 6));
}

bool compareV(pair<pair<double, double>, int> A, pair<pair<double, double>, int> B)
{
	if(A.first < B.first)
		return true;
	else if(A.first == B.first && A.second < B.second)
		return true;
	return false;
}

int solve(vector<pair<double, double>> &points)
{
	int result = 0;
	int size = points.size();
	vector<pair<pair<double, double>, int>> equations;
	set<int> linePoints;

	for(int p = 0; p < size; p++)
	{
		for(int q = p + 1; q < size; q++)
		{
			pair<double, double> eq = calcEquation(points[p], points[q]);
			equations.push_back(make_pair(eq, p));
			equations.push_back(make_pair(eq, q));
		}
	}

	sort(equations.begin(), equations.end(), compareV);

	for(int idx = 0; idx < equations.size(); idx++)
	{
		linePoints.insert(equations[idx].second);
		if(idx == equations.size() - 1 || equations[idx].first != equations[idx + 1].first)
		{
			if(linePoints.size() >= 5)
				result++;
			linePoints.clear();
		}
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
		vector<pair<double, double>> points;
		cin >> n;

		points.assign(n, make_pair(0.0, 0.0));
		for(int idxPoint = 0; idxPoint < n; idxPoint++)
			cin >> points[idxPoint].first >> points[idxPoint].second;

		cout << solve(points) << endl;
	}

	return 0;
}
