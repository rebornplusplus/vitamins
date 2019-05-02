#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    freopen("brute.txt", "w", stdout);

    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for(int i=0; i<n; ++i) cin >> x[i] >> y[i];

    int q;
    cin >> q;
    while(q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int res = 0;
        for(int i=0; i<n; ++i) {
            if(x[i] >= a and x[i] <= c and y[i] >= b and y[i] <= d) ++res;
        }
        cout << res << "\n";
    }

    return 0;
}
