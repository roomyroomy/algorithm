#include <iostream>
#include <string>
#include <list>

using namespace std;

bool isPair(char left, char right);
bool checkValidation(string &str);


bool isPair(char left, char right)
{
	if(left == '{' && right == '}')
		return true;
	else if(left == '(' && right == ')')
		return true;
	else if(left == '[' && right == ']')
		return true;
	else
		return false;
}

bool checkValidation(string &str)
{
	int length = str.length();
	list<char> validStack;

	validStack.push_back(str.at(0));

	for(int idx = 1; idx < length; idx++)
	{
		if(validStack.size() > 0 && isPair(validStack.back(), str.at(idx)))
		{
			validStack.pop_back();
		}
		else
		{
			char ch = str.at(idx);

			if (ch != '{' && ch != '(' && ch != '[')
				return false;

			validStack.push_back(ch);
		}
	}

	if(validStack.size() <= 0)
		return true;
	else
		return false;
}

int main()
{
	int C;
	string str;

	cin >> C;
	getline(cin, str);

	for (int idx = 0; idx < C; idx++)
	{
		getline(cin, str);

		if(checkValidation(str) == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
