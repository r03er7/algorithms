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
struct CoverTree { 
#define nr (wp + wk + 1) >> 1
	int *el, *ma, s, p, k, il;
	CoverTree(int size) {
		el = new int[s = 1 << (size + 1)];
		ma = new int[s];
		REP(x, s) el[x] = ma[x] = 0;
	}
	~CoverTree() {
		delete[] el;
		delete[] ma;
	}
	void Mark(int wp, int wk, int g) {
		if(k<=wp || p>=wk) return;
		if(p<=wp && k>=wk) el[g] += il; else {
			Mark(wp, nr, 2 * g); 
			Mark(nr, wk, 2 * g + 1);
		}
		ma[g] = el[g] > 0 ? wk - wp : 
			(wk - 1 == wp ? 0 : ma[2 * g] + ma[2 * g + 1]);
	}
	void Add(int p1, int k1, int i1) {
		p = p1;
		k = k1;
		il = i1;
		Mark(0, s / 2, 1);
	}
    int F(int wp, int wk, int g) {
		if (wp >= k || wk <= p) return 0;
		if (el[g] > 0) return min(k, wk) - max(p, wp);
		if (p <= wp && wk <= k) return ma[g];
		return wp == wk - 1 ? 0 : F(wp, nr, 2 * g) + F(nr, wk, 2 * g + 1);
    }
    int Find(int p1, int k1) { 
		p = p1;
		k = k1;
		return F(0, s / 2, 1);
	}
};
int main() { 
	int w1, w2, w3;
	CoverTree tree(4);
	while(cin >> w1 >> w2 >> w3) {
		if (w1 == 0) {
			tree.Add(w2, w3, 1);
			cout << "Dodanie odcinka [" << w2 << "," << w3 << "]" << endl;
		} else if (w1 == 1) {
			tree.Add(w2, w3, -1);
			cout << "Usuniecie odcinka [" << w2 << "," << w3 << "]" << endl;
		} else
			cout << "Pokrycie odcinka [" << w2 << "," << w3 << 
				"] = " << tree.Find(w2, w3) << endl;
	}
	return 0;
}
