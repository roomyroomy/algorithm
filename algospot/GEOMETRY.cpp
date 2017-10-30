#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

typedef struct point {
	double x, y;
} Point;

double area(Point p, Point a, Point b)
{
	double result = 0;
	result += a.x * b.y;
	result -= b.x * a.y;
	result += b.x * p.y;
	result -= p.x * b.y;
	result += p.x * a.y;
	result -= a.x * p.y;
    return abs(result);
}

double solve(vector<Point> &points)
{
	vector<double> areas(points.size(), 0.0);
	double result = 0.0;
	int tcount = 0, count = 0;

	for(int a = 0; a < points.size(); a++)
	{
		for(int b = a + 1; b < points.size(); b++)
		{
			for(int c = b + 1; c < points.size(); c++)
			{
				double abc = area(points[a], points[b], points[c]);
				areas[a] += abc;
				areas[b] += abc;
				areas[c] += abc;

				if(a == 0)
					count ++;

				result += abc;
				tcount++;
			}
		}
	}

	double maxValue = 0.0;
	int maxIndex = -1;
	for(int idx = 0; idx < areas.size(); idx++)
	{
		if(areas[idx] > maxValue)
		{
			maxValue = areas[idx];
			maxIndex = idx;
		}
	}

	result -= maxValue;
	result /= (tcount - count);

	return result / 2;
}

double solve2(vector<Point> &points)
{
	vector<double> areas(points.size(), 0.0);
	double result = 0.0;
	int tcount = 0, count = 0;

	double temp = 0;
	for(int p = 0; p < points.size(); p++)
	{
		for(int q = 1; q < points.size() - 1; q++)
		{
			int a = p;
			int b = (p + q) % points.size();
			int c = (p + q + 1) % points.size();

			double abc = area(points[a], points[b], points[c]);

			areas[a] += abc;
			areas[b] += abc;
			areas[c] += abc;

			if(a == 0)
				count ++;

			result += abc;
			tcount++;
		}
	}

	for(int p = 0; p < points.size(); p++)
	{
		int a = p;
		int b = (p + 1) % points.size();
		int c = (p + 2) % points.size();

		double abc = area(points[a], points[b], points[c]);

		areas[a] -= abc;
		areas[b] -= abc;
		areas[c] -= abc;

		if(a == 0)
			count--;

		result -= abc;
		tcount--;
	}

	double maxValue = 0.0;
	int maxIndex = -1;
	for(int idx = 0; idx < areas.size(); idx++)
	{
		if(areas[idx] > maxValue)
		{
			maxValue = areas[idx];
			maxIndex = idx;
		}
	}

	result -= maxValue;
	result /= (tcount - count);

	return result;
}


int main()
{
	std::ios::sync_with_stdio(false);
	cout << fixed << setprecision(5) << endl;

	int tc, n;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<Point> points;
		cin >> n;
		for(int idx = 0; idx < n; idx++)
		{
			Point p;
			cin >> p.x >> p.y;
			points.push_back(p);
		}

		cout << solve(points) << endl;
		cout << solve2(points) << endl;
	}

	return 0;
}

/*
2
6
-4 -8
8 -6
8 -3
2 9
-10 0
-10 -6
5
-4 -8
8 -6
8 5
-4 9
-9 1
*/
