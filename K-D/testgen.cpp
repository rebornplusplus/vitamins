#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("in.txt", "w", stdout);
    srand(time(NULL));

    /// points in [0, 0] : [L, L]
    const int L = 23;

    int n = 1000;
    cout << n << "\n";

    for(int i=0; i<n; ++i) {
        int x = rand() % (L+1);
        if(rand() % 2) x *= -1;
        int y = rand() % (L+1);
        if(rand() % 2) y *= -1;
        cout << x << " " << y << "\n";
    }

    int q = 10000;
    cout << q << "\n";
    while(q--) {
        int a = rand() % (L+1);
        if(rand() % 2) a *= -1;
        int b = rand() % (L+1);
        if(rand() % 2) b *= -1;
        int c = rand() % (L+1);
        if(rand() % 2) c *= -1;
        int d = rand() % (L+1);
        if(rand() % 2) d *= -1;
        if(a > c) swap(a, c);
        if(b > d) swap(b, d);
        cout << a << " " << b << " " << c << " " << d << "\n";
    }

    return 0;
}
