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
bool MaR(LL x,LL n) {
    if (x>=n) return 0;
    LL d=1,y;
    int t=0,l=n-1;
    while (!(l&1)) {++t; l>>=1;}
    for(;l>0 || t--;l>>=1) {
	if(l&1) d=(d*x)%n;
	if(!l) {x=d; l=-1;}
        y=(x*x)%n;
	if(y==1 && x!=1 && x!=n-1) return 1;
	x = y;
    }
    return x!=1;
}
bool IsPrime(int x) {
    return !(x<2 || MaR(2,x) || MaR(3,x) || MaR(5,x) || MaR(7,x));
}
int main() {
	int b, e, count = 0;
	cin >> b >> e;
	while(b<e) {
		if (IsPrime(b)) cout << b << (!(++count % 5) ? "\n" : "\t");
		b++;
	}
	return 0;
}
