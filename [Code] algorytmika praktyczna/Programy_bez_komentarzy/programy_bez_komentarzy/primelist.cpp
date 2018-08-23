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
#include <list>
bit_vector Sieve(int s) { 
	bit_vector V(s+1,1);
	V[0] = V[1] = 0;
	FOR(x, 2, s) if(V[x] && LL(s) >= LL(x) * LL(x)) 
		for(int y = x * x; y <= s; y += x) V[y] = 0;
	return V;
}
VI PrimeListS(int s) {
    bit_vector l = Sieve(++s);
    VI V;
    REP(x, s) if (l[x]) V.PB(x);
    return V;
}
int main() {
	int n;
	cin >> n;
	VI l = PrimeListS(n);
	int count = 0;
	cout << "Lista liczb pierwszych mniejszych od " << n << ":" << endl;
	FOREACH(it, l) {
		if (count++) cout << ", ";
		if (!(count % 20)) cout << endl;
		cout << *it;
	}
	return 0;
}
