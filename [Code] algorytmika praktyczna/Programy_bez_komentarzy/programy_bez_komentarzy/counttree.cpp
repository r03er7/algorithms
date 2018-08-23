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
struct CountTree {
    int* el, s;
    CountTree(int size) {
	el=new int[2*(s=1<<size)];
	REP(x,2*s) el[x]=0;
    }
    ~CountTree(){delete[] el;}
    void Set(int p,int v){
		for(p+=s;p;p>>=1) el[p]+=v;}
    int Find(int p, int k) {
	int m=0;
	p+=s; k+=s;
	while(p<k) {
	    if(p&1) m+=el[p++];
	    if(!(k&1)) m+=el[k--];
	    p>>=1; k>>=1;
	}
	if(p==k) m+=el[p];
	return m;
    }
};
int main() { 
	int w1, w2, w3;
	CountTree tree(4);
	while(cin >> w1 >> w2 >> w3) {
		if (w1 == 0) {
			tree.Set(w2, w3);
			cout << "Zmiana wartosci elementu " << w2 << " o " << w3 << endl;
		} else
		cout << "Suma na przedziale " << w2 << ".." << w3 << 
			" = " << tree.Find(w2, w3) << endl;
	}
	return 0;
}
