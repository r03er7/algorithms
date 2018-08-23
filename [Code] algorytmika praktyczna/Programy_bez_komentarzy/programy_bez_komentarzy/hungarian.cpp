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
const int INF = 1000000001;
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
VI HungarianG() {
	vector<char> l;
	VI re(SIZE(g), -1);
	if (!BiPart(l)) return re;
	int gr[SIZE(g)], rel[2][SIZE(g)], n = 0, m = 0;
	REP(x, SIZE(g)) rel[l[x]][gr[x] = (l[x] ? n++ : m++)] = x;
	int *w[n >?= m];
	REP(i,n) {
		w[i] = new int[n];
		REP(j,n) w[i][j] = -INF;
	}
	REP(x, SIZE(g)) FOREACH(it, g[x]) 
		w[min(gr[x], gr[it->v])][max(gr[x], gr[it->v])] = max(w[min(gr[x], gr[it->v])][max(gr[x], gr[it->v])], it->c);
	VI res = Hungarian(w, n);
	REP(x,SIZE(res)) if (w[x][res[x]] != -INF) {
		re[rel[0][x]] = rel[1][res[x]];
		re[rel[1][res[x]]] = rel[0][x];
	}
	REP(i,n) delete []w[i];
	return re;
}
};
VI Hungarian(int **w,int n){
  int lx[n],ly[n],skojx[n],skojy[n];
  int markx[n],marky[n],sl[n],par[n],q[n];
  REP(i,n){ skojx[i]=skojy[i]=-1; ly[i]=0; lx[i]=*max_element(w[i], w[i]+n); }
  REP(k,n){
    int v=-1,qb=0,qe=0;
    REP(i,n){ marky[i]=markx[i]=0; sl[i]=-1; if (skojx[i]==-1) q[qe++]=i;}
    while (v==-1){
      while (qb<qe){
        int i=q[qb++]; markx[i]=1;
        REP(j,n)
          if (!marky[j] && (sl[j]==-1 || sl[j]>lx[i]+ly[j]-w[i][j])){
            if ((sl[j] = lx[ par[j]=i ]+ly[j]-w[i][j]) == 0){
              marky[j]=1;
              if (skojy[j]!=-1) q[qe++]=skojy[j]; else {v=j; goto end;}
            }
          }
      }
      int x=-1; REP(i,n) if (!marky[i] && (x==-1 || sl[i] < x)) x=sl[i];
      REP(i,n){
        if (markx[i]) lx[i]-=x; 
        if (marky[i]) ly[i]+=x; else
          if ((sl[i] -= x) == 0){
            marky[i]=1; if (skojy[i] != -1) q[qe++]=skojy[i]; else v=i;
          }
      }
    }
end:
    while (v!=-1){int y=skojx[par[v]]; skojx[par[v]]=v; skojy[v]=par[v]; v=y;}
  }
  return VI(skojx,skojx+n);
}
struct Vs {int t,s;};
struct Ve {int c,rev;};

int main(){
	int n, m, s, b, e;
	cin >> n >> m;
	Graph<Vs, Ve> g(n);
	Ve l;
	REP(x,m) {
		cin >> b >> e >> l.c;
		g.EdgeU(b, e, l);
	}
	VI res = g.HungarianG();
	REP(x, SIZE(res)) if (res[x] > x) 
		cout << "Wierzcholek " << x << " skojarzono z " << res[x] << endl;
	return 0;
}
