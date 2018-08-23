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
int nr;
void SccSDfs(int v){
	if (g[v].t == -1) {
		g[v].t = nr;
		FOREACH(it, g[v]) SccSDfs(it->v);
		if (nr < 0) g[v].t = -(--nr)-3;
	}
}
void SccS() {
	Graph<V,E> gt(SIZE(g));
	REP(x,SIZE(g)) {
		g[x].t = gt.g[x].t = -1;
		FOREACH(it, g[x]) gt.EdgeD(it->v, x);
	}
	gt.nr = -2; nr = 0;
	VI v(SIZE(g));
	REP(x, SIZE(g)) { gt.SccSDfs(x); v[gt.g[x].t] = x;}
	FORD(x, SIZE(g)-1, 0) { SccSDfs(v[x]); nr++; }
}
};
struct Vs{int t;};
struct Ve{};

int main() {
	int n, m, b, e;
	cin >> n >> m;
	Graph<Vs,Ve> gr(n);
	REP(x, m) {
		cin >> b >> e;
		gr.EdgeD(b-1, e-1);
	}
	gr.SccS();
	vector<bool> inD(n,false), outD(n,false), notEmpty(n,false);
	int inVal = 0, outVal = 0, sccC = 0;
	REP(x, n) {
		if (!notEmpty[gr.g[x].t]) {
			notEmpty[gr.g[x].t] = true;
			sccC++;
		}
		FOREACH(it, gr.g[x]) if (gr.g[x].t != gr.g[it->v].t)
			outD[gr.g[x].t] = inD[gr.g[it->v].t] = true;
	}
	REP(x, n) {
		if (!inD[x] && notEmpty[x]) inVal++;
		if (!outD[x] && notEmpty[x]) outVal++;
	}
	if (sccC == 1) inVal = outVal = 0;
	cout << max(inVal, outVal) << endl;
	return 0;
}
