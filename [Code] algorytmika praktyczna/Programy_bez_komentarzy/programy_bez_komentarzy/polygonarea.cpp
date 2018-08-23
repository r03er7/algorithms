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
struct POINT {
    int x,y;
    POINT(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator ==(POINT& a) {return a.x==x && a.y==y;}
}; /* newpage*/
ostream& operator<<(ostream& a, POINT& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
double PolygonArea(vector<POINT>& p) {
    double area=0; int s = SIZE(p);
	REP(x,s) area += (p[x].x + p[(x+1)%s].x)*(p[x].y - p[(x+1)%s].y);
    return abs(area)/2;
}
int main() {
	int n;
	vector<POINT> l;
	POINT p;
	cin >> n;
	REP(x, n) {
		cin >> p.x >> p.y;
		l.PB(p);
	}
	cout << "Pole wielokata: " << PolygonArea(l) << endl;
	return 0;
}
