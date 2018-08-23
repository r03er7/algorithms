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
  VI Hopcroft(){
    int n=SIZE(g); 
	VI res(n,-1);
	vector<char> l;
	if (!BiPart(l)) return res;
	g.resize(n+2);
	REP(i,n) if (!l[i]) EdgeD(n,i); else EdgeD(i,n+1);
	UnitFlow(n,n+1);
	REP(i,n) if (l[i] && g[i][0].v!=n+1)
		res[ res[g[i][0].v]=i ]=g[i][0].v;
    return res;
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
struct Ve {};
struct Vs {int t, s; bool rem; Vs() : rem(0){}};

#define Vnr(x,y) ((x)*n+y)

int main() {
	int n,m,wx,wy;
	cin >> n >> m;
	Graph<Vs,Ve> gr(n*n);
	REP(x, m) {
		cin >> wx >> wy;
		gr.g[Vnr(wx-1,wy-1)].rem = 1;
	}
	REP(x,n) REP(y,n) if ((x+y)&1 && !gr.g[Vnr(x,y)].rem) {
#define Add(px,py) if (px >= 0 && py >= 0 && px < n && py < n && !gr.g[Vnr(px,py)].rem) gr.EdgeD(Vnr(x,y),Vnr(px,py));
		Add(x-1,y-2);
		Add(x-2,y-1);
		Add(x-1,y+2);
		Add(x-2,y+1);
		Add(x+1,y-2);
		Add(x+2,y-1);
		Add(x+1,y+2);
		Add(x+2,y+1);
	}
	VI res = gr.Hopcroft();
	int val = 0;
	REP(x, SIZE(res)) if (res[x] != -1) val++;
	cout << n*n - m - val/2 << endl;
	return 0;
}
