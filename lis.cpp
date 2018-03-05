// Longest Increasing Subsequence

#include <bits/stdc++.h>
using namespace std;

int LIS(const int a[], int n) {
	vector<int> lis;
	for(int i=0; i<n; ++i) {
		vector<int>::iterator it = lower_bound(lis.begin(), lis.end(), a[i]);
		if(it == lis.end()) lis.push_back(a[i]);
		else *it = a[i];
	}
	return (int) lis.size();
}

int main() {
	int a[] = { 4, 2, 7, 5, 9 };
	cout << LIS(a, 5) << "\n";
	return 0;
}
