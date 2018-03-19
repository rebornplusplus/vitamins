#include <bits/stdc++.h>
using namespace std;

struct KMP {
	// prefix array, pi[q] refers to the length of longest proper prefix of P 
	// which is also a proper suffix of P[0..q]
	vector<int> pi;

	KMP() { pi.clear(); }

	void prefix_compute(string P) {
		pi.resize(P.size());
		pi[0] = 0;
		int q = 0;	// number of matched characters

		for(int i=1; i<(int) P.size(); ++i) {
			while(q > 0 and P[q] != P[i]) q = pi[q-1];
			if(P[q] == P[i]) ++q;
			pi[i] = q;
		}
	}

	int kmp_matcher(string T, string P) {
		prefix_compute(P);
		int q = 0;	// number of matched characters
		int ocr = 0;	// number of occurences of P in T

		for(int i=0; i<(int) T.size(); ++i) {
			while(q > 0 and P[q] != T[i]) q = pi[q-1];
			if(P[q] == T[i]) ++q;
			if(q == (int) P.size()) {
				// Pattern matches at (i+1 - P.size()) position of T
				++ocr;
				q = pi[q-1];
			}
		}
		return ocr;
	}
};

int main() {
	string t, p;
	cin >> t >> p;

	KMP ds;
	cout << ds.kmp_matcher(t, p) << "\n";

	return 0;
}
