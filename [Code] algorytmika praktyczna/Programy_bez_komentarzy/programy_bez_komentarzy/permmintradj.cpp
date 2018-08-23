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
namespace PermAntyLex {
	VI* V;
	void (*fun)(VI&);
	void Perm(int m) {
		if (!m) fun(*V); else
		FOR(i,0,m) {
			Perm(m-1);
			if(i<m) {
				swap((*V)[i],(*V)[m]);
				reverse(&(*V)[0],&(*V)[m]);
			}
		}
	}
	void Gen(VI& v, void (*f)(VI&)) {
		V=&v; fun=f; Perm(SIZE(v)-1);
	}
};
namespace PermMinTr { 
	VI* V;
	void (*fun)(VI&);
	void Perm(int m){
		if(m == 1) fun(*V); else
		REP(i, m) {
			Perm(m - 1);
			if(i < m - 1) swap((*V)[(!(m & 1) && m > 2) ? 
				(i < m - 1) ? i : m - 3 : m - 2], (*V)[m - 1]);
		}
	}
	void Gen(VI& v, void (*f)(VI&)) {
		V = &v; 
		fun = f; 
		Perm(SIZE(v));
	}
};
void PermMinTrAdj(VI& p, void (*fun)(VI&,int)) {
	int x,k,i=0,s=SIZE(p);
	VI c(s, 1);
	vector<bool> pr(s, 1);
	c[s-1] = 0;
	fun(p,-1);
	while(i < s-1) {
		i=x=0;
		while(c[i] == s-i) {
			if(pr[i]=!pr[i]) x++;
			c[i++]=1;
		}
		if(i < s-1) {
			k = pr[i] ? c[i]+x : s-i-c[i]+x;
			swap(p[k-1], p[k]);
			fun(p,k-1);
			c[i]++;
		}
	}
}
void Display(VI& v, int k) {
	if (k != -1) cout << "Zamiana elementow " << k << " i " << k+1 << endl;
	cout << "Permutacja: ";
	FOREACH(it, v) cout << *it << " ";
	cout << endl;
}

int main() {
	VI p;
	FOR(x,1,3) p.PB(x);
	PermMinTrAdj(p, &Display);
	return 0;
}
