// SPOJ RESIST ( http://www.spoj.com/problems/RESIST/ )
// Used Nodal Analysis ( I did a 4 credit course on this shit and still couldn't remember how to find equivalent resistance)
// Gaussian Elimination

// rebornplusplus
// May 22 2018 2142

#include <bits/stdc++.h>
using namespace std;

const double INF = 1e18;
const double EPS = 1e-12;
const int N = 109;
double a[N][N];
double g[N][N];

void gauss(int n) {
	for(int i=0; i<n; ++i) {
		// find row from i with largest value at i
		int tr = i;
		for(int j=i+1; j<n; ++j) {
			if(fabs(a[j][i]) > fabs(a[tr][i])) tr = j;
		}
		// swap with row i
		for(int j=0; j<=n; ++j) swap(a[i][j], a[tr][j]);
		
		// eliminate i from all rows below
		for(int j=i+1; j<n; ++j) {
			for(int k=n; k>=i; --k) {
				a[j][k] -= a[i][k] * a[j][i] / a[i][i];	// be careful here
			}
		}
	}
	// restore
	for(int i=n-1; i>=0; --i) {
		double t = a[i][n];
		for(int j=i+1; j<n; ++j) t -= a[i][j] * a[j][n];
		t /= a[i][i];
		a[i][n] = t;
	}
	// value of the i'th variable is in a[i][n]
}

void prep(int n) {
	for(int i=0; i<n; ++i) for(int j=0; j<=n; ++j) a[i][j] = 0;
	for(int i=0; i<n-1; ++i) {
		for(int j=0; j<n; ++j) {
			if(j == i) continue;
			double w = g[i][j];
			a[i][i] += (1.0 / w), a[i][j] -= (1.0 / w);
		}
	}
	a[0][n] = 1;
	a[n-1][n-1] = 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	while(cin >> n >> m) {
		for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) g[i][j] = INF;
		for(int i=0; i<m; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			--u, --v;
			g[u][v] = 1.0 / ((1.0/g[u][v]) + (1.0/w));
			g[v][u] = g[u][v];
		}

		prep(n);
		gauss(n);
		double res = a[0][n];
		cout << fixed << setprecision(2) << res << "\n";
	}
	
	return 0;
}
