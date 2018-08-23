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
void SubsetMin(int n, void (*fun)(vector<bool>&, int)) {  
	vector<bool> B(n, 0);
	fun(B, -1);
	for(int i = 0, p = 0, j; p < n;) {
		for(p = 0, j = ++i; j & 1; p++) j >>= 1;
		if(p < n) {
			B[p] =! B[p];
			fun(B, p);
		}
    }
}
void Display(vector<bool>& v, int k) {
	if (k != -1) {
		if (v[k]) cout << "Do zbioru zostal dodany element " << k << endl;
		else cout << "Ze zbioru zostal usuniety element " << k << endl;
	}
	cout << "Podzbior: ";
	FOREACH(it, v) cout << *it << " ";
	cout << endl;
}

int main() {
	SubsetMin(3, &Display);
	return 0;
}
