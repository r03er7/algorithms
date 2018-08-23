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
struct Ve {int rev;};
struct Vs {
	int d, f, s; 
	VI l;
};

#define Desc(n,m) (g->g[n].d <= g->g[m].d && g->g[n].f >= g->g[m].f)
int LCA(Graph<Vs, Ve> *g, int b, int e) {
	int res = 0, p = SIZE(g->g[b].l)-1;
	while(!Desc(b, e)) {
		p = min(p, SIZE(g->g[b].l)-1);
		while(p>0 && Desc(g->g[b].l[p], e)) p--;
		res += (1<<p);
		b = g->g[b].l[p];
	}
	return res;
}

void GenLCA(Graph<Vs, Ve> *g, int v) {
	if (v != 0 && !SIZE(g->g[v].l)) {
		int c = g->g[v].s;
		GenLCA(g, c);
		g->g[v].l.PB(c);
		while(SIZE(g->g[c].l) >= SIZE(g->g[v].l)) {
			c = g->g[c].l[SIZE(g->g[v].l)-1];
			g->g[v].l.PB(c);
		}
	}
}

int main() {
	int n, m, b, e;
	cin >> n;
	Graph<Vs, Ve> gr(n);
	REP(x, n-1) {
		cin >> b >> e;
		gr.EdgeU(b-1, e-1);
	}
	gr.Dfs(0);
	FOR(x,1,n-1) GenLCA(&gr, x);
	cin >> m;
	cin >> b;
	int res = 0;
	REP(x, m-1) {
		cin >> e;
		res += LCA(&gr, b-1, e-1) + LCA(&gr, e-1, b-1);
		b = e;
	}
	cout << res << endl;
	return 0;
}
