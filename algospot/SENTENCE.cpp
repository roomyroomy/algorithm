#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


bool binarySearch(vector<string> names, string value)
{
	int size = names.size();
    int first = 0, last = size - 1, middle, position = -1;
    bool found = false;

    while (!found && first <= last)
    {
        middle = (first + last) / 2;
		if (names[middle].substr(0, value.size()) == value)
        {
            found = true;
            position = middle;
        }
        else if (names[middle] > value)
            last = middle - 1;
        else
            first = middle + 1;
    }

    return found;
}

int main()
{
	int m, n;
	int result = 0;
	string str;
	vector<string> dictionary, sentence;

	cin >> m >> n;
	getline(cin, str);
	for(int idxDic = 0; idxDic < m; idxDic++)
	{
		getline(cin, str);
		dictionary.push_back(str);
	}
	sort(dictionary.begin(), dictionary.end());

	for(int idxSen = 0; idxSen < n; idxSen++)
	{
		getline(cin, str);
		if(binarySearch(dictionary, str) == true)
			result++;
	}

	cout << result << endl;

	return 0;
}
