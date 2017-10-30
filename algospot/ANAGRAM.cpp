#include <iostream>
#include <string>
#include <list>

using namespace std;

bool compareStringSet(string &compA, string &compB)
{
	list<char> listA, listB;
	list<char>::iterator iterA, iterB;
	int lengthA = compA.length();
	int lengthB = compB.length();

	if(lengthA != lengthB)
		return false;
	if(compA.compare(compB) == 0)
		return false;

	for(int idxString = 0; idxString < lengthA; idxString++)
	{
		listA.push_back(compA.at(idxString));
		listB.push_back(compB.at(idxString));
	}

	listA.sort();
	listB.sort();

	for(iterA = listA.begin(), iterB = listB.begin(); iterA != listA.end(); iterA++, iterB++)
	{
		if(*iterA != *iterB)
			return false;
	}

	return true;
}

int main()
{
	int T;
	string compA, compB;

	cin >> T;

	for(int idxCase = 0; idxCase < T; idxCase++)
	{
		cin >> compA >> compB;
		if(compareStringSet(compA, compB) == true)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No." << endl;
		}
	}

	return 0;
}