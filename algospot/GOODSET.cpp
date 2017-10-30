#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t, n, m;

	cin >> t;
	for(int idxCase = 0; idxCase < t; idxCase++)
	{
		vector<bool> questionList;
		bool result = true;
		int solvedCount = 0;

		cin >> n >> m;

		questionList.assign(m + 1, false);

		for(int idxPerson = 0; idxPerson < n; idxPerson++)
		{
			int x;
			cin >> x;

			for(int idxQuestion = 0; idxQuestion < x; idxQuestion++)
			{
				int q;
				cin >> q;
				if(questionList[q] == false)
				{
					questionList[q] = true;
					solvedCount++;
				}
			}

			if(x == m || x == 0)
				result = false;
		}

		if(solvedCount < m)
			result = false;

		if(result == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
