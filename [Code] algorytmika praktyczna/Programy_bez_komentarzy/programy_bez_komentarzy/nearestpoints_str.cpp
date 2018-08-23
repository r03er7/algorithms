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
const int INF = 1000000001;
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
bool OrdXY(POINT *a, POINT *b) {
	return a->x==b->x ? a->y<b->y : a->x<b->x;
}
bool OrdYX(POINT *a, POINT *b) {
	return a->y==b->y ? a->x<b->x : a->y<b->y;
}
struct NearestPoints { 
	vector<POINT*> l;
	POINT *p1, *p2;
	double dist;
	void Filter(vector<POINT*> &l, double p) {
		int s = 0;
		REP(x, SIZE(l))
			if (sqr(l[x]->x - p) <= dist) l[s++] = l[x];
		l.resize(s);
	}
	void Calc(int p, int k, vector<POINT*> &ys) {
		if (k - p > 1) {
			vector<POINT*> lp, rp;
			int c = (k + p - 1) / 2;
			FOREACH(it, ys)
				if (OrdXY(l[c], *it)) rp.PB(*it); else lp.PB(*it);
			Calc(p, c + 1, lp);
			Calc(c + 1, k, rp);
			Filter(lp, l[c]->x);
			Filter(rp, l[c]->x);
			int p = 0; double k;
			FOREACH(it, lp) {
			    while (p < SIZE(rp) - 1 && rp[p + 1]->y < (*it)->y) p++;
				FOR(x, max(0, p - 2), min(SIZE(rp) - 1, p + 1))
					if (dist > (k = sqr((*it)->x - rp[x]->x) + 
						sqr((*it)->y - rp[x]->y))) {
						dist = k;
						p1 = *it;
						p2 = rp[x];
					}
			}
		}
	}
	NearestPoints(vector<POINT> &p) {
		FOREACH(it, p) l.PB(&(*it));
		sort(ALL(l), OrdXY);
		FOR(x, 1, SIZE(l) - 1)
		    if (l[x - 1]->x == l[x]->x && l[x - 1]->y == l[x]->y) {
				dist = 0;
				p1 = l[x - 1]; p2 = l[x]; return;
		    }
		dist = double(INF) * double(INF);
		vector<POINT*> v = l;
		sort(ALL(v), OrdYX);
		Calc(0, SIZE(l), v);
		dist = sqrt(dist);
	}
};
int main() {
	int n;
	vector<POINT> l;
	POINT p;
	cin >> n;
	REP(x, n) {
		cin >> p.x >> p.y;
		l.PB(p);
	}
	NearestPoints str(l);
	cout << "Wyznaczona odleglosc: " << str.dist << endl;
	cout << "Znaleziona para najblizszych punktow:" << endl;
	cout << *(str.p1) << " " << *(str.p2) << endl;
	return 0;
}
