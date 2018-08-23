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
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
};
struct FAU {
    int *p,*w;
	FAU(int n) : p(new int[n]), w(new int[n]) {
		REP(x,n) p[x]=w[x]=-1;
    }
    ~FAU() {delete[] p; delete[] w;}
    int Find(int x) {
	return (p[x] < 0) ? x : p[x]=Find(p[x]);
    }
    void Union(int x, int y) {
	if ((x=Find(x))==(y=Find(y))) return;
	if (w[x] > w[y])
		p[y] = x; else p[x] = y;
	if (w[x] == w[y])
		w[y]++;
	}
};
struct monkey {
	int hand[2];
	bool rel[2];
	int time;
};

struct move {
	int monkey, hand;
};

struct Ve {int rev;};
struct Vs {};
Graph<Vs,Ve> gr;
vector<monkey> mon;
vector<move> act;

void SetTime(int v, int t) {
	if (mon[v].time == -1) {
		mon[v].time = t;
		FOREACH(it, gr.g[v]) SetTime(it->v, t);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	mon.resize(n);
	act.resize(m);
	REP(x, n) {
		cin >> mon[x].hand[0] >> mon[x].hand[1];
		--mon[x].hand[0];
		--mon[x].hand[1];
		mon[x].rel[0] = mon[x].rel[1] = false;
		mon[x].time = -1;
	}
	REP(x, m) {
		cin >> act[x].monkey >> act[x].hand;
		--act[x].monkey;
		--act[x].hand;
		mon[act[x].monkey].rel[act[x].hand] = true;
	}
	FAU fau(n);
	gr.g.resize(n);
	REP(x, n) REP(y, 2) if (!mon[x].rel[y] && mon[x].hand[y] != -2) {
		fau.Union(x, mon[x].hand[y]);
		gr.EdgeU(x, mon[x].hand[y]);
	}
	int e[2]; bool ground[2];
	FORD(x, m-1, 0) {
		e[0] = act[x].monkey;
		e[1] = mon[act[x].monkey].hand[act[x].hand];
		REP(y, 2) ground[y] = fau.Find(e[y]) != fau.Find(0);
		fau.Union(e[0], e[1]);
		REP(y, 2) if (ground[y] && fau.Find(e[y]) == fau.Find(0))
			SetTime(e[y], x);
		gr.EdgeU(e[0], e[1]);
	}
	REP(x, n) cout << mon[x].time << endl;
	return 0;
}
