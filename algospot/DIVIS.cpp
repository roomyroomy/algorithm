#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string solve(string &str)
{
	int t = 0;
	for(int i = 0; i < str.size(); i++)
	{
		int value = 0;
		if(str[i] >= '0' && str[i] <= '9')
			value += (int)(str[i] - '0');
		else if(str[i] >= 'A' && str[i] <= 'Z')
			value += (int)(str[i] - 'A' + 10);
		else if(str[i] >= 'a' && str[i] <= 'z')
			value += (int)(str[i] - 'a' + 36);
		t += value;
	}

	if(t % 61 == 0)
		return "yes";
	else
		return "no";
}

int main()
{
	std::ios::sync_with_stdio(false);

	while(true)
	{
		string str;
		cin >> str;
		if(str.compare("end") == 0)
			break;
		cout << solve(str) << endl;
	}

	return 0;
}
