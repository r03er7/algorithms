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
typedef pair<int,int> PII;
#define MP make_pair
template<class V, class E> struct Graph {
	struct Ed : E {
		int v; 
		Ed(E p, int w) : E(p), v(w) {}
	};
	struct Ve : V,vector<Ed> {};
	vector<Ve> g;
	Graph(int n=0) : g(n) {}
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
  PII MinCostFlow(int v1,int v2){
    int n=SIZE(g);
    PII res=MP(0,0);
	vector<typename vector<Ed>::iterator> vit(SIZE(g));
    while (1){
		FOREACH(it, g) it->t=INF; g[v1].t=0; g[v1].s=-1;
		for(int chg=1,cnt=0;chg && ++cnt<SIZE(g);) {
			chg=0;
			REP(i,SIZE(g)) FOREACH(it,g[i])
			if (g[i].t+it->l<g[it->v].t) {
				g[it->v].t=g[i].t+it->l;
				g[it->v].s=i; vit[it->v]=it; chg=1;
			}
		}
		if (g[v2].t==INF) break;
		res.ST++; res.ND+=g[v2].t;
		int x=v2;
		while (x!=v1){
			int v=g[x].s; swap(*vit[x],g[v].back());
			Ed e=g[v].back(); e.l*=-1; e.v=v;
			g[x].PB(e); g[x=v].pop_back();
		}
	}
	return res;
}
};
struct Vs {
	int t,s;
};
struct Ve {
	int l;
};
int main() {
	int n, m, s, f, b, e;
	cin >> n >> m >> s >> f;
	Graph<Vs, Ve> g(n);
	Ve l;
	REP(x,m) {
		cin >> b >> e >> l.l;
		g.EdgeD(b, e, l);
	}
	cout << "Wyznaczanie przeplywu z " << s << " do " << f << endl;
	PII res = g.MinCostFlow(s, f);
	cout << "Wielkosc przeplywu: " << res.ST;
	cout << ", koszt przeplywu: " << res.ND << endl;
	return 0;
}
