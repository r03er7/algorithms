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
void SetPartition(int n, void (*fun)(VI&)) { 
	VI B(n, 1), N(n + 1), P(n + 1);
	vector<bool> Pr(n + 1, 1);
	N[1] = 0;
	fun(B);
	for(int i, k, j = n; j > 1;) {
		k = B[j - 1];
		if(Pr[j]) {
			if(!N[k]) P[N[k] = j + (N[j] = 0)] = k;
		    	if(N[k] > j) N[P[j] = k] = P[N[j] = N[k]] = j;
			B[j - 1] = N[k];
		} else {
			B[j - 1] = P[k];
			if(k == j) N[k] ? P[N[P[k]] = N[k]] = P[k] : N[P[k]] = 0;
		}
		fun(B);
		j = n;
		while(j > 1 && ((Pr[j] && (B[j - 1] == j)) 
			|| (!Pr[j] && (B[j - 1] == 1)))) Pr[j--] = !Pr[j];
	}
}
void Display(VI& v) {
	static int calc = 0;
	if (!(calc++ % 6)) cout << endl;
	FOREACH(it, v) cout << *it << " ";
	cout << "\t";
}

int main() {
	SetPartition(4, &Display);
	return 0;
}
