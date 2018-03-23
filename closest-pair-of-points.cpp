// Closest Pair of Points
// O(n lg n)

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const long long inf = 1e18;

struct point {
	double x, y;
	point() { }
};

point *temp;
double closest = inf;
point p1, p2;

inline bool cmpX(point a, point b) { return a.x < b.x; }
inline double dist(point &a, point &b) { return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); }

double closestPair(point P[], int lo, int hi) {
	// distance to another element in lo-hi is infinity
	if(lo >= hi) return inf;

	// check both the sides
	int mid = (lo + hi) / 2;
	point midpoint = P[mid];
	double d1 = closestPair(P, lo, mid);
	double d2 = closestPair(P, mid+1, hi);
	double d = min(d1, d2);

	// mergesort according to Y co-ordinates
	for(int i=lo; i<=hi; ++i) temp[i] = P[i];
	int i=lo, j=mid+1, k=lo;
	while(i <= mid && j <= hi) 
		P[k++] = temp[i].y < temp[j].y ? temp[i++] : temp[j++];
	while(i <= mid) P[k++] = temp[i++];

	// check the pairs with less than d horizontal distance from the line
	int sz = 0;
	for(int i=lo; i<=hi; ++i) 
		if(abs(P[i].x - midpoint.x) < d)
			temp[sz++] = P[i];

	for(int i=0; i<sz; ++i) {
		for(int j=i+1; j<sz && temp[j].y - temp[i].y < d; ++j) {
			double dd = dist(temp[i], temp[j]);
			if(dd < d) {
				d = dd;
				if(d < closest) {
					closest = d;
					p1 = P[i];
					p2 = P[j];
				}
			}
		}
	}
	
	return d;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	point *pt = new point[n];
	for(int i=0; i<n; ++i) cin >> pt[i].x >> pt[i].y;
	
	temp = new point[n];
	sort(pt, pt+n, cmpX);
	closestPair(pt, 0, n-1);
	
	cout << "(" << p1.x << ", " << p1.y << ")\t"
	     << "(" << p2.x << ", " << p2.y << ")\n";
	cout << "Distance: " << closest << "\n";

	return 0;
}
