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
#include <set>
const int INF = 1000000001;
template<class V, class E> struct Graph {
	struct Ed : E {
		int v; 
		Ed(E p, int w) : E(p), v(w) {}
	};
	struct Ve : V,vector<Ed> {};
	vector<Ve> g;
	Graph(int n=0) : g(n) {}
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
  struct djcmp{
    bool operator()(const Ve* a, const Ve* b) const{
      return (a->t==b->t) ? a<b : a->t < b->t;
    }
  };
  void Dijkstra(int s){
    set<Ve*, djcmp> k;
    FOREACH(it, g) it->t = INF, it->s = -1;
    g[s].t = 0; g[s].s = -1; k.insert(&g[s]);
	while(!k.empty()){
      Ve *y = *(k.begin());
      k.erase(k.begin());
      FOREACH(it, *y) if (g[it->v].t > y->t+it->l){
        k.erase(&g[it->v]); g[it->v].t=y->t+it->l;
        g[it->v].s=y-&g[0]; k.insert(&g[it->v]);
      }
    }
  }
};
struct Vs {int t,s;};
struct Ve {int l;};

int main() {
	int n,m,b,e;
	cin >> n;
	int price[n];
	REP(x, n) cin >> price[x];
	Graph<Vs,Ve> gr(n), grTr(n);
	cin >> m;
	Ve str;
	REP(x, m) {
		cin >> b >> e >> str.l;
		gr.EdgeD(--b, --e, str);
		grTr.EdgeD(e, b, str);
	}
	gr.Dijkstra(0);
	grTr.Dijkstra(0);
	int res = INF;
	REP(x, n) res = min(res, price[x]/2+gr.g[x].t+grTr.g[x].t);
	cout << res << endl;
	return 0;
}
