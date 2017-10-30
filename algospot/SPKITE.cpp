#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>

using namespace std;


bool equal(double a, double b)
{
	if(abs(a - b) < 0.0000001)
		return true;
	else
		return false;
}

struct vector3
{
	double x, y, z;

	explicit vector3(double x_ = 0, double y_ = 0, double z_ = 0) : x(x_), y(y_), z(z_) {}

	bool operator == (const vector3 &rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool operator < (const vector3 &rhs) const
	{
		if(x < rhs.x)
			return true;
		else if(x == rhs.x && y < rhs.y)
			return true;
		else if(x == rhs.x && y == rhs.y && z < rhs.z)
			return true;
		return false;
	}

	vector3 operator + (const vector3 &rhs) const
	{
		return vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	vector3 operator - (const vector3 &rhs) const
	{
		return vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	vector3 operator * (double rhs) const
	{
		return vector3(x * rhs, y * rhs, z * rhs);
	}

	double norm() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	
	vector3 normalize() const
	{
		return vector3(x / norm(), y / norm(), z / norm());
	}

	double dot(const vector3 &rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	vector3 project(const vector3 &rhs) const
	{
		vector3 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

vector3 perpendicularFoot(vector3 p, vector3 a, vector3 b)
{
	return a + (p - a).project(b - a);
}

double pointToLine(vector3 p, vector3 a, vector3 b)
{
	vector3 f = perpendicularFoot(p, a, b);
	if(equal((f - a).norm() + (f - b).norm(), (a - b).norm()) == true)
		return (p - f).norm();
	else
		return min((p - a).norm(), (p - b).norm());
}


set<int> connectPlanets(vector<vector3> &planets, vector<vector3> places, double r)
{
	set<int> result;
	int n = planets.size(), m = places.size();
	
	for(int idxPlaces = 0; idxPlaces < m - 1; idxPlaces++)
	{
		vector<pair<double, int>> distances;
		for(int idxPlanet = 0; idxPlanet < n; idxPlanet++)
		{
			pair<double, int> current;
			current.first = pointToLine(planets[idxPlanet], places[idxPlaces], places[idxPlaces + 1]);
			current.second = idxPlanet + 1;
			distances.push_back(current);
		}
		sort(distances.begin(), distances.end());

		for(int idxDist = 0; idxDist < n; idxDist++)
		{
			if(distances[idxDist].first > r)
				break;
			if(idxDist > 0 && equal(distances[idxDist].first, distances[idxDist - 1].first) == false)
				break;
			if(result.find(distances[idxDist].second) == result.end())
				result.insert(distances[idxDist].second);
		}
	}
		
	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m, r, d;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<vector3> planets, places;
		set<int> connects;
		cin >> n >> m >> r >> d;
		m++;
		r += d + r;

		for(int idx = 0; idx < n; idx++)
		{
			vector3 tr;
			cin >> tr.x >> tr.y >> tr.z;
			planets.push_back(tr);
		}
		
		for(int idx = 0; idx < m; idx++)
		{
			vector3 tr;
			cin >> tr.x >> tr.y >> tr.z;
			places.push_back(tr);
		}
		
		connects = connectPlanets(planets, places, (double)(r));

		cout << connects.size() << " ";
		for(set<int>::iterator it = connects.begin(); it != connects.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	return 0;
}

/*
2
4 2 1 1
6 5 1
6 1 1
2 5 1
9 1 1
1 3 1
8 3 1
8 5 1
4 1 1 1
6 5 1
6 1 1
2 5 1
9 1 1
2 3 1
9 3 1
*/
/*
2
4 2 1 1
1 6 5
1 6 1
1 2 5
1 9 1
1 1 3
1 8 3
1 8 5
4 1 1 1
6 5 1
6 1 1
2 5 1
9 1 1
2 3 1
9 3 1
*/
/*
1
4 1 1 1
6 5 1
6 1 1
2 5 1
9 1 1
2 3 1
9 3 1
*/
