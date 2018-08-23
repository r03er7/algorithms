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
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
  VI vis;
  Graph<V,E> *sccRes;
  void SccDfs(int v,int nr, bool phase){
    g[v].t = 1;
	if(!phase) vis[v] = nr;
    FOREACH(it, g[v]) if (g[it->v].t == -1)
		SccDfs(it->v, nr, phase); else 
		if(!phase && nr > vis[it->v])
		sccRes->EdgeD(g[it->v].t, vis[it->v]=nr);
	if(phase) vis.PB(v); else g[v].t = nr;
  }
  Graph<V,E> Scc() {
    Graph<V,E> gt(SIZE(g)),res(SIZE(g)),*tab[]={this, & gt};
    gt.sccRes=&res; gt.vis.resize(SIZE(g), -1); vis.clear();
    REP(i,SIZE(g)) FOREACH(it,g[i]) gt.EdgeD(it->v,i);
    REP(i,2){
      FOREACH(it,tab[i]->g) it->t = -1;
      int comp=0,v;
      FORD(j,SIZE(g)-1,0)
        if (tab[i]->g[v=(i?vis[j]:j)].t == -1) tab[i]->SccDfs(v,comp++,1-i);
      if (i) res.g.resize(comp);
    }
    REP(i,SIZE(g)) g[i].t=gt.g[i].t;
    return res;
  }
};
struct Vs {int t; bool c,n; Vs(){c=n=false;}};
struct Empty {};
Graph<Vs, Empty> gr;
Graph<Empty, Empty> grTr;

void markUsed(int v) {
	if (!gr.g[v].n) {
		gr.g[v].n = true;
		FOREACH(it, grTr.g[v])
			markUsed(it->v);
	}
}

void mark(int v) {
	if (!gr.g[v].n) {
		gr.g[v].n = gr.g[v].c = true;
		markUsed(v^1);
		FOREACH(it, gr.g[v])
			mark(it->v);
	}
}

int main() {
	int n, m, b, e;
	cin >> n >> m;
	gr.g.resize(2*n);
	grTr.g.resize(2*n);
	REP(x, m) {
		cin >> b >> e;
		gr.EdgeD(--b, (--e)^1);
		gr.EdgeD(e, b^1);
		grTr.EdgeD(e^1, b);
		grTr.EdgeD(b^1, e);
	}
	gr.Scc();
	VI rep(SIZE(gr.g), -1);
	REP(x, 2*n) {
		rep[gr.g[x].t] = x;
	}
	FORD(x, SIZE(gr.g)-1, 0) if(rep[x] != -1) mark(rep[x]);
	int size = 0;
	REP(x, 2*n) {
		if (gr.g[x].c) {
			size++;
			FOREACH(it, gr.g[x]) 
				if (gr.g[it->v^1].c) size = n+1;
		}
		if (gr.g[x].c == gr.g[x^1].c) size = n+1;
	}
	if (size != n)
		cout << "NIE" << endl;
	else
		REP(x, 2*n) if (gr.g[x].c) cout << x+1 << endl;
	return 0;
}
