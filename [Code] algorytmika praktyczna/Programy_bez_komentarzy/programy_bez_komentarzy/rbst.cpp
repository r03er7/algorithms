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
template <typename _T> struct RBST {
	struct Ve {
		Ve *s[2]; 
		_T e; 
		int w; 
		Ve(){s[0] = s[1] = 0;}
	};
#define _Less int (*Less)(const _T&, const _T&)
#define _Upd void (*Upd)(_T*, _T*, _T*)
	_Less;
	_Upd;
	Ve *root, *v;
	vector<Ve*> uV;
	void Rem(Ve* p) {
		if (p) {
			REP(x,2) Rem(p->s[x]);
			delete p;
		}
	}
	~RBST() { 
		Rem(root);
	}
	RBST(_Less, _Upd) : Less(Less), Upd(Upd) {
		root = 0;
	}
	void Update(vector<Ve*> &uV) {
		for(int x = SIZE(uV) - 1; x >= 0 && (v = uV[x]); x--) {
			v->w = 1 + (v->s[0] ? v->s[0]->w : 0) + (v->s[1] ? v->s[1]->w : 0);
			Upd(&v->e, v->s[0] ? &(v->s[0]->e) : 0, 
				v->s[1] ? &(v->s[1]->e) : 0);
		}
		uV.clear();
	}
	Ve* Find(const _T& e, bool s) {
		v = root;
		if (s) uV.PB(v);
		for(int c; v && (-1 != (c = Less(v->e, e)));) {
			v = v->s[c];
			if (s) uV.PB(v);
		}
		return v;
	}
	_T* Find(const _T& e) {
		return (v = Find(e,0)) ? &(v->e) : 0;
	}
	_T* StatPos(int nr) {
		Ve* v = root;
		if (!v || v->w < nr) return 0;
		while (v && nr>0) {
			if (v->s[0] && v->s[0]->w >= nr)
				v = v->s[0];
			else {
				if (v->s[0]) nr -= v->s[0]->w;
				if (--nr) v = v->s[1];
			}
		}
		if (!v) return 0;
		return &(v->e);
	}
	Ve* AtRoot(Ve* p, const _T& e) {
		Ve* d = new Ve, *a, *t, *r=0;
		vector<Ve*> Up[2];
		d->e = e;
		int z = Less(p->e, e);
		a = (t = p)->s[z];
		p->s[z] = 0;
		d->s[1 - z] = t;
		d->s[z] = a;
		Up[1 - z].PB((r = d)->s[1 - z]);
		while(a) {
			if (Less(e, a->e) == z) {
				Up[z].PB(r=a);
				a = a->s[1-z];
			} else {
				r->s[r->s[0] != a] = 0;
				t->s[(t == d) ^ z] = a;
				t = r;
				z = 1 - z;
			}
		}
		REP(x, 2) Update(Up[x]);
		uV.PB(d);
		return d;
	}
	void Insert(const _T& e) {
		if (!root) {
			uV.PB(root = new Ve);
			root->e = e;
		} else if (v = Find(e, 1))
			v->e = e;
		else {
			uV.clear();
			v = root;
			int cmp = 0;
			while(v && rand() % (v->w + 1)) {
				uV.PB(v);
				v = v->s[cmp = Less(v->e, e)];
			}
			if (!v) {
				uV.PB(v = uV.back()->s[cmp] = new Ve);
				v->e = e;
			} else
				SIZE(uV) ? uV.back()->s[cmp] = AtRoot(v, e) : root = AtRoot(v, e);
		}
		Update(uV);
	}
	bool Delete(const _T& e) {
		Ve* c = Find(e, 1), *k;
		if (!c) {
			uV.clear();
			return 0;
		}
		if (c->s[0] && c->s[1]) {
			for(k = c->s[1]; k->s[0]; k = k->s[0]) uV.PB(k);
			uV.PB(k);
			c->e = k->e;
			c = k;
		}
		if (SIZE(uV)>=2)
			(k = uV[SIZE(uV) - 2])->s[k->s[0] != c] = c->s[0] ? c->s[0] : c->s[1];
		else 
			root = c->s[0] ? c->s[0] : c->s[1];
		Update(uV);
		delete c;
		return 1;
	}
};
struct Element { 
	int l, r, mr;
};
int Cmp(const Element &a, const Element &b) {
	if (a.l == b.l && a.r == b.r) return -1;
	return (a.l == b.l) ? a.r < b.r : a.l < b.l;
}
void Update(Element *p, Element *ls, Element *rs){
	p->mr = p->r;
	if (ls) p->mr = max(p->mr, ls->mr);
	if (rs) p->mr = max(p->mr, rs->mr);
}

Element* Find(RBST<Element> &t, int k) {
	VAR(v, t.root);
	while(v) {
		if (v->e.l <= k && v->e.r >= k) return &(v->e);
		v = (v->s[0] && v->s[0]->e.mr >= k) ? v->s[0] : v->s[1];
	}
	return 0;
}

int main() {
	RBST<Element> Tree(Cmp, Update);
	Element e, *p;
	int cmd;
	while(cin >> cmd >> e.l) {
		if (cmd == 0) {
			cin >> e.r;
			Tree.Insert(e);
			cout << "Dodawanie do drzewa odcinka (" 
				<< e.l << "," << e.r << ")" << endl;
		} else if(cmd == 1) {
			cin >> e.r;
			cout << "Usuniecie z drzewa odcinka (" 
				<< e.l << "," << e.r << ")" << endl;
			Tree.Delete(e);
		} else {
			p = Find(Tree, e.l);
			if (!p) cout << "W drzewie nie ma odcinka zawierajacego punktu " 
				<< e.l << endl;
			else cout << "Punkt " << e.l << " zawiera odcinek (" 
				<< p->l << "," << p->r << ")" << endl;
		}
	}
	return 0;
}
