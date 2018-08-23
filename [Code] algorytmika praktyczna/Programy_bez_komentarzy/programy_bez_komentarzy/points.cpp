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
typedef unsigned long long int ulli;
const ulli low_part  = 2147483647;
const ulli high_part = low_part * (low_part + 2);
struct superlong {
	ulli high, low;
	bool operator==(const superlong& a) {
		return a.high == high && a.low == low;
	}
	bool operator<(const superlong& a) {
		return high < a.high || (high == a.high && low < a.low);
	}
};

inline superlong multiply(ulli v1, ulli v2)
{
	superlong val;
	ulli x = (v1 & low_part) * (v2 >> 31) + (v1 >> 31) * (v2 & low_part);
	val.low = (v1 & low_part) * (v2 & low_part);
	val.high = (v1 >> 31) * (v2 >> 31);
	val.low  += (x & low_part) << 31;
	val.high += (x >> 31) + (val.low >> 62);
	val.low  = val.low & high_part;
	return val;
}

struct pSet {
	bool cen;
	LL size;
	vector<LL> cdist, dist;
};

LL sqr(int x) {
	return LL(x)*LL(x);
}

pSet ReadSet() {
	int s;
	pSet res;
	cin >> s;
	vector<POINT> pl(s);
	int wx = 0, wy = 0;
	REP(x,s) {
		cin >> pl[x].x >> pl[x].y;
		wx += pl[x].x;
		wy += pl[x].y;
	}
	REP(x,s) {
		pl[x].x = pl[x].x*s - wx;
		pl[x].y = pl[x].y*s - wy;
	}
	res.cen = false;
	REP(x,s) if (!pl[x].x && !pl[x].y) {
		res.cen = true;
		swap(pl[x], pl.back());
		pl.pop_back();
		s--;
		break;
	}
	vector<POINT*> sorted = AngleSort(pl, POINT(0,0), POINT(1,0));
	res.cdist.resize(s);
	res.dist.resize(s);
	res.size = 0;
	REP(x, s) {
		res.cdist[x] = sqr(sorted[x]->x) + sqr(sorted[x]->y);
		res.dist[x] = sqr(sorted[x]->x - sorted[(x+1)%s]->x) + sqr(sorted[x]->y - sorted[(x+1)%s]->y);
		res.size >?= res.cdist[x];
	}
	return res;
}

int CmpEl(pSet& l, int pl, pSet& r, int pr) {
	superlong v1 = multiply(l.cdist[pl], r.size);
	superlong v2 = multiply(r.cdist[pr], l.size);
	if (v1 == v2) {
		v1 = multiply(l.dist[pl], r.size);
		v2 = multiply(r.dist[pr], l.size);
		if (v1 == v2) return 0;
	}
	return v1 < v2 ? -1 : 1;
}

bool equal(pSet& l, pSet& r) {
	if (SIZE(l.dist) != SIZE(r.dist) || l.cen != r.cen) return false;
	int n = SIZE(l.dist), i = 0, j = 0, k = 1;
	while(i < n && j < n && k < n) {
		k = 1;
		while(k <= n && CmpEl(l, (i+k)%n, r, (j+k)%n) == 0) k++;
		if (k<=n) if (CmpEl(l, (i+k)%n, r, (j+k)%n) == -1) i+=k;
		else j+=k;
	}
	return k > n;
}

int main() {
	int n;
	pSet p1 = ReadSet();
	cin >> n;
	while(n--) {
		pSet p2 = ReadSet();
		if (!equal(p1, p2) && SIZE(p1.cdist) > 1) {
			reverse(ALL(p2.cdist));
			reverse(p2.dist.begin(), p2.dist.end()-1);
		}
		cout << (equal(p1, p2) ? "TAK" : "NIE") << endl;
	}
	return 0;
}
