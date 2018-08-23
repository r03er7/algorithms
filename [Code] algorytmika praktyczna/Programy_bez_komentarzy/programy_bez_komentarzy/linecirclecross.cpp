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
vector<POINTD> LineCircleCross(POINTD p, double cr, POINTD p1, POINTD p2){ 
	double a = sqr(p1.x) + sqr(p1.y) + sqr(p2.x) + sqr(p2.y) - 
		2.0 * (p1.x * p2.x + p1.y * p2.y);
	double b = 2.0 * (p.x * (p2.x - p1.x) + p.y * (p2.y - p1.y) +
		p1.x * p2.x + p1.y * p2.y - sqr(p2.x)-sqr(p2.y));
	double c = -sqr(cr) + sqr(p2.x) + sqr(p2.y) + sqr(p.x) +
		sqr(p.y) - 2.0 * (p.x * p2.x + p.y * p2.y);
	double d = b * b - 4.0 * a * c;
	vector<POINTD> r;
	if (d < -EPS) return r;
	double t = -b / (2.0 * a), e = sqrt(abs(d)) / (2.0 * a);
	if (IsZero(d))
		r.PB(POINTD(t * p1.x + (1.0 - t) * p2.x, t * p1.y + (1.0 - t) * p2.y));
  else {
		r.PB(POINTD((t + e) * p1.x + (1.0 - t - e) * p2.x, 
			(t + e) * p1.y + (1.0 - t - e) * p2.y));
		r.PB(POINTD((t - e) * p1.x + (1.0 - t + e) * p2.x, 
			(t - e) * p1.y + (1.0 - t + e) * p2.y));
	}
	return r;
}
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
int main() { 
	vector<POINT> cCen;
	VI cR;
	vector<POINTD> res;
	POINT l1, l2, p; int r;
/* newpage */
	cin >> l1.x >> l1.y >> l2.x >> l2.y;
	while(cin >> p.x >> p.y >> r) {
		cR.PB(r); cCen.PB(p);
	}
	cout << "Przeciecie prostej " << l1 << " - " << l2 << 
		" i okregu:" << endl;
	REP(x, SIZE(cCen)) {
		res = LineCircleCross(cCen[x], cR[x], l1, l2);
		cout << "\t(" << cCen[x].x << ", " << cCen[x].y << 
			", " << cR[x] << ") - ";
		if (!SIZE(res)) cout << "brak punktow przeciecia";
		FOREACH(it, res) cout << " " << (*it);
		cout << endl;
	}
	cout << "Przeciecie okregow:" << endl;
	REP(x, SIZE(cCen)) REP(y, x) {
		res = CirclesCross(cCen[x], cR[x], cCen[y], cR[y]);
		cout << "\t(" << cCen[x].x << ", " << cCen[x].y << ", " << cR[x] << 
			") oraz (" << 
			cCen[y].x << ", " << cCen[y].y << ", " << cR[y] << ") - ";
		if (!SIZE(res)) cout << "brak punktow przeciecia";
		FOREACH(it, res) cout << " " << *(it);
		cout << endl;
	}
	return 0;
}
