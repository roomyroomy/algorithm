#include <iostream>

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, a, b;

	cin >> tc;

	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> a >> b;
		if(a > b)
			cout << 0 << endl;
		else
			cout << b - a + 4 << endl;
	}

	return 0;
}

