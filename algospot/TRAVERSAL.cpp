#include <iostream>
#include <vector>

using namespace std;

int findIndex(vector<int> &v, int item)
{
	int length = v.size();

	for(int idx = 0; idx < length; idx++)
	{
		if(v[idx] == item)
			return idx;
	}

	return -1;
}

void findPostOrder(vector<int> &preOrder, vector<int> &inOrder, vector<int> &postOrder, int preStart, int inStart, int postStart, int count)
{
	int rootIndex = 0;

	if(count <= 0)
		return;

	postOrder[postStart + count - 1] = preOrder[preStart];
	rootIndex = findIndex(inOrder, preOrder[preStart]);

	findPostOrder(preOrder, inOrder, postOrder, preStart + 1, inStart, postStart, rootIndex - inStart);
	findPostOrder(preOrder, inOrder, postOrder, preStart + 1 + (rootIndex - inStart), rootIndex + 1, postStart + (rootIndex - inStart), inStart + count - rootIndex - 1);
}

int main()
{
	int c, n, node;

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		vector<int> preOrder, inOrder, postOrder;
		cin >> n;

		for(int idxNode = 0; idxNode < n; idxNode++)
		{
			cin >> node;
			preOrder.push_back(node);
		}

		for(int idxNode = 0; idxNode < n; idxNode++)
		{
			cin >> node;
			inOrder.push_back(node);
		}

		postOrder.assign(n, 0);

		findPostOrder(preOrder, inOrder, postOrder, 0, 0, 0, n);

		for(int idxNode = 0; idxNode < n; idxNode++)
		{
			cout << postOrder[idxNode] << " ";
		}
		cout << endl;
	}

	return 0;
}
