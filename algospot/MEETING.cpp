#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int T, N;
	vector<int> manList;
	vector<int> womanList;

	cin >> T;
	for(int idxCase = 0; idxCase < T; idxCase++)
	{
		int sumMan = 0, sumWoman = 0, weight = 0, result = 0;
		cin >> N;

		manList.clear();
		womanList.clear();

		for(int idxMan = 0; idxMan < N; idxMan++)
		{
			cin >> weight;
			manList.push_back(weight);
		}
		for(int idxWoman = 0; idxWoman < N; idxWoman++)
		{
			cin >> weight;
			womanList.push_back(weight);
		}

		sort(manList.begin(), manList.end());
		sort(womanList.begin(), womanList.end());

		for(int idxCouple = 0; idxCouple < N; idxCouple++)
		{
			result += abs(manList[idxCouple] - womanList[idxCouple]);
		}

		cout << result << endl;
	}

	return 0;
}
