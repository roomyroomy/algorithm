#include <iostream>
#include <algorithm>
#include <list>


using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, k;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		list<int> persons;
		cin >> n >> k;

		for(int idx = 1; idx <= n; idx++)
			persons.insert(persons.end(), 1, idx);

		list<int>::iterator it = persons.begin();

		it = persons.erase(it);
		for(int count = n - 1; count > 2; count--)
		{
			for(int iter = 0; iter < k - 1; iter++)
			{
				it++;
				if(it == persons.end())
					it = persons.begin();
			}

			it = persons.erase(it);
			if(it == persons.end())
				it = persons.begin();
		}

		cout << persons.front() << " " << persons.back() << endl;
	}

	return 0;
}
