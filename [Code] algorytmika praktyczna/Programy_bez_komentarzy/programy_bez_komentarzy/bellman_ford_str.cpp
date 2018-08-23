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
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
bool BellmanFord(int v){
	FOREACH(it, g) it->t=INF; g[v].t=0; g[v].s=-1;
    int change,cnt=0;
    do {
      change=0;
      REP(i,SIZE(g)) FOREACH(it,g[i])
        if (g[i].t+it->l<g[it->v].t){
          g[it->v].t=g[i].t+it->l;
          g[it->v].s=i; change=1;
        }
    } while (change && cnt++<SIZE(g));
    return change;
  }
};
struct Ve {
	int l;
}; 
struct Vs {
	int t, s;
};

int main() {
	int n, m, s, b, e;
	Ve ed;
	cin >> n >> m >> s;
	Graph<Vs, Ve> g(n);
	REP(x, m) {
		cin >> b >> e >> ed.l;
		g.EdgeD(b, e, ed);
	}
	g.BellmanFord(s);
	REP(x, SIZE(g.g))
		cout << "Wierzcholek " << x << ": odleglosc od zrodla = " << 
		g.g[x].t << ", ojciec w drzewie najkrotszych sciezek = " << 
		g.g[x].s << endl;
	return 0;
}
