#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
vector<int> g[N];
int par[N], lev[N];
int sp[N][18];  // sparse table, i's 2^j th parent
int n;

void dfs(int u, int pr, int lv) {
    par[u] = pr;
    lev[u] = lv;
    for(int v : g[u]) {
        if(v != pr) dfs(v, u, lv+1);
    }
}

void lca_init() {
    dfs(1, -1, 0);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for(int i=1; i<n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    lca_init();
    int q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        cout << "lca: " << lca(u, v) << "\n";
    }

    return 0;
}
