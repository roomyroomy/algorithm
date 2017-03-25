#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void outputOftenPrefix(vector<string> &wordList, int maxStrLength)
{
	vector<pair<string, int>> accumCountList(maxStrLength);
	vector<pair<string, int>> maxCountList(maxStrLength);
	
	for(vector<string>::iterator strCurrent = wordList.begin(); strCurrent != wordList.end(); strCurrent++)
	{
		for(int idxWord = 0; idxWord < maxStrLength; idxWord++)
		{
			if(idxWord > strCurrent->length() - 1)
			{
				accumCountList[idxWord] = make_pair("", 0);
			}
			else
			{
				string strCurrentSub = strCurrent->substr(0, idxWord + 1);
				if(strCurrentSub.compare(accumCountList[idxWord].first) == 0)
				{
					accumCountList[idxWord].second++;
				}
				else
				{
					accumCountList[idxWord].first = strCurrentSub;
					accumCountList[idxWord].second = 1;
				}
			}

			if(accumCountList[idxWord].second > maxCountList[idxWord].second)
			{
				maxCountList[idxWord] = accumCountList[idxWord];
			}
		}
	}

	for(vector<pair<string, int>>::iterator countList = maxCountList.begin(); countList != maxCountList.end(); countList++)
	{
		cout << countList->first << endl;
	}
}

int main()
{
	int C, N, M;

	cin >> C;
	while(C-- > 0)
	{
		vector<string> wordList;
		string strWord;
		cin >> N >> M;
		for(int idxWord = 0; idxWord < N; idxWord++)
		{
			int length = 0;
			cin >> strWord;
			wordList.push_back(strWord);
		}
		sort(wordList.begin(), wordList.end());
		outputOftenPrefix(wordList, M);
	}

	return 0;
}
