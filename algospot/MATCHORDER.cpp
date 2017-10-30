#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);

	int c, n;

	cin >> c;
	for(int idxCase = 0; idxCase < c ; idxCase++)
	{
		int avility;
		vector<int> avilityRussia, avilityKorea;
		cin >> n;
		for(int idxPerson = 0; idxPerson < n ; idxPerson++)
		{
			cin >> avility;
			avilityRussia.push_back(avility);
		}

		for(int idxPerson = 0; idxPerson < n ; idxPerson++)
		{
			cin >> avility;
			avilityKorea.push_back(avility);
		}

		sort(avilityRussia.begin(), avilityRussia.end());
		sort(avilityKorea.begin(), avilityKorea.end());

		vector<int>::iterator itRu = avilityRussia.begin();
		vector<int>::iterator itKo = avilityKorea.begin();
		int result = 0;

		while(itKo != avilityKorea.end() && itRu != avilityRussia.end())
		{
			while(itKo != avilityKorea.end() && *itRu > *itKo)
				itKo++;

			if(itKo != avilityKorea.end())
			{
				result++;
				itRu++;
				itKo++;
			}

			if(itRu == avilityRussia.end())
			{
				while(itKo != avilityKorea.end()) 
				{
					itKo++;
					result++;
				}
			}
		}

		cout << result << endl;
	}

	return 0;
}
