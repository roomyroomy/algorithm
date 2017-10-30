#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

struct Comparator
{
	vector<int> &group;
	int t;
	Comparator(vector<int> &_group, int _t): group(_group), t(_t)
	{
		group = _group;
		t = _t;
	}
	bool operator() (int a, int b)
	{
		if(group[a] != group[b])
			return group[a] < group[b];
		else
			return group[a + t] < group[b + t];
	}
};

vector<int> getSuffixArray(const string &s)
{
	int n = s.size();

	int t = 1;
	vector<int> group(n + 1);

	for(int i = 0; i < n; i++)
		group[i] = s[i];
	group[n] = -1;

	vector<int> perm(n);

	for(int i = 0; i < n; i++)
		perm[i] = i;

	while(t < n)
	{
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);

		t *= 2;
		if(t >= n)
			break;

		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;

		for(int i = 1; i < n; i++)
		{
			if(compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		}

		group = newGroup;
	}

	return perm;
}


vector<int> getLcp(string &str, vector<int> &suffixArray)
{
    int strLength = str.length(), k = 0;
    vector<int> resultLcp(strLength, 0);
    vector<int> rank(strLength, 0);

    for(int idx = 0; idx < strLength; idx++)
		rank[suffixArray[idx]] = idx;

    for(int idx = 0; idx < strLength; idx++, k ? k-- : 0)
    {
        if(rank[idx] == strLength - 1)
		{
			k=0;
			continue;
		}
        int j = suffixArray[rank[idx] + 1];
        while(idx + k < strLength && j + k < strLength && str[idx + k] == str[j + k])
			k++;
        resultLcp[rank[idx]] = k;
    }
    return resultLcp;
}

int subStrCount(string strWord, int minAcceptedCount)
{
	int strLength = strWord.length();
	vector<string> wordList;
	vector<int> suffixArray;
	vector<int> lcp;
	multiset<int> boundaryLcpSet;
	int resultCount = 0;

	if(minAcceptedCount <= 1)
	{
		return strLength;
	}

	for(int idxWord = 0; idxWord < strLength; idxWord++)
	{
		suffixArray.push_back(idxWord);
	}

	suffixArray = getSuffixArray(strWord);
	lcp = getLcp(strWord, suffixArray);
	
	for(int idx = 0; idx < minAcceptedCount - 1; idx++)
	{
		boundaryLcpSet.insert(lcp[idx]);
	}

	resultCount = *(boundaryLcpSet.begin());

	for(int idx = minAcceptedCount - 1; idx < strLength; idx++)
	{
		int currentMin = 0;
		boundaryLcpSet.insert(lcp[idx]);
		std::multiset<int>::iterator it = boundaryLcpSet.find(lcp[idx - minAcceptedCount + 1]);
		boundaryLcpSet.erase(it);
		currentMin = *(boundaryLcpSet.begin());
		if(currentMin > resultCount)
			resultCount = currentMin;
	}

	return resultCount;
}

//#include <time.h>
int main()
{
    //clock_t begin, end;
    //begin = clock();  

	int c, k;

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		string strWord;

		cin >> k;
		cin >> strWord;

		cout << subStrCount(strWord, k) << endl;
	}

	//end = clock();
    //cout<<"Elasped Time : "<<(end-begin)<<endl;

	return 0;
}
