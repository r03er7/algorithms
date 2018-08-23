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
VI PalRad(const char *x, bool p) 
{
	int n = strlen(x), i = 1, j = 0, k;
	VI r(n, 0);
	while(i < n) {
		while(i + j + p < n && i > j && x[i - j - 1] == x[ i + j + p]) j++;
		for(r[i] = j, k = 0; ++k <= j && r[i - k] != j - k;) 
			r[i + k] = min(r[i - k], j - k);
		j = max(0, j - k);
		i += k;
	}
	return r;
}
char t[205];
VI rad;

void Disp(VI& v, int p) {
	if (p > 0) {
		Disp(v, v[p]);
		FOR(y,v[p],p-1) cout << t[y];
		cout << " ";
	}
}

int main() {
	VI minV(205, 9), maxV(205, 0);
	VI minS(205), maxS(205);
	minV[0]=0;
	cin >> t;
	int l = strlen(t);
	rad = PalRad(t, 0);
	REP(x,l) FOR(y, 1, rad[x]) {
		if (minV[x+y] > minV[x-y]+1) {
			minS[x+y] = x-y;
			minV[x+y] = minV[x-y]+1;
		}
		if (maxV[x+y] < maxV[x-y]+1) {
			maxS[x+y] = x-y;
			maxV[x+y] = maxV[x-y]+1;
		}
	}
	if (!maxV[l]) cout << "NIE" << endl; else {
		Disp(minS, l); cout << endl;
		Disp(maxS, l); cout << endl;
	}
	return 0;
}
