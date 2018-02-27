/*
    Heavy Light Decomposition
	used in SPOJ QTREE
    rebornplusplus
    Feb 27, 2018 1551
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
vector<int> g[N], c[N], e[N];
int par[N], lev[N];
int sp[N][18];  // sparse table, i's 2^j th parent
int n, cnt;
int chainNo, chainHead[N], chainIdx[N], chainPos[N], chainSize[N];
int subsize[N], otherEnd[N];
int baseArray[N], posInBase[N];
int seg[4*N];

void dfs(int u, int pr, int lv) {
    par[u] = pr;
    lev[u] = lv;
	subsize[u] = 1;
    for(int i=0; i<(int) g[u].size(); ++i) {
		int v = g[u][i];
        if(v != pr) {
			otherEnd[e[u][i]] = v;
			dfs(v, u, lv+1);
			subsize[u] += subsize[v];
		}
    }
}

void lca_init() {
    memset(sp, -1, sizeof sp);
    for(int i=1; i<=n; ++i) sp[i][0] = par[i];

    for(int j=1; (1<<j) < n; ++j) {
        for(int i=1; i<=n; ++i) {
            if(sp[i][j-1] != -1) sp[i][j] = sp[sp[i][j-1]][j-1];
        }
    }
}

int lca(int u, int v) {
	if(lev[u] < lev[v]) swap(u, v);

    int logn = 0;
    while((1 << (1+logn)) <= n) ++logn;
    for(int i=logn; i>=0; --i) {
        if(lev[u] - (1<<i) >= lev[v]) {
            u = sp[u][i];
        }
    }

    if(u == v) return u;
    for(int i=logn; i>=0; --i) {
        if(sp[u][i] != -1 && sp[u][i] != sp[v][i]) {
            u = sp[u][i];
            v = sp[v][i];
        }
    }
    return par[u];
}

void hld(int u, int w, int prev) {
	if(chainHead[chainNo] == -1) chainHead[chainNo] = u;
	chainIdx[u] = chainNo;
	chainPos[u] = chainSize[chainNo];
	++chainSize[chainNo];
	posInBase[u] = cnt;
	baseArray[cnt++] = w;

	int sc = -1, maxi = -1;
	for(int i=0; i<(int) g[u].size(); ++i) {
		int v = g[u][i];
		if(v != prev and subsize[v] > maxi) {
			sc = v, maxi = subsize[v], w = c[u][i];
		}
	}

	if(sc > -1) hld(sc, w, u);

	for(int i=0; i<(int) g[u].size(); ++i) {
		if(g[u][i] != prev and g[u][i] != sc) {
			++chainNo;
			hld(g[u][i], c[u][i], u);
		}
	}
}

void build_tree(int at, int l, int r) {
	if(l == r) {
		seg[at] = baseArray[l];
		return ;
	}

	int left = at+at, right = left+1, mid = (l+r) / 2;
	build_tree(left, l, mid);
	build_tree(right, mid+1, r);
	seg[at] = max(seg[left], seg[right]);
}

void update_tree(int at, int l, int r, const int &pos, const int &val) {
	if(pos < l or pos > r) return ;
	if(l == r and pos == l) {
		seg[at] = val;
		return ;
	}

	int left = at+at, right = left+1, mid = (l+r) / 2;
	update_tree(left, l, mid, pos, val);
	update_tree(right, mid+1, r, pos, val);
	seg[at] = max(seg[left], seg[right]);
}

int query_tree(int at, int l, int r, const int &lo, const int &hi) {
	if(r < lo or l > hi) return 0;
	if(l >= lo and r <= hi) return seg[at];

	int left = at+at, right = left+1, mid = (l+r) / 2;
	int q1 = query_tree(left, l, mid, lo, hi);
	int q2 = query_tree(right, mid+1, r, lo, hi);
	return max(q1, q2);
}

void change(int edg, int val) {
	int v = otherEnd[edg];
	update_tree(1, 1, n, posInBase[v], val);
}

int query_up(int u, int v) {
	if(u == v) return 0;
	int uchain, vchain = chainIdx[v], ret = -1;

	while(true) {
		uchain = chainIdx[u];
		if(uchain == vchain) {
			if(u == v) break;
			int q = query_tree(1, 1, n, posInBase[v]+1, posInBase[u]);
			ret = max(ret, q);
			break;
		}

		int q = query_tree(1, 1, n, posInBase[chainHead[uchain]], posInBase[u]);
		ret = max(ret, q);
		u = chainHead[uchain];
		u = par[u];
	}
	return ret;
}

int query(int u, int v) {
	int l = lca(u, v);
	return max(query_up(u, l), query_up(v, l));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

	int t;
	cin >> t;

	while(t--) {
		// clear stuffs
		for(int i=1; i<N; ++i) g[i].clear(), c[i].clear(), e[i].clear();
		memset(chainSize, 0, sizeof chainSize);

		cin >> n;
		for(int i=1; i<n; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			g[u].push_back(v);
			c[u].push_back(w);
			e[u].push_back(i);
			g[v].push_back(u);
			c[v].push_back(w);
			e[v].push_back(i);
		}

		dfs(1, -1, 0);
		lca_init();
		cnt = 1;
		memset(chainHead, -1, sizeof chainHead);
		hld(1, 0, -1);
		build_tree(1, 1, n);

		string s;
		while(cin >> s and s != "DONE") {
			if(s.front() == 'C') {
				int edg, val;
				cin >> edg >> val;
				change(edg, val);
			}
			else {
				int u, v;
				cin >> u >> v;
				cout << query(u, v) << "\n";
			}
		}
	}

    return 0;
}
