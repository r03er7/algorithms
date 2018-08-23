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
#define Nr(x,y) (wy*(x)+y)
#define Mark(ox,oy) if (ox >= 0 && oy >= 0 && ox < wx && oy < wy) equ[Nr(x,y)][Nr(ox,oy)] = 1;

int main() {
	int wx, wy;
	cin >> wx >> wy;
	vector<bitset<225> > equ(wx*wy);
	vector<string> mp(wy);
	VI vals(wx*wy,0), res;
	REP(y, wy) cin >> mp[y];
	REP(x, wx) REP(y, wy) {
		Mark(x, y);
		Mark(x-1, y);
		Mark(x+1, y);
		Mark(x, y-1);
		Mark(x, y+1);
		if (mp[y][x] == '0') vals[Nr(x,y)] = 1;
	}
	int r = GaussZ2<225>(equ, vals, res);
	if (r < 0) cout << "-1"  << endl; else {
		int count = 0;
		REP(x, wx*wy) if (res[x]) count++;
		cout << count << endl;
		REP(x, wx) REP(y, wy) if (res[Nr(x,y)]) cout << y+1 << " " << x+1 << endl;
	}
	return 0;
}
