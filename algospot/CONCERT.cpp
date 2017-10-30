#include <iostream>
#include <vector>
#include <queue>


using namespace std;


int findMaxVol(vector<int> &vols, int vs, int vm)
{
	int result = -1;
	int days = vols.size();
	pair<int, int> previous = make_pair(-1, -1);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;	// first일째에 second 볼륨이 존재한다는 의미
	
	que.push(make_pair(0, -vs));

	while(que.size() > 0)
	{
		pair<int, int> current = que.top();
		que.pop();
		if(days <= current.first)
		{
			result = -current.second;
			break;
		}
		if(previous == current)
			continue;
		else
			previous = current;

		int upVol = current.second - vols[current.first];
		int downVol = current.second + vols[current.first];

		if(upVol >= -vm)
			que.push(make_pair(current.first + 1, upVol));
		if(downVol <= 0)
			que.push(make_pair(current.first + 1, downVol));
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, vs, vm;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> vols;
		cin >> n >> vs >> vm;

		for(int idxSong = 0; idxSong < n; idxSong++)
		{
			int v;
			cin >> v;
			vols.push_back(v);
		}

		cout << findMaxVol(vols, vs, vm) << endl;
	}

	return 0;
}
