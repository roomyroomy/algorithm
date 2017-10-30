/*
1. n진수의 자연수에 대하여 p자리 숫자에 대해서 n ^ p개 만큼의 조합의 개수를 가진다. (10진수 4자리는 10 ^ 4 = 10000개)
2. 따라서, (a, b)에 대하여, n ^ a + n ^ (a + 1) + ... n ^ b 의 숫자를 구한다.
   (결국, n진수로 표현 시, 1111111000000 형태의 숫자를 구하라는 문제)
3. 하지만, (a, b)의 범위가 최대 100000000이므로, 직관적인 방법으로는 답을 구할 수 없고, 효율적인 방법이 필요하다.
4. n ^ 1, n ^ 2, n ^ 4, n ^ 8, ...과 같이 "2제곱수 자리"에 해당하는 값을 미리 계산해두면, 좀 더 빠른 시간안에 답을 구할 수 있다.
   예를 들어, n진수 100자리는 n을 100번 곱하는 것이 아니라, 미리 구해둔 n ^ 64, n ^ 32, n ^ 4를 곱하면 3번의 연산에 답을 구하게 된다.
5. (a, b) 범위에 대해서는, (0, b - a) 범위에 대한 전체 개수를 구한 뒤, n ^ a를 곱하면 된다.
*/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll modNum = 1000000007;


int getCombination(vector<int> table, int digit, int n)
{
	int remainDigit = digit;
	int currentDigitCombi = 1;
	int result = 1;
	vector<int>::iterator it = table.begin();

	while(it != table.end())
	{
		currentDigitCombi *= 2;
		it++;
	}

	it--;
	currentDigitCombi /= 2;
	while(remainDigit > 0)
	{
		if(remainDigit >= currentDigitCombi)
		{
			remainDigit -= currentDigitCombi;
			result = (int)(((ll)result * (ll)(*it)) % modNum);
		}
		else
		{
			it--;
			currentDigitCombi /= 2;
		}
	}

	return result;
}

int solve(int a, int b, int n)
{
	if(n == 1)
		return b - a + 1;

	vector<int> tableZero;	// table[k]는 2 ^ k 자리 수를 의미
	vector<int> tableOne;
	int maxDigit = 0, remainDigit = 0, currentDigit = 0;
	int diff = b - a;
	int result = 0;

	tableZero.push_back(n);
	tableOne.push_back(1);

	for(int k = 1, comp = 1; comp <= b; k++, comp *= 2)
	{
		ll nextValue = (ll)tableZero[k - 1] * (ll)tableZero[k - 1];
		ll nextSum = (ll)tableZero[k - 1] * (ll)tableOne[k - 1] + (ll)tableOne[k - 1];
		tableZero.push_back((int)(nextValue % modNum));
		tableOne.push_back((int)(nextSum % modNum));
		maxDigit = comp;
	}

	int num1 = 0;
	int num2 = getCombination(tableZero, a, n);

	currentDigit = maxDigit;
	remainDigit = b - a + 1;
	vector<int>::iterator it = tableOne.end();
	it -= 2;
	while(remainDigit > 0)
	{
		if(remainDigit >= currentDigit)
		{
			remainDigit -= currentDigit;
			num1 = (int)(((ll)num1 + (ll)(*it) * (ll)(getCombination(tableZero, remainDigit, n))) % modNum);
		}
		else
		{
			it--;
			currentDigit /= 2;
		}
	}

	result = (int)(((ll)num1 * (ll)num2) % modNum);

	return result;
}

int main()
{
	int tc, a, b, n;

	cin >> tc;

	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> a >> b >> n;
		cout << solve(a, b, n) << endl;
	}

	return 0;
}
