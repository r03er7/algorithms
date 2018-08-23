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
#define TPL template<class T> inline
#define CR(t) const t&
#define RET return
TPL T gcd(CR(T)a,CR(T)b) { RET b?gcd(b,a%b):a; }
LL GCD(LL a,LL b) { 
	while(b) swap(a%=b,b);
	return a;
}
int GCDW(int a, int b, LL &l, LL &k) {
    if (!a) { 
		l=0; k=1; return b; }
    int d = GCDW(b%a, a, k, l);
    l -= (b/a)*k;
    return d;
}
LL Offset(LL a, LL b, LL c)
{
	if (a == 0) return b == 0 ? 0 : -1;
	LL v1, v2, dz;
	dz = GCDW(a, c, v1, v2);
	if (b % dz != 0) return -1;
	dz = b / dz;
	v1 *= dz;
	v2 *= dz;
	LL pos = -v1*a, layer = c*(a/GCD(a,c));
	pos %= layer;
	if (pos < 0) pos += layer;
	return pos;
}

int main()
{
	LL sx, sy, px, py, wx, wy;
	cin >> sx >> sy >> px >> py >> wx >> wy;
	sx /= 2;
	bool rotx = false, roty = false;
	if (wx < 0) {
		rotx = true;
		wx = -wx;
		px = 2*sx - px;
	}
	if (wy < 0) {
		roty = true;
		wy = -wy;
		py = sy - py;
	}
	LL nw = GCD(wx, wy);
	if (nw) {
		wx /= nw;
		wy /= nw;
	}
	LL wsp = Offset(wx, px, sx);
	if (wsp == -1) {
		cout << "NIE" << endl;
		return 0;
	}
	if (wsp) {
		px = (px + wsp) % (4*sx);
		py = (py + (wsp/wx)*wy) % (2*sy);
	}
	wsp = Offset(wy*(sx/GCD(sx, wx)), py % sy, sy);
	if (wsp == -1) {
		cout << "NIE" << endl;
		return 0;
	}
	if (wsp) {
		py += wsp;
		px += (wsp/wy)*wx;
	}
	if (rotx)
		px = -px + sx*2;
	if (roty)
		py = -py + sy;
	cout << (((py % (2*sy)) == 0) ? 'D' : 'G');
	if ((px % (4*sx)) == 0) 
		cout << "L" << endl;
	else if ((px % (2*sx)) == 0)
		cout << "P" << endl;
	else
		cout << "S" << endl;
	return 0;
}
