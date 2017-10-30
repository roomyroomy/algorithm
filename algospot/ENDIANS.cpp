#include <iostream>
#include <string>
#include <vector>

using namespace std;

unsigned convert(unsigned num)
{
	int result = 0;

	result += num & 0xFF;
	result = result << 8;

	result += (num >> 8) & 0xFF;
	result = result << 8;

	result += (num >> 16) & 0xFF;
	result = result << 8;

	result += (num >> 24) & 0xFF;

	return result;
}

int main()
{
	int C;

	cin >> C;
	for(int idxItem = 0; idxItem < C; idxItem++)
	{
		unsigned num;
		cin >> num;
		cout << convert(num) << endl;
	}

	return 0;
}
