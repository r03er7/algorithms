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
bool congr(int a,int b, int p, int q, int& c, int& r)
{
 LL x,y;
 r=GCDW(p,q,x,y);
 if((a-b)%r) return 0;
 x=LL(a)+LL(p)*LL(b-a)/r*x;
 r=LL(p)*LL(q)/r;
 c=x%r;
 if (c<0) c+=r;
 return 1;
}
int main() { 
	int a, b, p, q, c, v;
	while(cin >> a >> p >> b >> q) {
		cout << a << " (mod " << p << "), " << b << 
			" (mod " << q << "), rozwiazanie: ";
		if (congr(a, b, p, q, c, v)) 
			cout << c << " (mod " << v << ")" << endl;
		else cout << "Brak rozwiazan" << endl;
	}
	return 0;
}
