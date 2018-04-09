#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

const int modular = 1000000007;

vector<int> makeTable()
{
	vector<int> result(101, 0);
	result[0] = result[1] = 1;
	result[2] = 2;

	for(int i = 3; i <= 100; i++)
		result[i] = (result[i - 1] + result[i - 2]) % 1000000007;

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;
	vector<int> table = makeTable();

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n;
		cout << table[n] << endl;
	}

	return 0;
}
