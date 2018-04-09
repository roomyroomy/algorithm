#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, i, j;
	string str;
	vector<int> nums;

	cin >> str;
	nums.push_back(0);

	for(int idx = 0; idx < str.size(); idx++)
	{
		nums.push_back(nums.back());
		if(str[idx] == '1')
			nums[nums.size() - 1]++;
	}

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> i >> j;
		if(i > j)
			swap(i, j);
		if(nums[j + 1] - nums[i] == 0 || nums[j + 1] - nums[i] == (j - i + 1))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}
