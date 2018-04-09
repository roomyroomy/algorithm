#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

struct {
	bool operator()(pair<int, int> i, pair<int, int> j)
	{
		return (i.second < j.second);
	}
} compare_second;

vector<int> solve(vector<int> &dolls, int m)
{ 
	vector<int> result;
	vector<pair<int, int>> sorted;
	vector<pair<int, int>> sortedResult;
	int remain = m, thresold = 0;

	for(int i = 0; i < dolls.size(); i++)
	{
		sorted.push_back(make_pair(i, dolls[i]));
	}

	sort(sorted.begin(), sorted.end(), compare_second);
	
	for(int p = 0; p < sorted.size(); p++)
	{
		int add = (sorted[p].second - thresold) * (sorted.size() - p);
		if(add <= remain)
		{
			thresold = sorted[p].second;
			remain -= add;
		}
		else
		{
			thresold += remain / (sorted.size() - p);
			remain %= (sorted.size() - p);
			break;
		}

		if(remain <= 0)
			break;
	}

	for(int p = 0; p < dolls.size(); p++)
	{
		sortedResult.push_back(make_pair(sorted[p].first, min(sorted[p].second, thresold)));
	}

	sort(sortedResult.begin(), sortedResult.end());

	for(int p = 0; p < dolls.size(); p++)
	{
		result.push_back(sortedResult[p].second);
		if(remain > 0 && sortedResult[p].second < dolls[p])
		{
			remain--;
			result[p]++;
		}
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> dolls;
		cin >> n >> m;
		dolls.assign(n, 0);
		for(int i = 0; i < n; i++)
			cin >> dolls[i];

		vector<int> result = solve(dolls, m);
		for(int i = 0; i < result.size(); i++)
			cout << result[i] << " ";
		cout << endl;
	}

	return 0;
}
