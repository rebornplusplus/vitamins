/*
	Floyd's Cycle Finding Algorithm
	ref: https://en.wikipedia.org/wiki/Cycle_detection
*/


#include <bits/stdc++.h>
using namespace std;

// lam(λ) is the length of the loop to be found and mu(μ) is the index of the first element of the cycle.
int mu, lam;

inline int f(int x) {
	return (x * (x+1)) % 11;
}

void floyd(int x0) {
	int tortoise = f(x0);
	int hare = f(f(x0));
	while(hare != tortoise) {
		tortoise = f(tortoise);
		hare = f(f(hare));
	}

	mu = 0;
	tortoise = x0;
	while(hare != tortoise) {
		tortoise = f(tortoise);
		hare = f(hare);
		++mu;
	}

	lam = 1;
	hare = f(tortoise);
	while(hare != tortoise) {
		hare = f(hare);
		++lam;
	}

	// updated lam, mu instead of returning the pair
}

int main()
{
	int x0;
	cin >> x0;

	floyd(x0);
	cout << mu << " " << lam << "\n";

	for(int i=0; i<20; ++i) {
		cout << x0 << " ";
		x0 = f(x0);
	} cout << endl;

	return 0;
}
