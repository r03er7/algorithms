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
bool MDfs(int x){
	if (!g[x].t) {
		g[x].t=1;
		FOREACH(it,g[x]) if (g[it->v].m==-1 || MDfs(g[it->v].m)){
			g[ g[it->v].m=x ].m=it->v; return true;
		}
	}
    return false;
}
bool BipMatching(){
	vector<char> l;
	if (!BiPart(l)) return 0;
	int n=SIZE(g),p=1; 
	FOREACH(it,g) it->m=-1;
	while (p) {
		p=0; FOREACH(it,g) it->t=0;
		REP(i,n) if (l[i] && g[i].m==-1) p|=MDfs(i);
	}
	return 1;
}
bool BiPart(vector<char> &v) {
	v.resize(SIZE(g),2);
	VI r = TopoSortV();
	FOREACH(x, r) {
		if(v[*x]==2) v[*x]=0;
		FOREACH(it, g[*x]) if (v[it->v]==2)
				v[it->v] = 1-v[*x];
			else if (v[it->v] == v[*x])
				return 0;
	}
	return 1;
}
};
struct Ve{int rev;};
struct Vs{int m,t;};

int main() {
	int n, m, s, b, e;
	cin >> n >> m;
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e;
		g.EdgeU(b, e);
	}
	if (g.BipMatching()) REP(x, SIZE(g.g)) if (g.g[x].m > x) 
		cout << "Wierzcholek " << x << " skojarzono z " << g.g[x].m << endl;
	return 0;
}
