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
bool OrdXY(POINT *a, POINT *b) {
	return a->x==b->x ? a->y<b->y : a->x<b->x;
}
struct POINTD {
    double x,y;
    POINTD(double wx = 0, double wy = 0) : x(wx), y(wy) {}
	POINTD(const POINT& p) : x(p.x), y(p.y) {}
    bool operator ==(POINTD& a) {return IsZero(a.x-x) && IsZero(a.y-y);}
};
ostream& operator<<(ostream& a, POINTD& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
int sgn(double x){ return IsZero(x)?0:(x < 0 ? -1 : 1); }
int sgn(int x){ return !x?0:(x < 0 ? -1 : 1); }
int LineCrossPoint(POINTD p1, POINTD p2, POINTD l1, POINTD l2, POINTD &prz){
  double s, t = (p1.x - p2.x) * (l1.y - l2.y) - (p1.y - p2.y) * (l1.x - l2.x);
  s = (l2.x - p2.x) * (l1.y - l2.y) - (l2.y - p2.y) * (l1.x - l2.x);
  if (IsZero(t)) return IsZero(s) ? 2 : 0;
  s = s/t;
  prz.x = s * p1.x + (1-s) * p2.x;
  prz.y = s * p1.y + (1-s) * p2.y;
  return 1;
}
inline bool SegmentCrossPoint(POINT p1, POINT p2, POINT l1, POINT l2, 
	vector<POINTD> &r) {
	r.clear(); 
	int w1 = sgn(Det(p1, p2, l1)), w2 = sgn(Det(p1, p2, l2)), 
		v1 = sgn(Det(l1, l2, p1)), v2 = sgn(Det(l1, l2, p2));
	if (w1*w2 > 0 || v1*v2 > 0) return false;
	if (!w1 && !w2) {
		if (OrdXY(&p2, &p1)) swap(p1, p2);
		if (OrdXY(&l2, &l1)) swap(l1, l2);
		if (OrdXY(&p2, &l1) || OrdXY(&l2,&p1)) return false;
		if (p2 == l1) r.PB(POINTD(p2.x, p2.y));
		else if (p1 == l2) r.PB(POINTD(l2.x, l2.y)); 
		else {
			r.PB(OrdXY(&p1, &l1) ? l1 : p1);
			r.PB(OrdXY(&p2, &l2) ? p2 : l2);
		}
	}
	else if (l1 == l2) r.PB(l1);
	else if (p1 == p2) r.PB(p2);
	else {
		double t = double(LL(l2.x - p2.x) * LL(l1.y - l2.y) - LL(l2.y - p2.y) * 
			LL(l1.x - l2.x)) / double(LL(p1.x - p2.x) * LL(l1.y - l2.y) - 
			LL(p1.y - p2.y) * LL(l1.x - l2.x));
		r.PB(POINTD(t * p1.x + (1.0 - t) * p2.x, t * p1.y + (1.0 - t) * p2.y));
	}
	return true;
}
int main() { 
	vector<POINT> b, e;
	vector<POINTD> l;
	int res;
	POINT p1, p2;
	POINTD p;
	while(cin >> p1.x >> p1.y >> p2.x >> p2.y) {
		b.PB(p1); e.PB(p2);
	}
	REP(x, SIZE(b)) REP(y, x) {
/* newpage */
		cout << b[x] << " - " << e[x] << 
			" oraz " << b[y] << " - " << e[y] << endl;
		cout << "Punkt przeciecia prostych: " << 
			(res = LineCrossPoint(b[x], e[x], b[y], e[y], p));
		if (res == 1) cout << " " << p;
		cout << endl;
		cout << "Punkt przeciecia odcinkow: " << 
			SegmentCrossPoint(b[x], e[x], b[y], e[y], l);
		FOREACH(it, l) cout << " " << (*it);
		cout << endl;
	}
	return 0;
}
