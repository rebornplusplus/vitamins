/**
 * 2-D Tree or 2-Dimensional K-D Tree
 * Build complexity: O(n lg^2 n); can be optimized further to O(n lg n) by finding median in O(n)
 * Splitting at some vertical line x means
 *   the left child contains points [-inf, x]
 *   the right child contains points [x, inf]
 * Query complexity:
 *   A rectangular range query on the kd-tree takes O(sqrt(n)+k) time,
 *   where k is the number of reported points.
 * Not your usual K-D Tree I suppose.
 * Use at own risk.
 *
 * Rafid
 * May 02 2019
**/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define x first
#define y second
const int inf = 0x3f3f3f3f;

const int N = 100000+7;
pii pts[N];    /// points
int n;  /// number of points; n = pts.size()

inline bool cmpX(const pii &a, const pii &b) {
    return a.x < b.x;
}
inline bool cmpY(const pii &a, const pii &b) {
    return a.y < b.y;
}

int tr[4*N], line[4*N];
pii leaf[4*N];

/* inline void prnt(int at, int depth) {
    return ;
    for(int i=0; i<depth; ++i) cout << "--";
    cout << (depth&1 ? "horizontal" : "vertical") << " split at " << line[at] << " contained " << tr[at] << " points " << (at&1 ? "[rc]" : "[lc]") << "\n";
} */

struct rectangle {
    int a, b;   /// lower left point
    int c, d;   /// upper right point

    rectangle(int aa=0, int bb=0, int cc=0, int dd=0) : a(aa), b(bb), c(cc), d(dd) { }
};

/// whether p and q intersects
bool intersects(rectangle p, rectangle q) {
    if(p.c < q.a or q.c < p.a) return false;
    if(p.d < q.b or q.d < p.b) return false;
    return true;
}

/// whether p contains q
bool contains(rectangle p, rectangle q) {
    return (p.a <= q.a and p.c >= q.c and p.b <= q.b and p.d >= q.d);
}

/// n lg^2 n
void build(int at, int l, int r, int depth=0) {
    if(l == r) {
        tr[at] = 1; /// pts[l]
        line[at] = (depth&1) ? pts[l].y : pts[l].x; /// unnecessary
        leaf[at] = pts[l];
        // prnt(at, depth);
        return ;
    }

    if(depth&1) sort(pts+l, pts+r+1, cmpY);
    else sort(pts+l, pts+r+1, cmpX);

    int lc=(at<<1), rc=(lc|1), mid = (l+r)>>1;
    line[at] = (depth&1) ? pts[mid].y : pts[mid].x;

    build(lc, l, mid, depth+1);
    build(rc, mid+1, r, depth+1);
    tr[at] = tr[lc] + tr[rc];

    // prnt(at, depth);
}

/// Finds the number of points in rectangle qq
int query(int at, int l, int r, int depth, rectangle cur, rectangle qq) {
    if(contains(qq, cur)) return tr[at];
    if(l == r) {
        if(contains(qq, rectangle(leaf[at].x, leaf[at].y, leaf[at].x, leaf[at].y))) return tr[at];
        return 0;
    }

    int lc=(at<<1), rc=(lc|1), mid = (l+r)>>1;
    rectangle rlc = cur, rrc = cur;
    if(depth&1) {
        rlc.d = line[at];
        rrc.b = line[at];
    }
    else {
        rlc.c = line[at];
        rrc.a = line[at];
    }

    int q1 = (intersects(rlc, qq) ? query(lc, l, mid, depth+1, rlc, qq) : 0);
    int q2 = (intersects(rrc, qq) ? query(rc, mid+1, r, depth+1, rrc, qq) : 0);
    return q1+q2;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin >> n;
    for(int i=1; i<=n; ++i) cin >> pts[i].x >> pts[i].y;

    build(1, 1, n);

    int q;
    cin >> q;

    while(q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << query(1, 1, n, 0, rectangle(-inf, -inf, inf, inf), rectangle(a, b, c, d)) << "\n";
    }

    return 0;
}

/**

6
2 3
4 2
4 4
3 3
3 3
1 5

**/
