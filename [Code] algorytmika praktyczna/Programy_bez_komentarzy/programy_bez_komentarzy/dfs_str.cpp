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
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
  void Dfs(int e = -1) {
	VI st(SIZE(g));
	int t = -1 , i = 0, b = 0;
	e==-1 ? e=SIZE(g)-1 : b = e;
	REP(x,SIZE(g)) g[x].d = g[x].f = g[x].s = -1;
	FOR(s,b,e) if(g[s].d == -1) {
		g[st[i++] = s].d = ++t; g[s].f = SIZE(g[s]);
		while(i) {
			int s = st[i-1];
			if (!g[s].f) {g[s].f = ++t; --i;} else {
				if (g[s = g[s][--g[s].f].v].d == -1) {
					g[s].s = st[i-1];
					g[s].f = SIZE(g[s]);
					g[st[i++] = s].d = ++t;
				}
			}
		}
	}
}
};
struct Ve {
	int rev;
};
struct Vs {
	int d, f, s;
};
int main() { 
	int n, m, s, b, e;
	cin >> n >> m >> s;
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e;
		g.EdgeU(b, e);
	}
	g.Dfs(s);
	REP(x, SIZE(g.g)) cout << "Wierzcholek " << x << ": czas wejscia = " <<
		g.g[x].d << ", czas wyjscia = " << g.g[x].f << 
		", ojciec w lesie DFS = " << g.g[x].s << endl;
	return 0;
}
