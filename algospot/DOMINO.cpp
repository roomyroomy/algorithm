/*
   Domino[n] = Domino[n - 1] + n * (n + 1) + n * (n + 1) / 2
             = Domino[n - 1] + (3 * n^2 + 3 * n) / 2
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);

	int n;
	cin >> n;

	vector<int> domino(n + 1, 0);

	for(int idx = 1; idx <= n; idx++)
		domino[idx] = domino[idx - 1] + (3 * idx * idx + 3 * idx) / 2;

	cout << domino[n] << endl;

	return 0;
}

