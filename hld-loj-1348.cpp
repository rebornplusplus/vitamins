#include <bits/stdc++.h>
using namespace std;

const int N = 30000 + 5;
vector<int> g[N];
int ghost[N];
int par[N], lev[N];
int sp[N][20];
int n;
int subsize[N], chainHead[N], chainIdx[N];
vector<int> chains[N];
int cnt, chainNo;
int base[N], pos[N];
int seg[N*4];

void dfs(int u, int pr, int lv) {
	par[u] = pr;
	lev[u] = lv;
	subsize[u] = 1;
	for(int i=0; i<(int) g[u].size(); ++i) {
		int v = g[u][i];
		if(v != pr) {
			dfs(v, u, lv+1);
			subsize[u] += subsize[v];
		}
	}
}

void lca_init() {
	memset(sp, -1, sizeof sp);
	for(int i=0; i<n; ++i) sp[i][0] = par[i];

	for(int j=1; (1<<j) < n; ++j) {
		for(int i=0; i<n; ++i) {
			if(sp[i][j-1] != -1) sp[i][j] = sp[sp[i][j-1]][j-1];
		}
	}
}

inline int lca(int u, int v) {
	if(lev[u] < lev[v]) swap(u, v);

	int logn = 0;
	while((1 << (1+logn)) <= n) ++logn;
	for(int i=logn; i>=0; --i) {
		if(lev[u] - (1<<i) >= lev[v]) u = sp[u][i];
	}
	if(u == v) return u;

	for(int i=logn; i>=0; --i) {
		if(sp[u][i] != -1 and sp[u][i] != sp[v][i]) {
			u = sp[u][i];
			v = sp[v][i];
		}
	}
	return par[u];
}

void hld(int u, int pr) {
	if(chainHead[chainNo] == -1) chainHead[chainNo] = u;
	chainIdx[u] = chainNo;
	base[cnt++] = ghost[u];
	pos[u] = cnt-1;
	chains[chainNo].push_back(u);

	int sc = -1, maxi = -1;
	for(int i=0; i<(int) g[u].size(); ++i) {
		int v = g[u][i];
		if(v != pr and subsize[v] > maxi) maxi = subsize[v], sc = v;
	}

	if(sc > -1) hld(sc, u);
	for(int i=0; i<(int) g[u].size(); ++i) {
		int v = g[u][i];
		if(v != pr and v != sc) {
			++chainNo;
			hld(v, u);
		}
	}
}

void build_tree(int at, int l, int r) {
	if(l == r) {
		seg[at] = base[l];
		return ;
	}

	int left = at+at, right = left+1, mid = (l+r)/2;
	build_tree(left, l, mid);
	build_tree(right, mid+1, r);
	seg[at] = seg[left] + seg[right];
}

void update_tree(int at, int l, int r, int &pos, int &val) {
	if(pos < l or pos > r) return ;
	if(pos == l and l == r) {
		seg[at] = val;
		return ;
	}

	int left = at+at, right = left+1, mid = (l+r)/2;
	update_tree(left, l, mid, pos, val);
	update_tree(right, mid+1, r, pos, val);
	seg[at] = seg[left] + seg[right];
}

int query_tree(int at, int l, int r, int &lo, int &hi) {
	if(l > hi or r < lo) return 0;
	if(l >= lo and r <= hi) return seg[at];

	int left = at+at, right = left+1, mid = (l+r)/2;
	int q1 = query_tree(left, l, mid, lo, hi);
	int q2 = query_tree(right, mid+1, r, lo, hi);
	return q1+q2;
}

int query_up(int u, int v) {
	int uchain, vchain = chainIdx[v], ret = 0;
	while(true) {
		uchain = chainIdx[u];
		if(uchain == vchain) {
			ret += query_tree(1, 0, n-1, pos[v], pos[u]);
			break;
		}
		ret += query_tree(1, 0, n-1, pos[chainHead[uchain]], pos[u]);
		u = chainHead[uchain];
		u = par[u];
	}
	return ret;
}

inline int update(int p, int val) {
	update_tree(1, 0, n-1, pos[p], val);
}

inline int query(int u, int v) {
	int l = lca(u, v);
	return query_up(u, l) + query_up(v, l) - query_up(l, l);
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		scanf("%d", &n);
		for(int i=0; i<n; ++i) scanf("%d", ghost+i);

		for(int i=0; i<n; ++i) g[i].clear(), chains[i].clear();
		for(int i=1; i<n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}

		dfs(0, -1, 0);
		lca_init();
		cnt = 0, chainNo = 0;
		memset(chainHead, -1, sizeof chainHead);
		hld(0, -1);
		build_tree(1, 0, n-1);

		printf("Case %d:\n", ++tc);
		int q;
		scanf("%d", &q);
		while(q--) {
			int type, a, b;
			scanf("%d %d %d", &type, &a, &b);
			if(type) update(a, b);
			else printf("%d\n", query(a, b));
		}
	}

	return 0;
}
