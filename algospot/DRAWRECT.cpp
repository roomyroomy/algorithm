#include <iostream>
#include <set>

using namespace std;

int T;
set<int> pointX;
set<int> pointY;

int main()
{
	cin >> T;

	for(int idxTest = 0; idxTest < T; idxTest++)
	{
		set<int>::iterator it;

		pointX.clear();
		pointY.clear();

		for(int idxPoint = 0; idxPoint < 3; idxPoint++)
		{
			int x, y;
			cin >> x >> y;
			it = pointX.find(x);
			if(it != pointX.end())
				pointX.erase(*it);
			else
				pointX.insert(x);

			it = pointY.find(y);
			if(it != pointY.end())
				pointY.erase(*it);
			else
				pointY.insert(y);
		}
		set<int>::iterator valueX = pointX.begin();
		set<int>::iterator valueY = pointY.begin();

		cout << *valueX << " " << *valueY << endl;
	}

	return 0;
}
