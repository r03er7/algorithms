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
struct CoverBTree {
	struct Vert {
		Vert *s[2];
		int v,c;
		Vert(){s[v=c=0]=s[1]=0;}
	};
	Vert *root;
	int zp, zk;
	void Rem(Vert* p){ if (p) {Rem(p->s[0]); Rem(p->s[1]); delete p;}}
	~CoverBTree() {Rem(root);}
	CoverBTree(int p,int k) : zp(p), zk(k) {root=new Vert;}
	int pp,kk,cc;
	void Ad(int p, int k, Vert* v) {
		if(kk<=p || pp>=k) return;
		if (p>=pp && k<=kk) v->c+=cc;
		else
		{
			int c=(p+k)/2;
			if (pp<=c) {
				if (!v->s[0]) v->s[0]=new Vert;
				Ad(p,c,v->s[0]);
			}
			if (kk>=c) {
				if (!v->s[1]) v->s[1]=new Vert;
				Ad(c,k,v->s[1]);
			}
		}
		v->v = v->c ? k-p : 
			(v->s[0] ? v->s[0]->v : 0) + (v->s[1] ? v->s[1]->v : 0);
	}
	void Add(int p, int k, int c) {
		pp=p; kk=k; cc=c;
		Ad(zp,zk,root);
	}
	int Fi(int p, int k, Vert* v) {
		if (!v || p>=kk || k<=pp) return 0;
		if (v->c) return min(k,kk)-max(p,pp);
		if (p>=pp && k<=kk) return v->v;
		int c=(p+k)/2;
		return Fi(p,c,v->s[0])+Fi(c,k,v->s[1]);
	}
	int Find(int p, int k) {
		pp=p; kk=k;
		return Fi(zp,zk,root);
	}
};
int main() { 
	int w1, w2, w3;
	CoverBTree tree(0, 1000000000);
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
