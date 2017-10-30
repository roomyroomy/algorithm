#include <iostream>
#include <math.h>

using namespace std;

typedef long long llong;

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	llong n, m, r0, c0, r, c, a, b;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n >> m >> r0 >> c0 >> r >> c >> a >> b;
		cout << (abs(r0 - r) + (a - 1)) / a + (abs(c0 - c) + (b - 1)) / b << endl;
	}

	return 0;
}
