#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int INFINITY_INT = 2000000000;


pair<int, int> getMinMaxRect(vector<pair<int, int>> &pointList)
{
	int min = INFINITY_INT, max = 0;
	int length = pointList.size();
	int prevX = -1;
	vector<pair<int, vector<int>>> pointSet;

	sort(pointList.begin(), pointList.end());

	for(int idxPoint = 0; idxPoint < length; idxPoint++)
	{
		if(prevX != pointList[idxPoint].first) {
			vector<int> emptyVector;
			pointSet.push_back(make_pair(pointList[idxPoint].first, emptyVector));
			prevX = pointList[idxPoint].first;
		}
		pointSet.back().second.push_back(pointList[idxPoint].second);
	}

	for(int idxXaxis = 0; idxXaxis < pointSet.size(); idxXaxis++)
	{
		vector<int> vectorYList = pointSet[idxXaxis].second;
		int setLength = vectorYList.size();
		
		for(int idxPointA = 0; idxPointA < setLength - 1; idxPointA++)
		{
			for(int idxPointB = idxPointA + 1; idxPointB < setLength; idxPointB++)
			{
				int diff = vectorYList[idxPointB] - vectorYList[idxPointA];
				if(binary_search(pointList.begin(), pointList.end(), make_pair(pointSet[idxXaxis].first + diff, vectorYList[idxPointA]))
				   && binary_search(pointList.begin(), pointList.end(), make_pair(pointSet[idxXaxis].first + diff, vectorYList[idxPointB])))
				{
					if(diff > max)
						max = diff;
					if(diff < min)
						min = diff;
				}
			}
		}
	}

	return make_pair(min, max);
}

int main()
{
	int t;

	cin >> t;
	for(int idxCase = 0; idxCase < t; idxCase++)
	{
		vector<pair<int, int>> pointList;
		int n, x, y;

		cin >> n;

		for(int idxPoint = 0; idxPoint < n; idxPoint++)
		{
			cin >> x >> y;
			pointList.push_back(make_pair(x, y));
		}

		pair<int, int> minMax = getMinMaxRect(pointList);

		cout << minMax.first << " " << minMax.second << endl;
	}

	return 0;
}
