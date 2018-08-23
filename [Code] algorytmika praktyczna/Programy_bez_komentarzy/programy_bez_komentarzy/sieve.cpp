#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <bvector.h>

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
bit_vector Sieve(int s) { 
	bit_vector V(s+1,1);
	V[0] = V[1] = 0;
	FOR(x, 2, s) if(V[x] && LL(s) >= LL(x) * LL(x)) 
		for(int y = x * x; y <= s; y += x) V[y] = 0;
	return V;
}
int main() { 
	int n;
	cin >> n;
	bit_vector V = Sieve(n);
	REP(x, n) cout << x << (V[x] ? " jest liczba pierwsza" 
		: " nie jest liczba pierwsza") << endl;
	return 0;
}
