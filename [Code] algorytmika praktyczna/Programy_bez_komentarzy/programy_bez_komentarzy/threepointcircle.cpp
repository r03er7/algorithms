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
#include <list>
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
int LineCrossPoint(POINTD p1, POINTD p2, POINTD l1, POINTD l2, POINTD &prz){
  double s, t = (p1.x - p2.x) * (l1.y - l2.y) - (p1.y - p2.y) * (l1.x - l2.x);
  s = (l2.x - p2.x) * (l1.y - l2.y) - (l2.y - p2.y) * (l1.x - l2.x);
  if (IsZero(t)) return IsZero(s) ? 2 : 0;
  s = s/t;
  prz.x = s * p1.x + (1-s) * p2.x;
  prz.y = s * p1.y + (1-s) * p2.y;
  return 1;
}
bool ThreePointCircle(POINTD p1, POINTD p2, POINTD p3, POINTD &c, double &r){ 
	if (LineCrossPoint(POINTD((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0), 
		POINTD((p1.x + p2.x) / 2.0 + p2.y - p1.y, (p1.y + p2.y) / 2.0 + p1.x 
		- p2.x), POINTD((p1.x + p3.x) / 2.0, (p1.y + p3.y) / 2.0), 
		POINTD((p1.x + p3.x) / 2.0 + p3.y - p1.y, 
			(p1.y + p3.y) / 2.0 + p1.x - p3.x) ,c) != 1)
	return false;
	r = sqrt(sqr(p1.x - c.x) + sqr(p1.y - c.y));
	return true;
}
int main() {
	vector<POINT> l;
	POINT p;
	POINTD po;
	double r;
	bool res;
	while(cin >> p.x >> p.y) l.PB(p);
	REP(x, SIZE(l)) REP(y, x) REP(z, y) {
		cout << "Punkty: " << l[x] << ", " << l[y] << ", " << l[z] << endl;
		if (!ThreePointCircle(l[x], l[y], l[z], po, r))
			cout << "Punkty sa wspolliniowe" << endl;
		else
			cout << "Srodek okregu = " << po << ", promien = " << r << endl;
	}
	return 0;
}
