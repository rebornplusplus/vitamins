/*
	CF 319C
	Convex Hull Trick ( Special Case, lines have non-decreasing slope )
	rebornplusplus
	Mar 14 2018 1048
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1000000000000000000LL;

struct line {
	ll m, c;
	line(ll _m, ll _c) : m(_m), c(_c) { }
	ll get(ll x) const { return m * x + c; }
	bool operator < (const line &p) const { return m < p.m; }
};

// special case where lines have nondecreasing slope
// btw, calculates for minimum. for maximum, alternate signs in the // ... 's
struct CHT {
	vector<line> hull;
	int cur;

	CHT() : cur(0) { }

	bool isBad(line &p, line &q, line &r) {
		return (p.c - r.c) * 1.0 / (r.m - p.m) <= (p.c - q.c) * 1.0 /  (q.m - p.m);
		// return (p.c - q.c) * (r.m - p.m) >= (p.c - r.c) * (q.m - p.m)	// use if it doesn't overflow
	}

	void addLine(ll m, ll c) {
		if(!hull.empty() and hull.back().m == m) {
			if(hull.back().c > c) hull.pop_back();	// ...
			else return ;
		}
		hull.push_back(line(m, c));
		int sz = hull.size();
		while(sz > 2 and isBad(hull[sz-3], hull[sz-2], hull[sz-1])) {
			swap(hull[sz-2], hull[sz-1]);
			hull.pop_back();
			--sz;
		}
	}

	ll query(ll x) {
		if(hull.empty()) return -inf;
		int l = -1, r = hull.size() - 1;
		while(r-l > 1) {
			int m = (l + r) / 2;
			if(hull[m].get(x) >= hull[m+1].get(x)) l = m;	// ...
			else r = m;
		}
		return hull[r].get(x);
	}

	ll Cquery(ll x) {
		if(hull.empty()) return -inf;
		while(cur+1 < hull.size()) {
			if(hull[cur].get(x) > hull[cur+1].get(x)) ++cur;	// ...
			else break;
		}
		return hull[cur].get(x);
	}

	void clear() { hull.clear(); }
};

const int N = 100000 + 5;
ll dp[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	int a[n], b[n];
	for(int i=0; i<n; ++i) cin >> a[i];
	for(int i=0; i<n; ++i) cin >> b[i];

	dp[0] = 0;
	CHT cht;
	for(int i=0; i<n; ++i) {
		if(i) dp[i] = cht.Cquery(a[i]);
		cht.addLine(b[i], dp[i]);
	}
	cout << dp[n-1];

	return 0;
}
