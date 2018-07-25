#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000 + 7;
bool vis[MAXN];
int lpair[MAXN], rpair[MAXN];	// left pair of right node and right pair of left node
vector<int> adj[MAXN];
int n, m;	// number of nodes, edges

bool bipartite_matching(int u) {
	for(int i=0; i<(int) adj[u].size(); ++i) {
		int v = adj[u][i];
		if(vis[v]) continue;
		
		vis[v] = true;
		if(lpair[v] == -1 or bipartite_matching(lpair[v])) {
			lpair[v] = u;
			rpair[u] = v;
			return true;
		}
	}
	return false;
}

int max_matching() {
	memset(lpair, -1, sizeof lpair);
	memset(rpair, -1, sizeof rpair);
	int ret = 0;
	for(int i=1; i<=n; ++i) ret += bipartite_matching(i);
	return ret;
}

int main() {
	scanf("%d %d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
	}

	int mbm = max_matching();
	printf("Maximum Bipartite Matching = %d\n", mbm);

	return 0;
}
