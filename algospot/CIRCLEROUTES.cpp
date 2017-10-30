#include <iostream>
#include <string>

using namespace std;

class MMSS
{
public:
	int hour, min;

	MMSS()
	{
		hour = 0;
		min = 0;
	}

	MMSS(int h, int m)
	{
		hour = h;
		min = m;
	}

	MMSS operator - (MMSS o)
	{
		MMSS r;
		r.hour = hour - o.hour;
		r.min = min - o.min;
		if(r.min < 0)
		{
			r.min += 60;
			r.hour--;
		}
		return r;
	}

	static MMSS minimum(MMSS a, MMSS b)
	{
		if(a.hour < b.hour)
			return a;
		else if(a.hour == b.hour && a.min < b.min)
			return a;
		else
			return b;
	}
};

int solve(MMSS s, MMSS e, MMSS d, MMSS c)
{
	int result = 0;
	MMSS duration = e - s;
	duration.min++;
	c = MMSS::minimum(duration, c);
	int dmin = d.hour * 60 + d.min;
	int cmin = c.hour * 60 + c.min;
	result = cmin / dmin;
	if(cmin % dmin > 0)
		result++;
	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	MMSS s, e, d, c;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		string ss, ee, dd, cc;
		cin >> ss >> ee >> dd >> cc;
		s.hour = atoi(ss.substr(0, 2).c_str());
		s.min = atoi(ss.substr(3, 2).c_str());
		e.hour = atoi(ee.substr(0, 2).c_str());
		e.min = atoi(ee.substr(3, 2).c_str());
		d.hour = atoi(dd.substr(0, 2).c_str());
		d.min = atoi(dd.substr(3, 2).c_str());
		c.hour = atoi(cc.substr(0, 2).c_str());
		c.min = atoi(cc.substr(3, 2).c_str());

		cout << solve(s, e, d, c) << endl;
	}

	return 0;
}
