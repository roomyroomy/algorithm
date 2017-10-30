#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

#define M_PI 3.14159265358979323846

using namespace std;

struct vector2
{
	double x;
	double y;

	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

inline double pointToPoint(vector2 a, vector2 b)
{
	double p = a.x - b.x;
	double q = a.y - b.y;
	return sqrt(p * p + q * q);
}

inline double pointToSegment(vector2 &p, vector2 & a, vector2 &b)
{
	double linelen = pointToPoint(a, b);
	double prj = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / linelen;

	if (linelen == 0)
		return pointToPoint(a, p);
	else if (prj < 0)
		return pointToPoint(a, p);
	else if (prj > linelen)
		return pointToPoint(b, p);
	else
		return fabs((-1) * (p.x - a.x) * (b.y - a.y) + (p.y - a.y) * (b.x - a.x)) / linelen;
}

double distancePolygons(vector<vector2> &polygonA, vector<vector2> &polygonB)
{
	double result = 999999999.0;

	for(int idxA = 0; idxA < polygonA.size(); idxA++)
	{
		vector2 start = polygonA[idxA];
		vector2 end = polygonA[(idxA + 1) % polygonA.size()];

		for(int idxB = 0; idxB < polygonB.size(); idxB++)
		{
			double dist = pointToSegment(polygonB[idxB], start, end);
			if(dist < result)
				result = dist;
		}
	}

	return result;
}

pair<int, int> solve(vector<vector<vector2>> &polygons, double &distance)
{
	pair<int, int> resultIdx;
	distance = 999999999.0;

	for(int idxA = 0; idxA < polygons.size(); idxA++)
	{
		for(int idxB = idxA + 1; idxB < polygons.size(); idxB++)
		{
			double dist = distancePolygons(polygons[idxA], polygons[idxB]);
			double dist2 = distancePolygons(polygons[idxB], polygons[idxA]);
			if(dist < distance)
			{
				distance = dist;
				resultIdx.first = idxA;
				resultIdx.second = idxB;
			}
			if(dist2 < distance)
			{
				distance = dist2;
				resultIdx.first = idxA;
				resultIdx.second = idxB;
			}
		}
	}

	return resultIdx;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, mi;

	cout << fixed << setprecision(2) << endl;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector<vector2>> polygons;
		double distance = 0.0;
		cin >> n;

		polygons.assign(n, vector<vector2>(0));
		for(int idxD = 0; idxD < n; idxD++)
		{
			cin >> mi;
			polygons[idxD].assign(mi, vector2(0.0, 0.0));
			for(int idxPoint = 0; idxPoint < mi; idxPoint++)
			{
				cin >> polygons[idxD][idxPoint].x >> polygons[idxD][idxPoint].y;
			}
		}

		pair<int, int> result = solve(polygons, distance);
		cout << result.first + 1 << " " << result.second + 1 << endl;
		cout << distance << endl;
	}

	return 0;
}
