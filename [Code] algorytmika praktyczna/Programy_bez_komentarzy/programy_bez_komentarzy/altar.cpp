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
#include <list>
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
struct altar {
	int lx, hx, ly, hy;
	char side;
};

void addSeg(vector<POINT>& open, vector<POINT>& close, POINT p1, POINT p2, POINT r1, POINT r2, POINT r3) {
	if (Det(r1, p1, p2) > 0) swap(p1, p2);
	if (Det(r1, r3, p1) >= 0 && Det(r1, r2, p2) <= 0) {
		open.PB(p1);
		close.PB(p2);
	}
}

int main() {
	int n;
	cin >> n;
	altar tab[n];
	REP(x,n) {
		cin >> tab[x].lx >> tab[x].hy >> tab[x].hx >> tab[x].ly >> tab[x].side;
		tab[x].lx *= 4;
		tab[x].ly *= 4;
		tab[x].hx *= 4;
		tab[x].hy *= 4;
	}
	REP(x,n) {
		POINT c((tab[x].lx+tab[x].hx)/2, (tab[x].ly+tab[x].hy)/2);
		POINT g1, g2, srt = c;
		int xside = (tab[x].hx - tab[x].lx)/4;
		int yside = (tab[x].hy - tab[x].ly)/4;
		switch(tab[x].side) {
			case 'E' :
				srt.x -= 1;
				g1.x = g2.x = tab[x].hx; 
				g1.y = tab[x].hy - yside;
				g2.y = tab[x].ly + yside;
				break;
			case 'W' :
				srt.x += 1;
				g1.x = g2.x = tab[x].lx; 
				g1.y = tab[x].ly + yside;
				g2.y = tab[x].hy - yside;
				break;
			case 'N' :
				srt.y -= 1;
				g1.y = g2.y = tab[x].hy; 
				g1.x = tab[x].lx + xside;
				g2.x = tab[x].hx - xside;
				break;
			case 'S' :
				srt.y += 1;
				g1.y = g2.y = tab[x].ly; 
				g1.x = tab[x].hx - xside;
				g2.x = tab[x].lx + xside;
				break;
		}
		vector<POINT> open, close;
		addSeg(open, close, g1, g1, c, g1, g2);
		addSeg(open, close, g2, g2, c, g1, g2);
		REP(y,n) if (x!=y) {
			addSeg(open, close, POINT(tab[y].lx, tab[y].ly), POINT(tab[y].hx, tab[y].hy), c, g1, g2);
			addSeg(open, close, POINT(tab[y].lx, tab[y].hy), POINT(tab[y].hx, tab[y].ly), c, g1, g2);
		}
		vector<POINT*> openS = AngleSort(open, c, srt);
		vector<POINT*> closeS = AngleSort(close, c, srt);
		int p1 = 0, p2 = 0;
		while(p2 < SIZE(openS)) {
			if (p1 < SIZE(closeS) && Det(c, (*openS[p1]), (*closeS[p2])) > 0) p1++; else p2++;
			if (p1 >= p2) {
				cout << x+1 << endl;
				break;
			}
		}
	}
	return 0;
}
