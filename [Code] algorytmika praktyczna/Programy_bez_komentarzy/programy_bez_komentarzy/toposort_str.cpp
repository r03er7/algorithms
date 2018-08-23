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
  int topo;
  void TopoDfs(int v){
	  if (!g[v].t) {
		g[v].t=1; 
		FOREACH(it,g[v]) TopoDfs(it->v);
		g[v].t=--topo;
	  }
  }
  void TopoSort(){
    FOREACH(it,g) it->t=0; topo=SIZE(g);
	FORD(x,topo-1,0) TopoDfs(x);
  }
  VI TopoSortV(){
    VI res(SIZE(g));
    TopoSort();
    REP(x,SIZE(g)) res[g[x].t] = x;
    return res;
  }
};
struct Ve {}; 
struct Vs {
	int t;
};
int main() {
	int n, m, b, e;
	cin >> n >> m;
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e;
		g.EdgeD(b, e);
	}
	VI res = g.TopoSortV();
	cout << "Kolejnosc topologiczna wierzcholkow: ";
	FOREACH(it, res) cout << *it << " ";
	cout << endl;
	REP(x, SIZE(g.g)) cout << "Wierzcholek " << x << " ma pozycje " <<
		g.g[x].t << " w porzadku topologicznym" << endl;
	return 0;
}
