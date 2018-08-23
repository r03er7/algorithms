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
inline double sqr(double a) {return a*a;}
struct POINT {
    int x,y;
    POINT(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator ==(POINT& a) {return a.x==x && a.y==y;}
}; /* newpage*/
ostream& operator<<(ostream& a, POINT& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
#define Det(a, b, c) (LL(b.x - a.x) * LL(c.y - a.y) - LL(b.y - a.y) * (c.x - a.x))
#define PointInRect(p1, p2, p3) (min(p1.x, p2.x) <= p3.x && \
min(p1.y, p2.y) <= p3.y && max(p1.x, p2.x) >= p3.x && max(p1.y, p2.y) >= p3.y)
#define PointInsideRect(p1, p2, p3) (min(p1.x, p2.x) < p3.x && \
min(p1.y, p2.y) < p3.y && max(p1.x, p2.x) > p3.x && max(p1.y, p2.y) > p3.y)
#define PointInSegment(p1, p2, l) (Det(p1, p2, l) == 0 && PointInRect(p1, p2, l))
#define PointInsideSegment(p1, p2, l) (Det(p1, p2, l) == 0 && PointInsideRect(p1, p2, l))
#define PointInCircle(c, r, p) (sqr(c.x - p.x) + sqr(c.y - p.y) - EPS < sqr(r))
#define PointInsideCircle(c, r, p) (sqr(c.x - p.x) + sqr(c.y - p.y) + EPS < sqr(r))
int main() { 
	POINT r1,r2,c,s1,s2,p;
	int r;
	cin >> r1.x >> r1.y >> r2.x >> r2.y;
	cin >> s1.x >> s1.y >> s2.x >> s2.y;
	cin >> c.x >> c.y >> r;
	cout << "\t\t\t    Rectangle\t\t    Segment\t\t     Circle" << endl;
	cout << "\t\t\tInside\t In\t    Inside\t In\t    Inside\t In" << endl;
	while(cin >> p.x >> p.y) {
		cout << p << "\t\t" << PointInsideRect(r1, r2, p) << "\t\t" << 
			PointInRect(r1, r2, p) << "\t\t" << 
			PointInsideSegment(s1, s2, p) << "\t\t" << 
			PointInSegment(s1, s2, p) << "\t\t" << 
			PointInsideCircle(c, r, p) << "\t\t" << 
			PointInCircle(c, r, p) << endl;
	}
	return 0;
}
