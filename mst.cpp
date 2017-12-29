#include <bits/stdc++.h>
using namespace std;

struct edge {
	int u, v, w;
	edge() { }
	edge(int uu, int vv, int ww) : u(uu), v(vv), w(ww) { }
	bool operator < (const edge &p) const { return w < p.w; }
};

const int N = 100005;
int par[N], rep[N];
vector<edge> e;

inline int Find(int r) {
	return par[r] == r ? r : par[r] = Find(par[r]);
}

int mst(int n) {
	sort(e.begin(), e.end());
	for(int i=1; i<=n; ++i) par[i] = i, rep[i] = 0;

	int res = 0, cnt = 0;
	for(int i=0; i<(int) e.size(); ++i) {
		int u = Find(e[i].u);
		int v = Find(e[i].v);

		if(u != v) {
			if(rep[u] > rep[v]) par[v] = u, ++rep[u];
			else par[u] = v, ++rep[v];
			res += e[i].w;
			if(++cnt == n-1) return res;
		}
	}

	return -1;
}

int main() {
	int n, m;
	cin >> n >> m;

	while(m--) {
		int u, v, w;
		cin >> u >> v >> w;
		e.push_back(edge(u, v, w));
	}

	int res = mst(n);
	cout << res;

	return 0;
}
