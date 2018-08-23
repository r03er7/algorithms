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
#include <map>
struct mkmp {
    struct leaf {
	map<char, leaf*> son;
	leaf *lnk, *wo;
	int el;
	leaf() : el(-1) {}
    };
	VI len;
    leaf root;
	leaf* mv(leaf* w, char l) {
		while(w!=&root && w->son.find(l) == w->son.end()) w = w->lnk;
		if (w->son.find(l) != w->son.end()) w = w->son[l];
		return w;
	}
    int addWord(const char *s) {
		int l = strlen(s);
		leaf *p = &root;
		for(;*s;++s) {
			VAR(e, p->son.find(*s));
			p = (e == p->son.end()) ? p->son[*s] = new leaf : e->second;
		}
		if (p->el==-1) {
			p->el=SIZE(len);
			len.PB(l);
		}
		return p->el;
    }
    void calcLink() {
	vector<leaf*> l;
	leaf* w;
	root.lnk = root.wo = 0;
	FOREACH(it, root.son) {
	    l.PB(it->ND);
	    it->ND->lnk = &root;
	}
	REP(x, SIZE(l)) {
	    l[x]->wo = (l[x]->lnk->el != -1) ? l[x]->lnk : l[x]->lnk->wo;
	    FOREACH(it, l[x]->son) {
		l.PB(it->ND);
		w = l[x]->lnk;
		w = mv(w, it->ST);
		it->ND->lnk=w;
	    }
	}
    }
    void searchAll(const char* s, void (*fun)(int, int)) {
	leaf *p = &root;
	for(int x=0;s[x];++x) {
		p = mv(p, s[x]);
	    for(VAR(r,p); r; r=r->wo) if (r->el != -1) fun(x-len[r->el]+1, r->el);
	}
    }
    void searchFirst(const char* s, void (*fun)(int, int)) {
	leaf *p = &root, *r, *t;
	for(int x=0;s[x];++x) {
		p=mv(p,s[x]);
	    r = p;
	    while(r) {
		if (r->el != -1) fun(x-len[r->el]+1, r->el);
		r->el = -1;
		t = r;
		r = r->wo;
		t->wo = 0;
	    }
	}
    }
};
void update(mkmp::leaf *l) {
	vector<mkmp::leaf*> q;
	q.PB(l);
	for(int p=0; p<SIZE(q); p++) if (q[p]->el == -1 && !q[p]->wo) {
		FOREACH(it, q[p]->son) q.PB(it->ND);
		if (!q[p]->lnk) q[p]->lnk = q[0];
		for(char i='0';i<='1';i++)
			if (q[p]->son.find(i) == q[p]->son.end())
				q[p]->son[i] = q[p]->lnk->son[i];
	} else q[p]->el = 0;
}

bool isCycle(mkmp::leaf *l) {
	if (!l || l->el == -2) return 1;
	if (l->el != -1) return 0;
	l->el = -2;
	FOREACH(it, l->son)
		if(isCycle(it->ND)) return 1;
	l->el = -3;
	return 0;
}

int main() {
	int n;
	char s[30000];
	mkmp str;
	cin >> n;
	REP(x, n) {
		cin >> s;
		str.addWord(s);
	}
	str.calcLink();
	update(&(str.root));
	cout << (isCycle(&(str.root)) ? "TAK" : "NIE") << endl;
	return 0;
}
