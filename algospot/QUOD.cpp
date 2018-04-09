#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

inline bool inBound(int r, int c)
{
	if(r >= 0 && r < 11 && c >= 0 && c < 11)
		return true;
	return false;
}

string solve(vector<vector<char>> &boards)
{
	string result = "";

	for(int r1 = 0; r1 < 11; r1++)
	{
		for(int c1 = 0; c1 < 11; c1++)
		{
			for(int r2 = r1; r2 < 11; r2++)
			{
				int point = 0;
				if(r1 == r2)
					point = c1 + 1;

				for(int c2 = point; c2 < 11; c2++)
				{
					if(boards[r1][c1] == boards[r2][c2])
					{
						char item = boards[r1][c1];
						if(item == 'B' || item == 'R')
						{
							int dr = r2 - r1;
							int dc = c2 - c1;
							int nr1 = r1 - dc;
							int nc1 = c1 + dr;
							int nr2 = r2 - dc;
							int nc2 = c2 + dr;

							if(inBound(nr1, nc1) && inBound(nr2, nc2) && boards[nr1][nc1] == item && boards[nr2][nc2] == item)
							{
								if(item == 'B')
									return "Blue";
								else if(item == 'R')
									return "Red";
							}
						}
					}
				}
			}
		}
	}

	return "No squares";
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		string str;
		vector<vector<char>> boards(11, vector<char>(11, '.'));
		for(int i = 0; i < 11; i++)
		{
			cin >> str;
			for(int s = 0; s < 11; s++)
			{
				boards[i][s] = str[s];
			}
		}
		cout << solve(boards) << endl;
	}

	return 0;
}
