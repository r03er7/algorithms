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
#include <set>
void SubsetKLex(int k, int n, void (*fun)(VI&)) {
    int i, p=k;
    VI A(k);
    REP(x,k) A[x]=x;
    while(p) {
		fun(A);
		A[k-1]==n-1 ? p-- : p=k;
		if(p) FORD(i,k,p) A[i-1]=A[p-1]+i-p+1;
    }
}
void Display(VI& v) {
	static int calc = 0;
	if (!(++calc % 6)) cout << "\n";
	FOREACH(it, v) cout << *it << " ";
	cout << "\t";
}

int main() {
	SubsetKLex(4, 7, &Display);
	return 0;
}
