#include <iostream>

using namespace std;

int main()
{
	int T, W;

	cin >> T;
	for(int idxTest = 0; idxTest < T; idxTest++)
	{
		int total = 0;
		cin >> W;
		for(int idxHour = 0; idxHour < 9; idxHour++)
		{
			int num;
			cin >> num;
			total += num;
		}

		if(W >= total)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
