#include <bits/stdc++.h>
using namespace std;

/*////////////////////
adj[] is the main graph
trans[] strores tranpose graph
ind[u] will store the component number where u belongs to
////////////////////*/
const int maxn = 100000 + 7; 	// 1e5
vector<int> adj[maxn], trans[maxn]; 
int ind[maxn], vis[maxn], idx = 0; 
stack<int> st; 

void dfs(int u) {
	vis[u] = 1;
	for(int i=0; i<(int) adj[u].size(); ++i) {
		int v = adj[u][i];
		if(!vis[v]) dfs(v);
	}
	st.push(u);
}
void dfs2(int u) {
	ind[u] = idx;
	for(int i=0; i<(int) trans[u].size(); ++i) {
		int v = trans[u][i];
		if(!ind[v]) dfs2(v);
	}
}
int scc(int n) {
	memset(vis, false, sizeof vis);
	while(!st.empty()) st.pop();
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) dfs(i);
	}
	for(int u = 1; u <= n; u++) {
		for(int i=0; i<(int) adj[u].size(); ++i) {
			int v = adj[u][i];
			trans[v].push_back(u);
		}
	}
	idx = 0;
	memset(ind, 0, sizeof ind);
	while(!st.empty()) {
		int u = st.top(); st.pop();
		if(ind[u]) continue; 
		idx++; dfs2(u); 
	}
	return idx;
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; ++i) adj[i].clear(), trans[i].clear();
		while(m--) {
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
		}
		
		int res = scc(n);
		printf("Case %d: %d\n", ++tc, res);
	}

	return 0;
}
