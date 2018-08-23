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
  int out;
#define ITER typename vector<Ed>::iterator
  vector<ITER> itL;
  VI vis;
int FlowDfs(int x,int fl) {
	int r=0, f;
    if (x==out || !fl) return fl;
    for (ITER &it=itL[x]; it!=g[x].end(); ++it) {
		if (vis[x]+1 == vis[it->v] && it->c - it->f) {
			it->f += f = FlowDfs(it->v, min(fl, it->c - it->f)); 
			g[it->v][it->rev].f -= f;
			r+=f; fl-=f;
			if (!fl) break;
		}
	}
	return r;
}
	int MaxFlow(int s,int f){
		int res=0,n=SIZE(g);
		vis.resize(n);
		itL.resize(n);
		out=f;
		REP(x,n) FOREACH(it,g[x]) it->f = 0;
		int q[n],b,e;
		while(1) {
			REP(x, n) vis[x] = -1, itL[x] = g[x].begin();
			for(q[vis[s]=b=e=0]=s;b<=e;++b)
				FOREACH(it,g[q[b]]) if (vis[it->v]==-1 && it->c > it->f)
					vis[q[++e] = it->v] = vis[q[b]] + 1;
			if (vis[f]==-1) break;
			res+=FlowDfs(s,INF);
		}
		return res;
	}
};
struct Ve {int rev, c, f;};
struct Vs {int t;};

int main() {
	int n, m, s, f, b, e;
	cin >> n >> m >> s >> f;
	Graph<Vs, Ve> g(n);
	Ve l; /* newpage */
	REP(x,m) {
		cin >> b >> e >> l.c;
		g.EdgeU(b, e, l);
	}
	cout << "Wielkosc calkowitego przeplywu: " << g.MaxFlow(s, f) << endl;
	cout << "Wartosci przeplywu dla kolejnych krawedzi:" << endl;
	REP(x, SIZE(g.g)) FOREACH(it, g.g[x]) if (it->f > 0) 
		cout << "f(" << x << ", " << it->v << ") = " << it->f << endl;
	return 0;
}
