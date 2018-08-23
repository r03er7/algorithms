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
typedef pair<int,int> PII;
typedef vector<PII> VPII;
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
  int id,l;
typedef typename vector<Ed>::iterator EIT;
  vector<EIT> qu;
#define DccMark(bri) e->dcc = g[e->v][e->rev].dcc = id, \
  e->bridge = g[e->v][e->rev].bridge = bri
  void Dcc(){
    id=l=0; qu.clear();
    FOREACH(it,g) it->d=-1; 
    REP(i,SIZE(g)) if (g[i].d==-1) DccSearch(i,-1);
  }
  void DccSearch(int v,int u){
      EIT e;
      g[v].d=g[v].low=l++;
      FOREACH(it,g[v]){
        int w=it->v;
        if (g[w].d==-1){
          qu.PB(it);
          DccSearch(w,v);
          if (g[w].low>=g[v].d){
			  int cnt=0;
            do{
              e=qu.back();
              DccMark(0);
              qu.pop_back(); cnt++;
            } while (e!=it);
            if (cnt==1) DccMark(1);
            id++;
          } else g[v].low = min(g[v].low, g[w].low);
        } else if (g[w].d<g[v].d && w!=u) qu.PB(it), g[v].low = min(g[v].low, g[w].d);
      }
  }
  int s;
  VPII *X;
  void Bridges(VPII &res){
    res.clear();
    X=&res;
    s=0;
    FOREACH(it,g) it->d=-1;
    REP(i,SIZE(g)) if (g[i].d==-1) BriSearch(i,-1);
  }
  void BriSearch(int v,int u){
      g[v].d=g[v].low=s++;
      FOREACH(it,g[v]){
        int w=it->v;
        if (g[w].d==-1){
          BriSearch(w,v);
          if (g[w].low>g[v].d){
            X->PB(MP(min(v, w), max(v, w) ));  
          } else g[v].low = min(g[v].low, g[w].low);
        } else if (w!=u) g[v].low = min(g[v].low, g[w].d);
      }
  }
int t;
VPII *br;
int BriArtR(int v, int p) {
	int l=g[v].d=++t;
	FOREACH(it, g[v]) if (it->v != p)
		l = min(l, !g[it->v].d ? BriArtR(it->v, v) : g[it->v].d);
	if(g[p].d<=l) g[p].art = 1;
	if(g[p].d<l) br->PB(MP(min(v, p), max(v, p)));
	return l;
}
void BriArt(VPII &res) {
	res.clear(); br=&res;
	t=0;
	REP(x, SIZE(g)) g[x].art=g[x].d=0;
	REP(x, SIZE(g)) if(!g[x].d) {
		g[x].d=++t;
		int c = 0;
		FOREACH(it, g[x]) if (!g[it->v].d) {c++; BriArtR(it->v, x);}
		g[x].art=(c>1);
	}
}
};
struct VsBridges { 
	int d, low;
};
struct VeBridges {
	int rev;
};
struct VsDcc {
	int d, low;
};
struct VeDcc {
	int rev, dcc; 
	bool bridge;
};
struct VsBriArt {
	int d; 
	bool art;
};
struct VeBriArt {
	int rev;
};
int main() {
	int n, m, b, e;
	cin >> n >> m;
	Graph<VsBridges, VeBridges> g1(n);
	Graph<VsDcc, VeDcc> g2(n);
	Graph<VsBriArt, VeBriArt> g3(n);
	REP(x, m) {
		cin >> b >> e;
		g1.EdgeU(b, e);
		g2.EdgeU(b, e);
		g3.EdgeU(b, e);
	}
	VPII res1;
	g1.Bridges(res1);
	FOREACH(it, res1) 
		cout << "E(" << it->ST << "," << it->ND << ")" << endl;
	g2.Dcc();
	REP(x, SIZE(g2.g)) FOREACH(it, g2.g[x]) if (x < it->v) {
		if (it->bridge)
			cout << "(" << x << "," << it->v << ") - most" << endl;
		cout << "E(" << x << "," << it->v << ") - " << 
			it->dcc << endl;
	}
	VPII res3;
	g3.BriArt(res3);
	FOREACH(it, res3) 
		cout << "E(" << it->ST << ", " << it->ND << ") - most" << endl;
	REP(x, SIZE(g3.g)) 
		if (g3.g[x].art) cout << x << " - punkt art." << endl;
	return 0;
}
