// LightOJ 1064 - Throwing Dice

// rebornplusplus
// Jun 17 2018 1802

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define ff first
#define ss second
#define INF 2000000000
#define fuk cout << "FUK \n"

inline ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

struct Fraction {
	ll n, d;
	Fraction() { n = 0, d = 1; }
	Fraction(ll _n, ll _d) : n(_n), d(_d) { }
	Fraction operator+(Fraction p) {
		ll g = gcd(d, p.d);
		ll td = d * (p.d / g);
		ll tn = n * (td/d) + p.n * (td/p.d);
		g = gcd(tn, td);
		tn /= g, td /= g;
		return Fraction(tn, td);
	}
	Fraction operator-(Fraction p) {
		ll g = gcd(d, p.d);
		ll td = d * (p.d / g);
		ll tn = n * (td/d) - p.n * (td/p.d);
		g = gcd(tn, td);
		tn /= g, td /= g;
		return Fraction(tn, td);
	}
	Fraction operator*(Fraction p) {
		ll g1 = gcd(n, p.d), g2 = gcd(p.n, d);
		ll tn = (n/g1) * (p.n/g2);
		ll td = (d/g2) * (p.d/g1);
		ll g = gcd(tn, td);
		tn /= g, td /= g;
		return Fraction(tn, td);
	}
	Fraction operator/(Fraction p) {
		ll g1 = gcd(n, p.n), g2 = (d, p.d);
		ll tn = (n/g1) * (p.d/g2);
		ll td = (d/g2) * (p.n/g1);
		ll g = gcd(tn, td);
		tn /= g, td /= g;
		return Fraction(tn, td);
	}
	bool operator==(Fraction p) {
		return n == p.n and d == p.d;
	}
	bool operator!=(Fraction p) {
		return !(*this == p);
	}
};

ostream& operator<<(ostream &out, Fraction p) {
	out << p.n << "/" << p.d;
}

const Fraction ONE = Fraction(1, 1);
const Fraction ZERO = Fraction(0, 1);
const Fraction NEGO = Fraction(-1, 1);
const Fraction PROB = Fraction(1, 6);
Fraction dp[30][155];

inline Fraction fun(int n, int x) {
	if(x <= 0) return ONE;
	if(n == 0) return ZERO;
	Fraction &r = dp[n][x];
	if(r != NEGO) return r;

	r = ZERO;
	for(int i=1; i<=6; ++i) r = r + fun(n-1, x-i);
	r = r * PROB;
	return r;
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		int n, x;
		scanf("%d %d", &n, &x);
		for(int i=0; i<=n; ++i) for(int j=0; j<=x; ++j) dp[i][j] = NEGO;
		Fraction res = fun(n, x);
		printf("Case %d: %lld", ++tc, res.n);
		if(res.d > 1) printf("/%lld", res.d);
		putchar('\n');
	}

	return 0;
}
