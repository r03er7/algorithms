#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef long long LL;

#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
struct POINT {
    int x,y;
    POINT(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator ==(POINT& a) {return a.x==x && a.y==y;}
}; /* newpage*/
ostream& operator<<(ostream& a, POINT& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
bool OrdXY(POINT *a, POINT *b) {
	return a->x==b->x ? a->y<b->y : a->x<b->x;
}
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
#define XCAL {while(SIZE(w) > m && Det((*w[SIZE(w) - 2]), (*w[SIZE(w) - 1]), \
	(*s[x])) <= 0) w.pop_back(); w.PB(s[x]);} 
vector<POINT*> ConvexHull(vector<POINT>& p) {
	vector<POINT*> s, w;
	FOREACH(it, p) s.PB(&*it);
	sort(ALL(s), OrdXY);
	int m = 1;
	REP(x, SIZE(s)) XCAL
	m = SIZE(w);
	FORD(x, SIZE(s) - 2, 0) XCAL
	w.pop_back();
	return w;
}
bool PointInsideConvexPol(vector<POINT>& l, POINT p){
	int a = 1, b = SIZE(l)-1, c;
	if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
	if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
	while(abs(a-b) > 1) {
		c = (a+b)/2;
		if (Det(l[0], l[c], p) > 0) b = c; else a = c;
	}
	return Det(l[a], l[b], p) < 0;
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<POINT> l(n), l2;
	POINT p;
	REP(x,n) cin >> l[x].x >> l[x].y;
	vector<POINT*> hull = ConvexHull(l);
	l2.resize(SIZE(hull));
	REP(x, SIZE(hull)) l2[x] = *hull[x];
	REP(x,m) {
		cin >> p.x >> p.y;
		cout << (PointInsideConvexPol(l2, p) ? "NIE" : "TAK") << endl;
	}
	return 0;
}
