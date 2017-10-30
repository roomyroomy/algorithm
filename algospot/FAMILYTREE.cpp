#include <iostream>
#include <vector>

using namespace std;

int getTreeDistance(vector<int> &tree, int nodeA, int nodeB)
{
	vector<int> ancestorA, ancestorB;
	int currentNode;
	int currentA, currentB;
	int result = 0;

	if(nodeA == nodeB)
		return 0;

	currentNode = nodeA;
	ancestorA.push_back(currentNode);
	while(currentNode != 0)
	{
		currentNode = tree[currentNode];
		ancestorA.push_back(currentNode);
	}

	currentNode = nodeB;
	ancestorB.push_back(currentNode);
	while(currentNode != 0)
	{
		currentNode = tree[currentNode];
		ancestorB.push_back(currentNode);
	}

	while(ancestorA.size() > 0 && ancestorB.size() > 0 && ancestorA.back() == ancestorB.back())
	{
		ancestorA.pop_back();
		ancestorB.pop_back();
	}

	return ancestorA.size() + ancestorB.size();
}

int main()
{
	int c, n, q;

	cin >> c;

	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		vector<int> tree;
		cin >> n >> q;
		tree.assign(n, 0);

		for(int idxNode = 1; idxNode < n; idxNode++)
		{
			int parentNode;
			cin >> parentNode;
			tree[idxNode] = parentNode;
		}

		for(int idxCheck = 0; idxCheck < q; idxCheck++)
		{
			int a, b;
			cin >> a >> b;
			cout << getTreeDistance(tree, a, b) << endl;
		}
	}

	return 0;
}
