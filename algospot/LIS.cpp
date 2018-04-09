#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

int solve(vector<int> &nums)
{
	vector<int> table(nums.size(), 1);
	int result = 0;

	for(int i = 1; i < nums.size(); i++)
	{
		for(int k = 0; k < i; k++)
		{
			if(nums[k] < nums[i])
				table[i] = max(table[i], table[k] + 1);
		}
	}

	for(int i = 0; i < table.size(); i++)
	{
		result = max(result, table[i]);
	}

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> nums;
		cin >> n;
		nums.assign(n, 0);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		cout << solve(nums) << endl;
	}

	return 0;
}
