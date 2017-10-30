#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int N;
	vector<pair<int, string>> dataList;

	cin >> N;
	for(int idxItem = 0; idxItem < N; idxItem++)
	{
		int num;
		string str;

		cin >> num;
		cin >> str;

		dataList.push_back(make_pair(num, str.erase(num - 1, 1)));
	}

	for(int idxItem = 0; idxItem < N; idxItem++)
	{
		cout << idxItem + 1 << " " << dataList[idxItem].second << endl;
	}

	return 0;
}

