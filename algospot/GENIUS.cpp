#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct SquareMatrix
{
    int N;
    vector<vector<double> > v;
    SquareMatrix(int _N);
    static SquareMatrix identity(int N);
    SquareMatrix operator * (const SquareMatrix& rhs) const;
    SquareMatrix pow(int n) const;
    double* operator [] (int idx);
};

SquareMatrix::SquareMatrix(int _N)
{
    N = _N;
    v.resize(N, vector<double>(N, 0));
}

SquareMatrix SquareMatrix::identity(int N)
{
    SquareMatrix ret = SquareMatrix(N);
    for(int i = 0; i < N; i++) ret.v[i][i] = 1;
    return ret;
}

SquareMatrix SquareMatrix::operator * (const SquareMatrix& rhs) const
{
    SquareMatrix ret = SquareMatrix(N);
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                ret.v[i][j] += v[i][k] * rhs.v[k][j];
    return ret;
}

SquareMatrix SquareMatrix::pow(int n) const
{
    if(n == 0) return identity(N);
    if(n % 2 > 0) return (*this) * pow(n - 1);
    SquareMatrix half = pow(n/2);
    return half * half;
}

double* SquareMatrix::operator [] (int idx)
{
    return &v[idx][0];
}


vector<double> getProbability(vector<vector<double>> &T, vector<int> length, int k)
{
	int n = T.size();
	SquareMatrix W(4 * n);

	for(int i = 0; i < 3 * n; i++)
		W[i][i + n] = 1.0;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			W[3 * n + i][(4 - length[j]) * n + j] = T[j][i];

	SquareMatrix Wk = W.pow(k);
	vector<double> ret(n);

	for(int song = 0; song < n; song++)
		for(int start = 0; start < length[song]; start++)
			ret[song] += Wk[(3 - start) * n + song][3 * n];

	return ret;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cout << fixed << setprecision(8);

	int tc, n, k, m;

	cin >> tc;
	for(int idxCase = 0; idxCase < tc; idxCase++)
	{
		vector<int> songLength;
		vector<vector<double>> songProb;
		cin >> n >> k >> m;
		songLength.assign(n, 0);
		songProb.assign(n, vector<double>(n, 0.0));

		for(int idx = 0; idx < n; idx++)
			cin >> songLength[idx];

		for(int idxA = 0; idxA < n; idxA++)
			for(int idxB = 0; idxB < n; idxB++)
				cin >> songProb[idxA][idxB];

		vector<double> prob = getProbability(songProb, songLength, k);
		
		for(int idx = 0; idx < m; idx++)
		{
			int song;
			cin >> song;
			cout << prob[song] << " ";
		}
		cout << endl;
	}

	return 0;
}

/*
3
3 6 3
4 4 2
0.18 0.40 0.42
0.15 0.46 0.39
0.58 0.23 0.19
0 1 2
4 10 4
1 3 2 4
0.26 0.07 0.49 0.18
0.21 0.33 0.15 0.31
0.41 0.20 0.38 0.01
0.28 0.31 0.18 0.23
2 0 3 1
4 1000 4
4 3 4 4
0.08 0.47 0.12 0.33
0.10 0.02 0.39 0.49
0.08 0.33 0.35 0.24
0.14 0.19 0.58 0.09
1 3 2 0 
*/

/*
3
3 6 3
4 4 2
0.18 0.40 0.42
0.15 0.46 0.39
0.58 0.23 0.19
0 1 2
4 10 4
1 3 2 4
0.26 0.07 0.49 0.18
0.21 0.33 0.15 0.31
0.41 0.20 0.38 0.01
0.28 0.31 0.18 0.23
2 0 3 1
4 1000000 4
4 3 4 4
0.08 0.47 0.12 0.33
0.10 0.02 0.39 0.49
0.08 0.33 0.35 0.24
0.14 0.19 0.58 0.09
1 3 2 0 
*/