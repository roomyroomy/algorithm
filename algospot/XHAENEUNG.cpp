#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<string, int> numbers;
map<int, string> alpha;

void init()
{
	numbers.insert(make_pair("zero", 0));
	numbers.insert(make_pair("one", 1));
	numbers.insert(make_pair("two", 2));
	numbers.insert(make_pair("three", 3));
	numbers.insert(make_pair("four", 4));
	numbers.insert(make_pair("five", 5));
	numbers.insert(make_pair("six", 6));
	numbers.insert(make_pair("seven", 7));
	numbers.insert(make_pair("eight", 8));
	numbers.insert(make_pair("nine", 9));
	numbers.insert(make_pair("ten", 10));

	alpha.insert(make_pair(0, "zero"));
	alpha.insert(make_pair(1, "one"));
	alpha.insert(make_pair(2, "two"));
	alpha.insert(make_pair(3, "three"));
	alpha.insert(make_pair(4, "four"));
	alpha.insert(make_pair(5, "five"));
	alpha.insert(make_pair(6, "six"));
	alpha.insert(make_pair(7, "seven"));
	alpha.insert(make_pair(8, "eight"));
	alpha.insert(make_pair(9, "nine"));
	alpha.insert(make_pair(10, "ten"));
}

string solve(string s1, string s2, string op, string r)
{
	int n1, n2, num = -1;
	string sol = "";

	n1 = numbers.find(s1)->second;
	n2 = numbers.find(s2)->second;
	if(op.compare("+") == 0)
		num = n1 + n2;
	else if(op.compare("-") == 0)
		num = n1 - n2;
	else if(op.compare("*") == 0)
		num = n1 * n2;

	auto it = alpha.find(num);
	if(it != alpha.end())
		sol = it->second;

	if(sol.size() != r.size())
		return "No";

	sort(sol.begin(), sol.end());
	sort(r.begin(), r.end());

	for(auto it = sol.begin(), it2 = r.begin(); it != sol.end(); it++, it2++)
	{
		if(*it != *it2)
			return "No";
	}

	return "Yes";
}

int main()
{
	std::ios::sync_with_stdio(false);

	init();

	int tc;
	string n1, n2, op, eq, r;
	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> n1 >> op >> n2 >> eq >> r;
		cout << solve(n1, n2, op, r) << endl;
	}

	return 0;
}
