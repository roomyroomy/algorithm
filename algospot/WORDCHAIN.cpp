/*
sample input:
3
4
dog
god
dragon
need
3
aa
ab
bb
2
ab
cd

sample output:
need dog god dragon
aa ab bb
IMPOSSIBLE
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class node;

int C, N;
vector<node> graph(27);
vector<string> resultWords;
vector<int> resultPath;

class node {
public:
	int inDegree;
	int outDegree;
	vector<pair<string, bool>> edgeList;

	node()
	{
	}
};

void init()
{
	for(int idxNode = 0; idxNode < 27; idxNode++)
	{
		graph[idxNode].edgeList.clear();
		graph[idxNode].inDegree = 0;
		graph[idxNode].outDegree = 0;
	}

	resultWords.clear();
	resultPath.clear();
}

int getStartIndex()
{
	int inDegreeMoreCount = 0;
	int outDegreeMoreCount = 0;
	int startIndex = -1;

	for(char idxNode = 0; idxNode < 27; idxNode++)
	{
		if(startIndex == -1 && graph[idxNode].outDegree >= 1)
			startIndex = idxNode;

		if(graph[idxNode].inDegree + 1 == graph[idxNode].outDegree)
		{
			startIndex = idxNode;
			inDegreeMoreCount++;
		}
		else if(graph[idxNode].outDegree + 1 == graph[idxNode].inDegree)
		{
			outDegreeMoreCount++;
		}
		else if(graph[idxNode].outDegree != graph[idxNode].inDegree)
		{
			return -1;
		}
	}

	if(inDegreeMoreCount > 1 || outDegreeMoreCount > 1)
		return -1;

	return startIndex;
}

bool dfs(int start)
{
	if(resultPath.size() == N)
	{
		resultPath.push_back(start);
		return true;
	}

	for(vector<pair<string, bool>>::iterator it = graph[start].edgeList.begin(); it != graph[start].edgeList.end(); it++)
	{
		if(it->second == false)
		{
			it->second = true;
			dfs(it->first.back() - 'a');
		}
	}

	resultPath.push_back(start);
	
	return false;
}

void makePath()
{
	int length = resultPath.size();

	for(int idxAlpha = 0; idxAlpha < 27; idxAlpha++)
	{
		for(vector<pair<string, bool>>::iterator it = graph[idxAlpha].edgeList.begin(); it != graph[idxAlpha].edgeList.end(); it++)
		{
			it->second = false;
		}
	}

	for(int idxPath = length - 1; idxPath > 0; idxPath--)
	{
		int startLetter = resultPath[idxPath];
		int endLetter = resultPath[idxPath - 1];

		for(vector<pair<string, bool>>::iterator it = graph[startLetter].edgeList.begin(); it != graph[startLetter].edgeList.end(); it++)
		{
			if(it->second == false && it->first.back() == endLetter + 'a')
			{
				it->second = true;
				resultWords.push_back(it->first);
				break;
			}
		}
	}
}

int main()
{
	cin >> C;

	for(int idxCase = 0; idxCase < C; idxCase++)
	{
		cin >> N;
		init();
		for(int idxWord = 0; idxWord < N; idxWord++)
		{
			string str;
			char first, last;
			cin >> str;
			first = str.front();
			last = str.back();

			graph[first - 'a'].edgeList.push_back(make_pair(str, false));
			graph[first - 'a'].outDegree++;
			graph[last - 'a'].inDegree++;
		}

		char startIndex = getStartIndex();

		if(startIndex != -1)
		{
			dfs(startIndex);
			makePath();
			for(vector<string>::iterator it = resultWords.begin(); it != resultWords.end(); it++)
			{
				cout << *it << " ";
			}
			cout << endl;
		}
		else
		{
			cout << "IMPOSSIBLE" << endl;
		}
	}

	return 0;
}
