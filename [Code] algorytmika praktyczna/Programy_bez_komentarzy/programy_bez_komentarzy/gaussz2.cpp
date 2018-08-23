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
#include <bitset>
template<const int s> int GaussZ2(vector<bitset<s> > equ, VI vals, VI &res) {
	int n=SIZE(equ),a=0,b=0,c;
	res.resize(s, 0);
	for(;a<n && b<s;b++) {
		for(c=a; c<n && !equ[c][b]; c++);
		if (c<n) {
			if (a!=c) {equ[a]^=equ[c]; vals[a]^=vals[c];}
			REP(y,n) if(a!=y && equ[y][b]) {equ[y]^=equ[a]; vals[y]^=vals[a];}
			res[b]=++a;
		}
  }
  REP(x,b) if (res[x]) res[x] = vals[res[x]-1];
  REP(x,n) {
    c=0;
    REP(z,s) if(equ[x][z]) c^=res[z];
    if (c!=vals[x]) return -1;
  }
  return s-a;
}
int main() {
  vector<bitset<4> > equ(4);
  VI vals(4), res;
  equ[0][1] = equ[0][2] = 1; vals[0] = 0;
  equ[1][1] = equ[1][3] = 1; vals[1] = 1;
  equ[2][1] = equ[2][3] = equ[2][4] = 1; vals[2] = 0;
  cout << "Wymiar przestrzeni rozwiazan: " << GaussZ2<4>(equ, vals, res) << endl;
  REP(z, SIZE(res)) cout << "x" << z << " = " << res[z] << endl;
  return 0;
}
