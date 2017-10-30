#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct _acm_format {
	char letter;
	int next;
	int repeat;
} ACM;

int gcd(int u, int v)
{
    int t;
    while (v)
	{
        t = u % v;
        u = v;
        v = t;
    }
    return u;
}

int lcm(int u, int v)
{
	return (u * v) / gcd(u, v);
}

vector<ACM> convertFormat(string &str)
{
	vector<ACM> result;
	int length = str.length();
	int lastJoint = -1, repeat = 0;
	bool inBrace = false;

	for(int idx = 0; idx < length; idx++)
	{
		char c = str[idx];

		if(str[idx] == '(' || (str[idx] >= 'A' && str[idx] <= 'Z'))
		{
			if(inBrace == false)
			{
				if(repeat > 0)
					result.back().repeat = repeat;
				if(lastJoint > -1)
					result.back().next = lastJoint;
				repeat = 0;
				lastJoint = -1;
			}
		}

		if(str[idx] == '(')
		{
			lastJoint = result.size();
			inBrace = true;
		}
		else if(str[idx] == ')' || str[idx] == '^')
		{
			inBrace = false;
		}
		else if(str[idx] >= '0' && str[idx] <= '9')
		{
			repeat = repeat * 10 + (int)(str[idx] - '0');
		}
		else
		{
			ACM piece;
			piece.letter = str[idx];
			piece.next = result.size() + 1;
			piece.repeat = 0;
			result.push_back(piece);
		}
	}

	if(inBrace == false)
	{
		if(repeat > 0)
			result.back().repeat = repeat;
		if(lastJoint > -1)
			result.back().next = lastJoint;
		repeat = 1;
		lastJoint = -1;
	}

	return result;
}

string equal(vector<ACM> &src, vector<ACM> &tar)
{
	int idxSrc = 0, idxTar = 0;
	int currentRepeatSrcIdx = -1, currentRepeatTarIdx = -1;
	int currentRepeatSrc = 0, currentRepeatTar = 0;
	int currentRepeatSrcSize = 0, currentRepeatTarSize = 0;
	int currentLcm = 0;

	while(idxSrc < src.size() && idxTar < tar.size())
	{
		if(src[idxSrc].letter != tar[idxTar].letter)
		{
			return "NO";
		}
		else
		{
			src[idxSrc].repeat--;
			tar[idxTar].repeat--;
			currentRepeatSrcSize++;
			currentRepeatTarSize++;
			if(src[idxSrc].repeat == 0)
			{
				src[idxSrc].next = idxSrc + 1;
				currentRepeatSrc = 0;
				currentRepeatSrcSize = 0;
			}
			if(tar[idxTar].repeat == 0)
			{
				tar[idxTar].next = idxTar + 1;
				currentRepeatTar = 0;
				currentRepeatTarSize = 0;
			}
			if(idxSrc >= src[idxSrc].next)
			{
				currentRepeatSrc = idxSrc - src[idxSrc].next + 1;
				currentRepeatSrcSize = idxSrc - src[idxSrc].next + 1;
				currentRepeatSrcIdx = idxSrc;
				currentLcm = lcm(currentRepeatSrc, currentRepeatTar);
			}
			if(idxTar >= tar[idxTar].next)
			{
				currentRepeatTar = idxTar - tar[idxTar].next + 1;
				currentRepeatTarSize = idxTar - tar[idxTar].next + 1;
				currentRepeatTarIdx = idxTar;
				currentLcm = lcm(currentRepeatSrc, currentRepeatTar);
			}
			idxSrc = src[idxSrc].next;
			idxTar = tar[idxTar].next;
			if(currentLcm > 0 && currentRepeatSrcIdx >= 0 && currentRepeatTarIdx >= 0 && currentRepeatSrc > 0 && currentRepeatTar > 0
				&& currentRepeatSrcSize >= currentLcm / currentRepeatSrc && currentRepeatTarSize >= currentLcm / currentRepeatTar)
			{
				int num1 = src[currentRepeatSrcIdx].repeat / (currentLcm / currentRepeatSrc);
				int num2 = tar[currentRepeatTarIdx].repeat / (currentLcm / currentRepeatTar);
				int minNum = min(num1, num2) - 1;
				if(minNum > 0)
				{
					src[currentRepeatSrcIdx].repeat -= (currentLcm / currentRepeatSrc) * minNum;
					tar[currentRepeatTarIdx].repeat -= (currentLcm / currentRepeatTar) * minNum;
				}
			}
		}
	}

	if(idxSrc < src.size() || idxTar < tar.size())
		return "NO";
	else
		return "YES";
}

int main()
{
	std::ios::sync_with_stdio(false);

	int tc;
	string str1, str2;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		cin >> str1 >> str2;
		vector<ACM> acm1 = convertFormat(str1);
		vector<ACM> acm2 = convertFormat(str2);
		cout << equal(acm1, acm2) << endl;
	}

	return 0;
}

/*
4
C(AAA)^10000000KKKK
C(AA)^15000000(K)^4
C(O)^2KIE(RUN)^5
COOKIER(UNR)^4UN
C(O)^2KIE(RUN)^50
CO(OKIER)^1(UNR)^49UN
KR(I)^3(I)^4
K(RI)^4
*/
