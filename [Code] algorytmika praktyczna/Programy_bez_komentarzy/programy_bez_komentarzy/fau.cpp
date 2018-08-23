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
int main() {
	int n, m, e1, e2;
	cin >> n >> m;
	FAU fau(n);
	REP(x, m) {
		cin >> e1 >> e2;
		fau.Union(e1, e2);
		cout << "Zlaczenie zbiorow zawierajacych elementy " << 
			e1 << " i " << e2 << endl;
		REP(y, n) cout << "Find(" << y << ") = " << fau.Find(y) << "  ";
		cout << endl;
	}
	return 0;
}
