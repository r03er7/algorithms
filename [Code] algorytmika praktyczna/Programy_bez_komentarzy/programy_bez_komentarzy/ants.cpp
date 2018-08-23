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
};
struct Ve {int rev;};
struct Vs {int t, s;};

int kpos[1000], knr[1000], lst[1000];

void Mark(Graph<Vs, Ve> &g, int v, int t) {
	g.g[v].t = t;
	FOREACH(it, g.g[v]) if (g.g[v].s != it->v && g.g[it->v].t == INF)
			Mark(g, it->v, t);
}

int main() {
	int n, b, e, k, l;
	cin >> n;
	Graph<Vs, Ve> g(n);
	REP(x, n-1) {
		cin >> b >> e;
		g.EdgeU(b-1, e-1);
	}
	cin >> k;
	REP(x, k) {
		cin >> kpos[x];
		kpos[x]--;
		knr[x] = 0;
	}
	cin >> l;
	while(l--) {
		int len = k, nlen, t = 2;
		cin >> b;
		g.Bfs(--b);
		REP(y, n) g.g[y].t = INF;
		REP(y, k) Mark(g, kpos[lst[y] = y], 0);
		while(len) {
			REP(y, len) {
				if (kpos[lst[y]] == b) {
					knr[lst[y]]++;
					len = 0;
				} else 
				if (g.g[e=g.g[kpos[lst[y]]].s].t < t) lst[y] = -1; else {
					Mark(g, kpos[lst[y]] = e, t);
					g.g[e].t = 0;
				}
			}
			nlen = 0;
			REP(x, len) if (lst[x] != -1) lst[nlen++] = lst[x];
			len = nlen;
			t++;
		}
	}
	REP(x, k) cout << kpos[x]+1 << " " << knr[x] << endl;
	return 0;
}
