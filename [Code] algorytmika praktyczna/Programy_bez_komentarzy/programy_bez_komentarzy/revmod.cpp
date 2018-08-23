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
int main() {
	int a, m;
	while(cin >> a >> m) {
		cout << "Rownanie: " << a << "*x = 1 (mod " << m << ")" << endl;
		int sol = RevMod(a,m);
		if (sol == -1) 
			cout << "Brak rozwiazan" << endl;
		else
			cout << "x = " << sol << endl;
	}
	return 0;
}
