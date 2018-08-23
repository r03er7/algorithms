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
#define MP make_pair
void KMP(const char* str,const char* wzo, void (*fun)(int)) { 
#define KMPH(z) while(k > 0 && wzo[k] != z[q]) k = p[k]; if(wzo[k] == z[q]) k++;
	int p[strlen(wzo) + 1], k = 0, q, m;
	p[1] = 0;
	for (q = 1; wzo[q]; q++) {
		KMPH(wzo);
		p[q + 1] = k;
	}
	m = q;
	k = 0;
	for (q = 0; str[q]; q++) {
		KMPH(str);
		if(m == k) {
			fun(q - m + 1); 
			k = p[k];
		}
	}
}
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
const int MAX = 1001;
char text[MAX][MAX];
char text2[MAX][MAX];
char pattern[MAX];
char pattern2[MAX];
int nr, res = 0;

void Found1(int x, int p) {
	text2[x][nr] = (char)(p+2);
}

void Found2(int v) {
	res++;
}

int main() {
	int cx, cy, mx, my, val;
	cin >> cx >> cy >> mx >> my;
	mkmp find1;
	REP(y, cy) {
		REP(x, cx) {
			cin >> val;
			text[y][x] = (char) val;
			text2[x][y] = (char) 1;
		}
		text[y][cx] = 0;
	}
	REP(y, my) {
		REP(x, mx) {
			cin >> val;
			pattern[x] = val;
		}
		pattern[mx] = 0;
		pattern2[y] = (char) (find1.addWord(pattern)+2);
	}
	pattern2[my] = 0;
	find1.calcLink();
	REP(x, cy) {
		nr = x;
		find1.searchAll(text[x], Found1);
	}
	REP(x, cx-mx+1) {
		text2[x][cy]=0;
		KMP(text2[x], pattern2, Found2);
	}
	cout << res;
	return 0;
}
