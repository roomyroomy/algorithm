#include <iostream>
#include <string>

using namespace std;

int T;
int main()
{
	string str;
	cin >> T;
	for(int idxTest = 0; idxTest < T; idxTest++)
	{
		cin >> str;
		for(int idxChar = 0; idxChar < str.length(); idxChar += 2)
		{
			cout << str.at(idxChar);
		}
		for(int idxChar = 1; idxChar < str.length(); idxChar += 2)
		{
			cout << str.at(idxChar);
		}
		cout << endl;
	}

	return 0;
}
