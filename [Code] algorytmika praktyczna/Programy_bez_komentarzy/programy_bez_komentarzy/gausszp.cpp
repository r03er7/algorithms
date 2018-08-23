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
#define TPL template<class T> inline
#define CR(t) const t&
#define RET return
TPL T gcd(CR(T)a,CR(T)b) { RET b?gcd(b,a%b):a; }
int GCDW(int a, int b, LL &l, LL &k) {
    if (!a) { 
		l=0; k=1; return b; }
    int d = GCDW(b%a, a, k, l);
    l -= (b/a)*k;
    return d;
}
int RevMod(int a, int m){ 
	LL x, y;
	if (GCDW(a, m, x, y) != 1) return -1;
	x %= m;
	if (x < 0) x += m;
	return x;
}
int Gauss(vector<VI>& A, VI &b, VI &x, int P){ 
	int m = SIZE(A), n = SIZE(A[0]), k, r;
	VI q;
	for (k = 0; k < min(m, n); k++) {
		int i, j;
		for (j = k; j < n; j++)
			for (i = k; i < m; i++)
				if (A[i][j] != 0) goto found;
		break;
		found:
		if (j != k) REP(t, m) swap(A[t][j], A[t][k]);
		q.PB(j);
		if (i != k) {
			swap(A[i], A[k]); 
			swap(b[i], b[k]);
		}
		FOR(j, k + 1, m - 1) if (A[j][k] != 0) {
			int l = (A[j][k] * RevMod(A[k][k], P)) % P;
			FOR(i, k + 1, n - 1) A[j][i] = (P + A[j][i] - (l * A[k][i]) % P) % P;
			b[j] = (P + b[j] - (l * b[k]) % P) % P;
		}
	}
	r = k;
	x.clear(); 
	x.resize(n, 0);
	FOR(k, r, m - 1) if (b[k] != 0) return -1;
	FORD(k, r - 1, 0) {
		int s = b[k];
		FOR(j, k + 1, r - 1) s = (P + s - (A[k][j] * x[j]) % P) % P;
		x[k] = (s * RevMod(A[k][k], P)) % P;
	}
	FORD(k, r - 1, 0) swap(x[k], x[q[k]]);
	return n - r;
}
int main(){
  vector<VI> a(3, VI(3));
  VI b(3), x;
  a[0][0] = 1, a[0][1] = 3, a[0][2] = 7; b[0] = 0;
  a[1][0] = 4, a[1][1] = 0, a[1][2] = 14; b[1] = 1;
  a[2][0] = 2, a[2][1] = 6, a[2][2] = 8;  b[2] = 2;
  cout << "Wymiar przestrzeni rozwiazan: " << Gauss(a, b, x, 19) << endl;
  REP(i, SIZE(x)) cout << "x" << i << " = " << x[i] << endl;
  return 0;
}
