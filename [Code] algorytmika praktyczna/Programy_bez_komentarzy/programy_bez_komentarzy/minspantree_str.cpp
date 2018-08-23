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
#include <set>
const int INF = 1000000001;
typedef pair<int,int> PII;
#define MP make_pair
template<class V, class E> struct Graph {
	struct Ed : E {
		int v; 
		Ed(E p, int w) : E(p), v(w) {}
	};
	struct Ve : V,vector<Ed> {};
	vector<Ve> g;
	Graph(int n=0) : g(n) {}
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
int MinSpanTree() {
	int r = 0, d[SIZE(g)];
	bool o[SIZE(g)];
	REP(x, SIZE(g)) { d[x] = INF; o[x] = 0;}
	set<PII> s;
	s.insert(MP(d[0]=0,0));
	while(!s.empty()) {
		int v = (s.begin())->ND; s.erase(s.begin());
		bool t = 0;
		o[v] = 1;
		r += d[v];
		FOREACH(it, g[v]) {
			it->span = 0;
			if (!t && o[it->v] && it->l == d[v])
				t = it->span = g[it->v][it->rev].span = 1; else
			if (!o[it->v] && d[it->v] > it->l) {
				s.erase(MP(d[it->v], it->v));
				s.insert(MP(d[it->v] = it->l, it->v));
			}
		}
	}
	return r;
}
};
struct Ve { 
	int rev, l; 
	bool span;
};
struct Vs {};
int main() {
	int n, m, b, e;
	cin >> n >> m;
	Ve l;
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e >> l.l;
		g.EdgeU(b, e, l);
	}
	cout << "Waga minimalnego drzewa rozpinajacego: " << 
		g.MinSpanTree() << endl << "Krawedzie nalezace do drzewa:";
	REP(x, SIZE(g.g)) FOREACH(it, g.g[x]) if (it->span && it->v < x) 
		cout << " (" << it->v << ", " << x << ")";
	cout << endl;
	return 0;
}
