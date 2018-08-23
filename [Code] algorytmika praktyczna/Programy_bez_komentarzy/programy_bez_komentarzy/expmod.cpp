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
int ExpMod(int a, int b, int q) {
    LL p=1;
    while(b>0) {
	if (b&1) p=(LL(a)*p)%q;
	a=(LL(a)*LL(a))%q;
	b/=2;
    }
    return p;
}
int main() { 
	int a, b, q;
	while(cin >> a >> b >> q) cout << a << " do potegi " << b << 
		" (mod " << q << ") = " << ExpMod(a,b,q) << endl;
	return 0;
}
