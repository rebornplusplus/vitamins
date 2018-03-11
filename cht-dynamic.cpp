/*
	CF 319C
	Trying to learn dynamic cht :/ 
	rebornplusplus
	Mar 11 2018 0746
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const double inf = 1e18;

struct line {
	ll m, b; double x; 
	ll val; bool isQuery; 
	line(ll _m = 0, ll _b = 0) : 
		m(_m), b(_b), val(0), x(-inf), isQuery(false) {} 
	
	ll eval(ll x) const { return m * x + b;	}
	bool parallel(const line &l) const { return m == l.m; }
	double intersect(const line &l) const {
		return parallel(l) ? inf : 1.0 * (l.b - b) / (m - l.m);
	}
	bool operator < (const line &l) const {
		if(l.isQuery) return x < l.val;
		else return m < l.m; 
	}
};

struct chtDynamic {
	set<line> hull; 
	typedef set<line> :: iterator iter; 

	bool cPrev(iter it) { return it != hull.begin(); }
	bool cNext(iter it) { return it != hull.end() && next(it) != hull.end(); }

	bool bad(const line &l1, const line &l2, const line &l3) {
		return l1.intersect(l3) <= l1.intersect(l2); 
	}
	bool bad(iter it) {
		return cPrev(it) && cNext(it) && bad(*prev(it), *it, *next(it));
	}

	iter update(iter it) {
		if(!cPrev(it)) return it; 
		double x = it -> intersect(*prev(it));
		line tmp(*it); tmp.x = x;
		it = hull.erase(it); 
		return hull.insert(it, tmp);
	}

	void addLine(ll m, ll b) { 
		m = -m, b = -b;
		line l(m, b); 
		iter it = hull.lower_bound(l); 
		if(it != hull.end() && l.parallel(*it)) {
			if(it -> b < b) it = hull.erase(it); 
			else return;
		}

		it = hull.insert(it, l); 
		if(bad(it)) return (void) hull.erase(it);

		while(cPrev(it) && bad(prev(it))) hull.erase(prev(it));
		while(cNext(it) && bad(next(it))) hull.erase(next(it));

		it = update(it);
		if(cPrev(it)) update(prev(it));
		if(cNext(it)) update(next(it));
	}

	ll query(ll x) const { 
		if(hull.empty()) return -inf;
		line q; q.val = x, q.isQuery = 1;
		iter it = --hull.lower_bound(q);
		return -(it -> eval(x));
	}
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
	chtDynamic cht;
	for(int i=0; i<n; ++i) {
		if(i) dp[i] = cht.query(a[i]);
		cht.addLine(b[i], dp[i]);
	}
	cout << dp[n-1];

	return 0;
}
