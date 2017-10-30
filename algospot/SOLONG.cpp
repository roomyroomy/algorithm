#include <iostream>
#include <map>
#include <string>

using namespace std;

class TRIE {
public:
	map<char, TRIE> childs;
	string str;
	pair<string, int> selected;
};

pair<string, int> addWord(TRIE &trie, string &word, int count, int depth = 0)
{
	if((int)word.length() < depth - 1)
		return make_pair(word, count);

	char c = word.c_str()[depth];

	map<char, TRIE>::iterator it = trie.childs.find(c);
	if(it == trie.childs.end())
	{
		TRIE cTrie;
		cTrie.str = word.substr(0, depth + 1);
		trie.childs.insert(make_pair(c, cTrie));
		it = trie.childs.find(c);
	}

	pair<string, int> candidate = addWord(it->second, word, count, depth + 1);
	if(depth > 0 &&
		(candidate.second > trie.selected.second
		|| (candidate.second == trie.selected.second && candidate.first.compare(trie.selected.first) < 0)))
		trie.selected = candidate;

	return trie.selected;
}

int typoNum(TRIE &trie, string &word, int depth = 0)
{
	char c = word.c_str()[depth];

	if(depth == word.length())
		return depth;

	if(word.compare(trie.selected.first) == 0)
	{
		if(depth != word.length())
			return depth + 1;	// 탭키 고려
	}

	map<char, TRIE>::iterator it = trie.childs.find(c);
	if(it == trie.childs.end())
		return word.length();
	else
		return typoNum(it->second, word, depth + 1);
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc, n, m, count;
	string str;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		TRIE trie;
		int result = 0;
		cin >> n >> m;
		for(int idxWord = 0; idxWord < n; idxWord++)
		{
			cin >> str >> count;
			addWord(trie, str, count);
		}
		for(int idxWord = 0; idxWord < m; idxWord++)
		{
			cin >> str;
			result += typoNum(trie, str);
		}
		result += m - 1;

		cout << result << endl;
	}

	return 0;
}
