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
#include <map>
template<typename _T> struct SufTree { 
	struct SufV {
		map<char, SufV*> sons;
		int p, k;
		bool s;
		_T e;
		SufV *par;
		SufV(int p, int k, SufV *par, bool s) : p(p), k(k), par(par), s(s) {}
		~SufV() {
			FOREACH(it, sons) delete it->second;
		}
	};
	struct VlP {
		SufV *p;
		char l;
		VlP(SufV *p, char l) : p(p), l(l) {}
		bool operator<(const VlP &a) const {
			return (a.p > p) || (a.p == p && a.l > l);
		}
	};
	SufV root;
	string  text;
	SufTree(const string& t) : root(0, 0, 0, 0), text(t) {
		map<VlP, SufV*> lnk;
		set<VlP> test;
		int len = t.length();
		SufV *v = root.sons[t[len - 1]] = new SufV(len - 1, len, &root, 1);
		lnk[VlP(&root, t[len - 1])] = v;
		test.insert(VlP(&root, t[len - 1]));
		FORD(i, len - 2, 0) {
			char a = t[i];
			if (!root.sons[a]) {
				SufV* it = v;
				while(it) { 
					test.insert(VlP(it, a));
					it = it->par;
				}
				it = v;
				lnk[VlP(it, a)] = v = root.sons[t[i]] = new SufV(i, len, &root, 1);
			} else {
				char lw;
				SufV *head, *head2, *x, *x1;
				int lw2 = 0, gl = 0;
				for(x = v; x != &root && test.find(VlP(x, a)) == test.end(); 
					x = x->par) lw2 += x->k - x->p;
				for(x1 = x; x1 && !lnk[VlP(x1, a)]; x1 = x1->par) {
					gl += x1->k - x1->p;
					lw = t[x1->p];
				}
				if (x1) gl--;
				SufV* head1 = x1 ? lnk[VlP(x1, a)] : &root;
				if (x == x1) head = head1; else {
					head2 = (!x1) ? root.sons[a] : head1->sons[lw];
					head = head1->sons[t[head2->p]] = 
						new SufV(head2->p, head2->p + 1 + gl, head1, 0);
					head->sons[t[head->k]] = head2;
					head2->p = head->k;
					head2->par = head;
					for(VAR(it, test.lower_bound(VlP(head2, 0))); it->p == head2;) 
						test.insert(VlP(head, (it++)->l));
				}
				for(SufV* it = v; it != x1; it = it->par) test.insert(VlP(it, a));
				lnk[VlP(x, a)] = head;
				SufV *v1 = v;
				v = head->sons[t[len - lw2]] = new SufV(len - lw2, len, head, 1);
				lnk[VlP(v1, a)] = v;
			}
		}
	}
};
int STSuffixC(SufTree<int>::SufV& v) {
	v.e = v.s;
	FOREACH(it, v.sons) v.e += STSuffixC(*(it->second));
	return v.e;
}
int STFindCount(SufTree<int> &st, const char* t) {
	int tp = 0,x;
	VAR(v, &(st.root));
	while(t[tp]) {
		if (!(v = v->sons[t[tp]])) return 0;
		for(x=v->p;x<v->k && t[tp];) if (t[tp++] != st.text[x++]) return 0;
	}
	return v->e;
}
int main() { 
	string text;
	cin >> text;
	cout << "Przeszukiwany tekst: " << text << endl;
	SufTree<int> tree(text.c_str());
	STSuffixC(tree.root);
	while(cin >> text) cout << "Wzorczec: " << text << " wystepuje " << 
		STFindCount(tree, text.c_str()) << " razy" << endl;
	return 0;
}
