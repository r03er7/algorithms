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
const int INF = 1000000001;
const double EPS = 10e-9;
int sgn(LL x) { if (x==0LL) return 0; return (x>0LL) ? 1 : -1;}
inline bool IsZero(double x){ return x>=-EPS && x<=EPS; }
struct POINT {
    int x,y;
    POINT(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator ==(POINT& a) {return a.x==x && a.y==y;}
}; /* newpage*/
ostream& operator<<(ostream& a, POINT& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
int sgn(double x){ return IsZero(x)?0:(x < 0 ? -1 : 1); }
int sgn(int x){ return !x?0:(x < 0 ? -1 : 1); }
#define PointInRect(p1,p2,p3) (min(p1.x, p2.x) <= p3.x && \
min(p1.y, p2.y) <= p3.y && max(p1.x, p2.x) >= p3.x && max(p1.y, p2.y) >= p3.y)
#define PointInSegment(p1,p2,l) (Det(p1,p2,l)==0 && PointInRect(p1,p2,l))
inline bool SegmentCross(POINT& p1, POINT& p2, POINT& l1, POINT& l2) {
    return sgn(Det(p1,p2,l1))*sgn(Det(p1,p2,l2)) == -1 && sgn(Det(l1,l2,p1))*sgn(Det(l1,l2,p2)) == -1;
}
bool PointInPol(vector<POINT>& l, POINT p) {
    int v=0,s=SIZE(l); POINT d(INF, p.y+1);
    REP(x,s) if (PointInSegment(l[x], l[(x+1)%s], p)) return true;
    REP(x,s) v += SegmentCross(p, d, l[x], l[(x+1)%s]);
    return v&1;
}
bool PointInsidePol(vector<POINT>& l, POINT p) {
    int v=0,s=SIZE(l); POINT d(INF, p.y+1);
    REP(x,s) if (PointInSegment(l[x], l[(x+1)%s], p)) return false;
    REP(x,s) v += SegmentCross(p, d, l[x], l[(x+1)%s]);
	return v&1;
}
bool PointInConvexPol(vector<POINT>& l, POINT p){
	int a = 1, b = SIZE(l)-1, c;
	if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
	if (Det(l[0], l[a], p) > 0 || Det(l[0], l[b], p) < 0) return false;
	while(abs(a-b) > 1) {
		c = (a+b)/2;
		if (Det(l[0], l[c], p) > 0) b = c; else a = c;
	}
	return Det(l[a], l[b], p) <= 0;
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
	vector<POINT> pol;
	POINT p;
	int n;
	cin >> n;
	REP(x, n) {
		cin >> p.x >> p.y;
		pol.PB(p);
	}
	cout << "\t\t\t\t Polygon\t\t\t\t  Convex Polygon" << endl;
	cout << "\t\t    Inside\t\t  In\t\t  Inside\t\t   In" << endl;
	while(cin >> p.x >> p.y) cout << p << "\t\t" << 
		PointInsidePol(pol, p) << "\t\t\t" <<
		PointInPol(pol, p) << "\t\t\t" << 
		PointInsideConvexPol(pol, p) << "\t\t\t" << 
		PointInConvexPol(pol, p) << endl;
	return 0;
}
