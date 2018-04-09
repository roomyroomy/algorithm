// 각 경우의 수에 대하여, o 또는 x가 연속된 경우 종료 조건임
// 현재 상태에 따라, 다음 상태를 찾아가며 DFS로 탐색.
// 상태 S[i]에 대하여, 다음 상태일 수 있는 S[j]에 대하여 아래와 같다.
//  S[j]의 값 중에서 하나라도 Lose라면 s[i] 상태는 Win 상태임
//  S[j]의 값 중에 Lose가 없고 하나 이상 Tie라면 S[i]는 Tie 상태 
//  나머지 케이스(S[j]가 모두 Win)에서는 S[i]는 Lose

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<vector<int>, int> wins;

int getState(vector<int> &table)
{
	int result = 0;
	for(int i = 0; i < 9; i++)
	{
		result += table[i];
		if(i < 8)
			result *= 3;
	}

	return result;
}

int isWin(vector<int> &table)
{
	if(table[0] == table[1] && table[1] == table[2])
		return table[0];
	else if(table[3] == table[4] && table[4] == table[5])
		return table[3];
	else if(table[6] == table[7] && table[7] == table[8])
		return table[6];
	else if(table[0] == table[3] && table[3] == table[6])
		return table[0];
	else if(table[1] == table[4] && table[4] == table[7])
		return table[1];
	else if(table[2] == table[5] && table[5] == table[8])
		return table[2];
	else if(table[0] == table[4] && table[4] == table[8])
		return table[0];
	else if(table[2] == table[4] && table[4] == table[6])
		return table[2];

	return 0;
}

// tie: 0, x: 1, o: 2
int runGame(vector<int> &table, int turn)
{
	int result = 0;
	int win = isWin(table);
	vector<int> counts(3, 0);
	auto it = wins.find(table);

	if(it != wins.end())
	{
		return it->second;
	}

	if(win == 1 || win == 2)
	{
		wins.insert(make_pair(table, win));
		return win;
	}
	else if(turn == table.size())
	{
		wins.insert(make_pair(table, 0));
		return 0;
	}

	for(int i = 0; i < 9; i++)
	{
		if(table[i] == 0)
		{
			table[i] = turn % 2 + 1;
			counts[runGame(table, turn + 1)]++;
			table[i] = 0;
		}
	}

	if(turn % 2 == 0)
	{
		// "X"
		if(counts[1] > 0)
			result = 1;
		else if(counts[0] > 0)
			result = 0;
		else
			result = 2;
	}
	else if(turn % 2 == 1)
	{
		// "O"
		if(counts[2] > 0)
			result = 2;
		else if(counts[0] > 0)
			result = 0;
		else
			result = 1;
	}

	wins.insert(make_pair(table, result));
	return result;
}

string solve(vector<int> &table, int turn)
{
	int winner = runGame(table, turn);

	if(winner == 1)
	{
		return "x";
	}
	else if(winner == 2)
	{
		return "o";
	}
	else
	{
		return "TIE";
	}
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	string str;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		int turn = 0;
		vector<int> table(9, 0);
		for(int r = 0; r < 3; r++)
		{
			cin >> str;
			for(int c = 0; c < 3; c++)
			{
				if(str[c] == '.')
					table[r * 3 + c] = 0;
				else if(str[c] == 'x')
					table[r * 3 + c] = 1;
				else if(str[c] == 'o')
					table[r * 3 + c] = 2;

				if(table[r * 3 + c] != 0)
					turn++;
			}
		}
		cout << solve(table, turn) << endl;
	}

	return 0;
}
