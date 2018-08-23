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
  void mvFlow(int v, Ed &e){
    int u=e.v;
    g[u].PB(e); g[u].back().v=v;
    swap(g[v].back(),e); g[v].pop_back();
  }
  int Ue;
  bool UFDfs(int v){
    if (v==Ue) return true;
    g[v].s=1;
    FOREACH(it,g[v])
      if (g[it->v].t==1+g[v].t && !g[it->v].s && UFDfs(it->v)){
        mvFlow(v,*it); return true;
    }
    return false;
  }
  int UnitFlow(int v1,int v2){
    int res=0; Ue=v2;
    while (1){
      Bfs(v1);
      if (g[v2].t==-1) break;
      FOREACH(it,g) it->s=0;
      FOREACH(it,g[v1]) if (UFDfs(it->v)) {res++; mvFlow(v1, *it--);}
    }
    return res;
  }
};
struct Ve {}; 
struct Vs {
	int t,s;
};
int main() {
	int n, m, s, f, b, e;
	cin >> n >> m >> s >> f;
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e;
		g.EdgeD(b, e);
	}
	cout << "Przeplyw miedzy wierzcholkami " << s << " i " << f << 
		" wynosi " << g.UnitFlow(s, f) << endl;
	return 0;
}
