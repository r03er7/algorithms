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
  void Bfs(int s) {
	FOREACH(it, g) it->t=it->s=-1; g[s].t=0;
	int qu[SIZE(g)],b,e;
    qu[b=e=0]=s;
    while(b<=e) {
      s=qu[b++];
      FOREACH(it, g[s]) if (g[it->v].t==-1) {
        g[qu[++e]=it->v].t=g[s].t+1;
		g[it->v].s=s;
      }
    }
  }
};
struct Ve {
	int rev;
}; 
struct Vs {
	int t, s;
};
int main() {
	int n, m, s, b, e;
	cin >> n >> m >> s;
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e;
		g.EdgeU(b, e);
	}
	g.Bfs(s);
	REP(x, n) cout << "Wierzcholek " << x << ": czas = " << g.g[x].t << 
		", ojciec w lesie BFS = " << g.g[x].s << endl;
	return 0;
}
