// Lowest Common Ancestor
// Using sparse table
// refer: http://www.shafaetsplanet.com/?p=1831

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;   // max nodes
vector<int> g[N];			// the graph
int par[N];					// parent of each node
int lev[N];					// level of each node. level of root = 0
int sp[N][18];				// sp[i][j] indicates i'th node's 2^j th parent
bool vis[N];				// for dfs
int n;						// actual number of nodes

// traverse the graph. Get the parents and levels
void dfs(int u, int pr, int lv) {
	vis[u] = true;
    par[u] = pr;
    lev[u] = lv;

    for(int i=0; i<(int) g[u].size(); ++i) {
		int v = g[u][i];
		if(!vis[v]) dfs(v, u, lv+1);
    }
}

// lca initialization
void lca_init() {
    memset(vis, false, sizeof vis);
    dfs(1, -1, 0);

    memset(sp, -1, sizeof sp);
    for(int i=1; i<=n; ++i) sp[i][0] = par[i];


    for(int j=1; (1<<j) < n; ++j) {
		for(int i=1; i<=n; ++i) {
			if(sp[i][j-1] != -1) {
				sp[i][j] = sp[sp[i][j-1]][j-1];
			}
		}
    }
}

// returns the LCA of u and v
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

// tester function
int main() {
    cin >> n;

    // clear graph
    for(int i=1; i<=n; ++i) g[i].clear();

    // input tree
    for(int i=1; i<n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
    }

    lca_init();

    // query
    int q;
    cin >> q;
    while(q--) {
		int u, v;
		cin >> u >> v;
        cout << lca(u, v) << "\n";
    }

    return 0;
}
