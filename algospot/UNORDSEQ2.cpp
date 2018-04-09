#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


const int mod = 1000000009;


vector<int> makeSubset(int n)
{
	vector<int> table(n + 1, 0);

	table[1] = 1;
	for(int i = 2; i <= n ; i++)
	{
		table[i] = (table[i - 1] + 1) * 2 - 1;
		table[i] %= mod;
	}

	return table;
}

int calcSerial(vector<int> &nums, bool isIncrease)
{
	int n = nums.size();
	int result = 0;
	vector<int> values(n, 0);

	for(int i = 0; i < n; i++)
	{
		values[i] = 1;
		for(int j = 0; j < i; j++)
		{
			if(isIncrease == true && nums[j] <= nums[i])
			{
				values[i] += values[j];
				values[i] %= mod;
			}
			else if(isIncrease == false && nums[j] >= nums[i])
			{
				values[i] += values[j];
				values[i] %= mod;
			}
		}
	}

	for(int i = 0; i < n; i++)
	{
		result += values[i];
		result %= mod;
	}

	return result;
}

int calcSame(vector<int> &nums, vector<int> &subset)
{
	int result = 0;
	int n = nums.size();
	vector<int> often(1000001, 0);

	for(int i = 0; i < n; i++)
	{
		often[nums[i]]++;
	}

	for(int i = 0; i < often.size(); i++)
	{
		if(often[i] > 1)
		{
			result += subset[often[i]] - often[i];
			result %= mod;
		}
	}

	return result;
}

int solve(vector<int> &nums, vector<int> &subset)
{
	int result = 0;
	int n = nums.size();

	result += subset[n];
	result -= calcSerial(nums, true);
	result -= calcSerial(nums, false);
	result += n;
	result += calcSame(nums, subset);

	while(result < 0)
		result += mod;

	result %= mod;

	return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n;

	vector<int> subset = makeSubset(2000);

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> nums;
		cin >> n;
		nums.assign(n, 0);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		cout << solve(nums, subset) << endl;
	}

	return 0;
}
