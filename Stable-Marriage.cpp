#include <bits/stdc++.h>
using namespace std;

// this class produces the stable marriage
// both men and women are ranked from 0....n-1
// produces the optimal result for men ( who proposes )
struct StableMarriage {
	vector< vector<int> > mpref, wpref;	// Men and Women preference
	vector<int> mpart;	// Men Partner for women, the actual result

	StableMarriage() { }
	StableMarriage(int n) {
		mpref.resize(n);
		wpref.resize(n);
		for(int i=0; i<n; ++i) mpref[i].resize(n), wpref[i].resize(n);
		mpart.resize(n);
	}

	void stabilize(int n) {
		// rank[w][m] means the preference rank of man 'm' in the list of woman 'w'
		int rank[n][n];
		for(int w=0; w<n; ++w)
			for(int i=0; i<n; ++i)
				rank[w][wpref[w][i]] = i;

		// proposed[m][w] holds whether m has proposed to w or not
		bool proposed[n][n];
		memset(proposed, false, sizeof proposed);
		fill(mpart.begin(), mpart.end(), -1);

		// the queue of freemen
		queue<int> q;
		for(int i=0; i<n; ++i) q.push(i);

		while(!q.empty()) {
			int m = q.front();
			q.pop();

			for(int i=0; i<n; ++i) {
				int w = mpref[m][i];
				if(proposed[m][w]) continue;	// Never propose twice

				proposed[m][w] = true;
				if(mpart[w] == -1) {
					mpart[w] = m;	// w is free, marry her for the time being :3
					break;
				}
				else {
					int cur = mpart[w];
					if(rank[w][m] < rank[w][cur]) {
						q.push(cur);	// w divorces cur
						mpart[w] = m;	// and marries m
						break;
					}
				}
			}
		}
	}
};

int main() {
	int n;
	cin >> n;

	StableMarriage ob(n);
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) cin >> ob.mpref[i][j];
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) cin >> ob.wpref[i][j];

	ob.stabilize(n);

	cout << "W - M\n";
	for(int w=0; w<n; ++w) cout << w << " - " << ob.mpart[w] << "\n";

	return 0;
}
