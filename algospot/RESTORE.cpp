/*
1. TSP2의 solution과 유사하게, DP를 이용한다. (Memoization)
2. S1이 S2의 substring일 경우, S2는 결과에 영향을 주지 않는다. 따라서 이러한 특징을 가지는 S2는 제거한다.
   (증명 : 만약 S2값이 결과에 영향을 준다면, 결과값은 S1 + alpha일 것이다. 하지만 이것은 문제에 주어진 명제에 어긋나므로 거짓)
3. 2번에서 처리된 스트링 리스트를 가지고, 각 string간의 접미/접두어 사이의 최대 길이를 구하고, table을 구성한다.
4. 3번에서 구한 table을 가지고 memoization을 수행한다.
5. memoization을 통해 생성되는 shortestTable은 아래와 같이 정의한다.
   shortestTable[a][b] = (f, s)
    - a : 마지막에 추가되어 있는 string의 index 값
	- b : 지금까지 추가된 string의 index값에 대한 bit flag
	- f : 가장 짧은 string 길이
	- s : 바로 다음 차례에 위치할 string의 index 값 (마지막에 추적을 통해 string을 출력하기 위한 목적)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> shortestTable;

bool comparator(string a, string b)
{
	return (a.length() > b.length());
}

vector<string> preprocessing(vector<string> &piece)
{
	vector<int> remove;
	vector<string> result;
	int size = piece.size();

	sort(piece.begin(), piece.end(), comparator);

	for(int idxA = 0; idxA < size; idxA++)
	{
		for(int idxB = idxA + 1; idxB < size; idxB++)
		{
			int lengthA = piece[idxA].length();
			int lengthB = piece[idxB].length();

			for(int idxComp = 0; idxComp < lengthA - lengthB + 1; idxComp++)
			{
				if(piece[idxA].substr(idxComp, lengthB).compare(piece[idxB]) == 0)
					remove.push_back(idxB);
			}
		}
	}

	for(vector<int>::iterator it = remove.begin(); it != remove.end(); it++)
		piece[*it] = "";

	for(vector<string>::iterator it = piece.begin(); it != piece.end(); it++)
		if(it->length() > 0)
			result.push_back(*it);

	return result;
}

int getCommonString(string s1, string s2)
{
	int diff = 0;
	int strLength = s1.length();

	for(int idxStr = 0; idxStr < strLength; idxStr++)
	{
		bool complete = true;
		string aaa = s1.substr(idxStr, strLength - idxStr);
		string bbb = s2.substr(0, strLength - idxStr);
		if(aaa.compare(bbb) == 0)
		{
			return strLength - idxStr;
		}
	}

	return 0;
}

vector<vector<int>> makeCommonStringTable(vector<string> &piece)
{
	int size = piece.size();
	vector<vector<int>> resultTable(size, vector<int>(size, 0));

	for(int here = 0; here < size; here++)
		for(int there = 0; there < size; there++)
			if(here != there)
				resultTable[here][there] = getCommonString(piece[here], piece[there]);

	return resultTable;
}

pair<int, int> shortestMerge(vector<string> &piece, vector<vector<int>> &table, int bitFlag = 0, int lastIdx = -1)
{
	int minResult = 99999999;
	pair<int, int> result;
	int size = piece.size();
	if(bitFlag == 0)
	{
		shortestTable.assign(size, vector<pair<int, int>>(1 << size, make_pair(0, 0)));
	}
	else if(shortestTable[lastIdx][bitFlag].first > 0)
		return shortestTable[lastIdx][bitFlag];
	else if(bitFlag == (1 << size) - 1)
	{
		shortestTable[lastIdx][bitFlag].first = piece[lastIdx].size();
		shortestTable[lastIdx][bitFlag].second = -1;
		return shortestTable[lastIdx][bitFlag];
	}

	for(int idxStr = 0; idxStr < size; idxStr++)
	{
		if((bitFlag & (1 << idxStr)) == 0)
		{
			bitFlag += (1 << idxStr);
			pair<int, int> subResult = shortestMerge(piece, table, bitFlag, idxStr);
			int subValue = subResult.first;
			if(lastIdx >= 0)
				subValue += piece[lastIdx].length() - table[lastIdx][idxStr];
			bitFlag -= (1 << idxStr);

			if(subValue < minResult)
			{
				minResult = subValue;
				result.first = minResult;
				result.second = idxStr;
			}
		}
	}

	if(lastIdx >= 0)
		shortestTable[lastIdx][bitFlag] = result;
	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<string> piece;
		vector<vector<int>> table;

		cin >> n;

		for(int idxStr = 0; idxStr < n; idxStr++)
		{
			string str;
			cin >> str;
			piece.push_back(str);
		}

		piece = preprocessing(piece);
		table = makeCommonStringTable(piece);
		pair<int, int> result = shortestMerge(piece, table);
		pair<int, int> currentPair = result;
		int previous = currentPair.second;
		int currentBitFlag = 0;

		cout << piece[previous];
		currentBitFlag = (1 << result.second);
		currentPair = shortestTable[result.second][currentBitFlag];
		while(currentPair.second >= 0)
		{
			int delLength = table[previous][currentPair.second];
			cout << piece[currentPair.second].substr(delLength, piece[currentPair.second].length() - delLength);
			previous = currentPair.second;
			currentBitFlag |= (1 << currentPair.second);
			currentPair = shortestTable[currentPair.second][currentBitFlag];
		}
		cout << endl;
	}

	return 0;
}

/*
5
3
geo
oji
jing
2
world
hello
3
abrac
cadabra
dabr
1
abcdefg
4
aaaaaaaaa
aaab
bbbbbb
aaaaaaa
*/



/*
3
15
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
15
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
15
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab
cadabracadabracadabracadabracadabracadab
racadabracadabradabracadabracadabracadab
abcdefgabcdefgabcdefgabcdefgabcdefgcadab

*/