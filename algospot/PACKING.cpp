#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item;

int C, N, W;
vector<Item> itemList;

class Item
{
public:
	string name;
	int size;
	int importance;
};

void compute(vector<vector<int>> &table)
{
	for(int idxRow = 1; idxRow < W; idxRow++)
	{
		if(idxRow >= itemList[0].size)
			table[0][idxRow] = itemList[0].importance;
	}

	for(int idxCol = 1; idxCol < N; idxCol++)
	{
		for(int idxRow = 1; idxRow <= W; idxRow++)
		{
			int caseA = table[idxCol - 1][idxRow];
			int caseB = table[idxCol][idxRow - 1];
			int caseC = 0;
			if(idxRow - itemList[idxCol].size >= 0)
				caseC = table[idxCol - 1][idxRow - itemList[idxCol].size] + itemList[idxCol].importance;
			table[idxCol][idxRow] = max(caseA, (max(caseB, caseC)));
		}
	}
}

void discoverItem(vector<vector<int>> &table, vector<string> &pickedItem)
{
	int currentRow = W;
	int currentCol = N - 1;

	while(table[currentCol][currentRow] != 0)
	{
 		if(currentCol > 0 && table[currentCol - 1][currentRow] == table[currentCol][currentRow])
		{
			currentCol--;
		}
		else if(table[currentCol][currentRow - 1] == table[currentCol][currentRow])
		{
			currentRow--;
		}
		else
		{
			pickedItem.push_back(itemList[currentCol].name);
			currentRow -= itemList[currentCol].size;
			if(currentCol > 0)
				currentCol--;
		}
	}
}

void printItem(vector<string> &pickedItem)
{
	for(vector<string>::reverse_iterator rit = pickedItem.rbegin(); rit!= pickedItem.rend(); rit++)
	{
		cout << *rit << endl;
	}
}

int main()
{
	cin >> C;

	while(C-- > 0)
	{
		vector<vector<int>> table;
		vector<string> pickedItem;

		itemList.clear();

		cin >> N >> W;

		table.assign(N, vector<int>(W + 1, 0));

		for(int idxItem = 0; idxItem < N; idxItem++)
		{
			Item item;
			cin >> item.name >> item.size >> item.importance;
			itemList.push_back(item);
		}
		
		compute(table);
		discoverItem(table, pickedItem);

		cout << table[N - 1][W] << " " << pickedItem.size() << endl;
		printItem(pickedItem);
	}

	return 0;
}
