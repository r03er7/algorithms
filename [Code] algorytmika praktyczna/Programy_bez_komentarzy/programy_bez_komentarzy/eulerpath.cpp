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
template<class V, class E> struct Graph {
	struct Ed : E {
		int v; 
		Ed(E p, int w) : E(p), v(w) {}
	};
	struct Ve : V,vector<Ed> {};
	vector<Ve> g;
	Graph(int n=0) : g(n) {}
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
bool EulerD(VI &r) { 
	int v = -1, kr = 1, h;
	r.clear();
	VI l, st(SIZE(g), 0);
	FOREACH(it, g) FOREACH(it2, *it) ++st[it2->v];
	REP(x, SIZE(g)) {
		if ((h = SIZE(g[x])) > st[x]) v = x; else
		if (h && v == -1) v = x;
		kr += st[x] = h;
	}
	if (v != -1) l.PB(v);
	while(SIZE(l)) if (!st[v = l.back()]) {
		l.pop_back();
		r.PB(v);
	} else l.PB(v = g[v][--st[v]].v);
	reverse(ALL(r));
	return SIZE(r) == kr;
}
};
struct Ve{};
struct Vs{};
int main() {
	VI res;
	int n, m, b, e;
	cin >> n >> m;
	Graph<Vs,Ve> g(n);
	REP(x,m) {
		cin >> b >> e;
		g.EdgeD(b, e);
	}
	if (g.EulerD(res)) {
		FOREACH(it, res) cout << *it << " ";
		cout << endl;
	} else {
		cout << "No Euler Path" << endl;
	}
	return 0;
}
