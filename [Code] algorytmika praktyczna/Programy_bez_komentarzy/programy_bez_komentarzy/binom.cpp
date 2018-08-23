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
LL Binom(int n, int k) { 
#define Mark(x, y) for(int w = x, t = 2; w > 1; t++) \
while(!(w % t)) {w /= t; p[t] += y;}
	if (n < k || n < 0) return 0;
	int p[n + 1];
	REP(x, n + 1) p[x] = 0;
	FOR(x, n - k + 1, n) Mark(x, 1);
	FOR(x, 1, k) Mark(x, -1);
	LL r = 1;
	FOR(x, 1, n) while(p[x]--) r *= x;
	return r;
}
int main() {
	int n, k;
	while(cin >> n >> k)
		cout << "Binom(" << n << "," << k << ") = " << Binom(n,k) << endl;
	return 0;
}
