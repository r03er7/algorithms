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
template <typename _T> struct BST {
    struct Ve {
		Ve *s[2];
		_T e; 
		Ve(){s[0]=s[1]=0;}};
#define _Less int (*Less)(const _T&, const _T&)
#define _Upd void (*Upd)(_T*, _T*, _T*)
    _Less;
    _Upd;
    Ve* root,*v;
    vector<Ve*> uV;
    void Rem(Ve* p)	{
	if (p) {
	    REP(x,2) Rem(p->s[x]);
	    delete p;
	}
    }
    ~BST(){Rem(root);}
    BST(_Less, _Upd) : Less(Less), Upd(Upd) {root=0;}
	void Update() {
	for(int x=SIZE(uV)-1;x>=0 && (v=uV[x]);x--)
	    Upd(&v->e, v->s[0] ? &(v->s[0]->e) : 0, v->s[1] ? &(v->s[1]->e) : 0);
        uV.clear();
    }
    Ve* Find(const _T& e, bool s) {
	v=root;
	if (s) uV.PB(v);
	for(int c;v && (-1 != (c=Less(v->e,e)));) { 
	    if(s) uV.PB(v);
	    v=v->s[c];
	}
	return v;
    }
    _T* Find(const _T& e) {return (v = Find(e,0)) ? &(v->e) : 0;}
    void Insert(const _T& e) {
	if (root) {
	    Find(e,1); v=uV.back();
	    int cmp=Less(v->e,e);
	    if (cmp!=-1)
		uV.PB(v=v->s[cmp]=new Ve);
        }
	else uV.PB(v=root=new Ve);
        v->e=e;
        Update();
    }
    bool Delete(const _T& e) {
	Ve* c=Find(e,1),*k;
    	if (!c) {uV.resize(0); return 0;}
	if (c!=root) uV.PB(c);
	if (c->s[0] && c->s[1]) {
	    for(k=c->s[1]; k->s[0]; k=k->s[0]) uV.PB(k);
	    uV.PB(k);
	    c->e=k->e;
	    c=k;
	}
	if(SIZE(uV)>1)
	    (k=uV[SIZE(uV)-2])->s[k->s[0] != c] = c->s[0] ? c->s[0] : c->s[1];
	else root=c->s[0] ? c->s[0] : c->s[1];
	Update();
	delete c;
	return 1;
    }
};
struct Element {
	int val, stat;
};
int Cmp(const Element &a, const Element &b) {
	return (a.val == b.val) ? -1 : a.val < b.val;
}
void Update(Element *p, Element *ls, Element *rs){
	p->stat = 1 + (ls ? ls->stat : 0);
}
Element* Stat(BST<Element> &t, int k) {
	VAR(v, t.root);
	while(v && k != v->e.stat) {
		if (v->s[0] && v->s[0]->e.stat >= k) v = v->s[0];
		else {
			if (v->s[0]) k -= v->s[0]->e.stat; 
			k--;
			v = v->s[1];
		}
	}
	return v ? &(v->e) : 0;
}

int main() {
	BST<Element> Tree(Cmp,Update);
	Element e, *p;
	int cmd;
	while(cin >> cmd >> e.val) {
		if (cmd == 0) {
			Tree.Insert(e);
			cout << "Dodawanie do drzewa elementu " << e.val << endl;
		} else if(cmd == 1) {
			cout << "Usuwanie z drzewa elementu " << e.val << endl;
			Tree.Delete(e);
		} else {
			p = Stat(Tree, e.val);	
			if (!p) 
				cout << "W drzewie nie ma wezla bedacego " << e.val << 
					" statystyka pozycyjna" << endl;
			else cout << e.val << " statystyka pozycyjna to: " << p->val << endl;
		}
	}
	return 0;
}
