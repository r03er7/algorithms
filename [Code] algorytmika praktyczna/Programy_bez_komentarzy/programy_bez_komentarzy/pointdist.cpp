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
double PointLineDist(POINTD p1, POINTD p2, POINTD p) {
    double A=p2.y-p1.y, B=p2.x-p1.x;
    return abs(A*(p1.x-p.x)+B*(p.y-p1.y))/sqrt(A*A+B*B);
}
int main() { 
	POINT l1, l2, p;
	cin >> l1.x >> l1.y >> l2.x >> l2.y;
	while(cin >> p.x >> p.y)
		cout << "Odleglosc punktu " << p << " od prostej (" << 
		l1 << "," << l2 << ") wynosi " << PointLineDist(l1, l2, p) << endl;
	return 0;
}
