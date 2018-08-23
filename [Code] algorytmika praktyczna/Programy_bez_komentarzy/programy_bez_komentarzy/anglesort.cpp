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
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
POINT* RSK; 
bool Rcmp(POINT *a, POINT *b) {
	LL w = Det((*RSK), (*a), (*b));
	if (w == 0) return abs(RSK->x - a->x) + abs(RSK->y - a->y) < 
		abs(RSK->x - b->x) + abs(RSK->y - b->y);
	return w > 0;
}
vector<POINT*> AngleSort(vector<POINT>& p, POINT s, POINT k) {
	RSK = &s;
	vector<POINT*> l, r;
	FOREACH(it, p) {
		LL d = Det(s, k, (*it));
		(d > 0 || (d==0 && (s.x == it->x ? s.y < it->y : s.x < it->x))) 
			? l.PB(&*it) : r.PB(&*it);
	}
	sort(ALL(l), Rcmp);
	sort(ALL(r), Rcmp);
	FOREACH(it, r) l.PB(*it);
	return l;
}
int main() {
	POINT c, k;
	int n;
	cin >> n >> c.x >> c.y >> k.x >> k.y;
	vector<POINT> l(n);
	REP(x, n) cin >> l[x].x >> l[x].y;
	vector<POINT*> res = AngleSort(l, c, k);
	FOREACH(it, res) cout << " " << *(*it);
	return 0;
}
