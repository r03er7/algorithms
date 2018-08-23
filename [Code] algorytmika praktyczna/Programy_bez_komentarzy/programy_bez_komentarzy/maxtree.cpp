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
#include <list>
const int INF = 1000000001;
struct MaxTree {
    int* el, s;
    MaxTree(int size) {
	el = new int[2*(s = 1<<size)];
	REP(x,2*s) el[x]=0;
    }
    ~MaxTree(){delete[] el;}
    void Set(int p,int v) {
	for(p+=s, el[p]=v, p>>=1; p>0; p>>=1)
	    el[p] = max(el[p<<1], el[(p<<1)+1]);
    }
    int Find(int p, int k) {
	int m = -INF;
	p+=s; k+=s;
	while(p<k) {
	    if((p&1)==1) m=max(m,el[p++]);
	    if((k&1)==0) m=max(m,el[k--]);
	    p>>=1; k>>=1;
	}
	if(p==k) m=max(m,el[p]);
	return m;
    }
};
int main() { 
	int w1, w2, w3;
	MaxTree tree(4);
	while(cin >> w1 >> w2 >> w3) {
		if (w1 == 0) {
			tree.Set(w2, w3);
			cout << "Zmiana wartosci elementu " << w2 << " na " << w3 << endl;
		} else
		cout << "Maksimum na przedziale " << w2 << ".." << w3 << 
			" = " << tree.Find(w2, w3) << endl;
	}
	return 0;
}
