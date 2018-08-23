#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

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
inline double sqr(double a) {return a*a;}
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
#define PointInCircle(c,r,p) (sqr(c.x-p.x)+sqr(c.y-p.y)-EPS < sqr(r))
vector<POINTD> CirclesCross(POINTD c1, double c1r, POINTD c2, double c2r){
  vector<POINTD> r;
  c2.x -= c1.x; c2.y-= c1.y;
  if (IsZero(c2.x) && IsZero(c2.y)) return r;
  double A = (-sqr(c2r)+sqr(c1r)+sqr(c2.x)+sqr(c2.y))/2.0;
  if (IsZero(c2.y)){
    double x = A/c2.x; double y2=sqr(c1r)-sqr(x);
    if (y2 <-EPS) return r;
    if(IsZero(y2)) r.PB(POINTD(c1.x+x,c1.y));
    else{
      r.PB(POINTD(c1.x+x,c1.y+sqrt(y2)));
      r.PB(POINTD(c1.x+x,c1.y-sqrt(y2)));
    }
    return r;
  }
  double a = sqr(c2.x) + sqr(c2.y);
  double b = -2.0 *A * c2.x;
  double c = A*A - sqr(c1r)*sqr(c2.y);
  double d = b*b-4.0*a*c;
  if (d<-EPS) return r;
  double x = -b/(2.0*a);
  if (IsZero(d)) r.PB(POINTD(c1.x + x, c1.y+(A - c2.x*x)/c2.y));
  else{
    double e = sqrt(d)/(2.0*a);
    r.PB(POINTD(c1.x+x+e, c1.y+(A-c2.x*(x+e))/c2.y));
    r.PB(POINTD(c1.x+x-e, c1.y+(A-c2.x*(x-e))/c2.y));
  }
  return r;
}
#define Dist(p1, p2) sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y))

bool crossPoint(POINT px, int rx, POINT py, int ry, POINTD& res) {
	if (rx > ry) {
		swap(rx, ry);
		swap(px, py);
	}
	res = px; res.x += rx;
	if (Dist(res, py) <= ry+EPS)
		return true;
	res = py; res.x += ry;
	if (Dist(res, px) <= rx+EPS)
		return true;
	vector<POINTD> l = CirclesCross(px, rx, py, ry);
	if (!SIZE(l)) return false;
	res = (SIZE(l) == 1 || l[0].x >= l[1].x) ? l[0] : l[1];
	return true;
}

int solve () {
	int n;
	cin >> n;
	POINT com[n];
	int r[n];
	REP(x, n)
		cin >> com[x].x >> com[x].y >> r[x];
	POINTD cross1, cross2;
	if (!crossPoint(com[0], r[0], com[1], r[1], cross1))
		return 2;
	FOR(x,2,n-1) {
		REP(y, x) {
			if (!crossPoint(com[x], r[x], com[y], r[y], cross2))
				return x+1;
			if (cross1.x > cross2.x) cross1 = cross2;
		}
		REP(y, x)
			if (!PointInCircle(com[y], r[y], cross1))
				return x+1;
	}
	return -1;
}

int main() {
	int res = solve();
	if (res == -1)
		cout << "NIE" << endl; 
	else
		cout << res << endl;
	return 0;
}
