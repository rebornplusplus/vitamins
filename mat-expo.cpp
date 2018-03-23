// Matrix class

#include <bits/stdc++.h>
using namespace std;

struct matrix {
	// matrix row and col max size
	const static int sz = 10;
	const static long long mod = 1000000000 + 7;
	
	int row, col;
	long long v[sz][sz];

	matrix() { memset(v, 0, sizeof v); }
	matrix(int r, int c) : row(r), col(c) { memset(v, 0, sizeof v); }

	// multiplied by p
	matrix operator * (const matrix &p) {
		assert(col == p.row);

		matrix ret(row, p.col);
		for(int i=0; i<ret.row; ++i) {
			for(int j=0; j<ret.col; ++j) {
				long long sum = 0;
				for(int k=0; k<col; ++k) {
					sum += (v[i][k] * p.v[k][j]);
					sum %= mod;
				}
				ret.v[i][j] = sum;
			}
		}

		return ret;
	}

	// pwr p :| 
	matrix operator ^ (int p) {
		assert(row == col);

		matrix base = *this;
		matrix ret(row, col);
		for(int i=0; i<row; ++i) ret.v[i][i] = 1;

		while(p > 0) {
			if(p & 1) ret = ret * base;
			base = base * base;
			p >>= 1;
		}

		return ret;
	}
};

int main()
{
	// A sample main to test
	matrix mat(2, 2);
	mat.v[0][0] = 1, mat.v[0][1] = 2;
	mat.v[1][0] = 3, mat.v[1][1] = 4;

	matrix res = mat ^ 2;
	for(int i=0; i<res.row; ++i) {
		for(int j=0; j<res.col; ++j) cout << res.v[i][j] << " ";
		cout << "\n";
	}

	return 0;
}
