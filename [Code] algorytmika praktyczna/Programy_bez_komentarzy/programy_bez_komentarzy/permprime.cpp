#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <bvector.h>

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
bit_vector Sieve(int s) { 
	bit_vector V(s+1,1);
	V[0] = V[1] = 0;
	FOR(x, 2, s) if(V[x] && LL(s) >= LL(x) * LL(x)) 
		for(int y = x * x; y <= s; y += x) V[y] = 0;
	return V;
}
bit_vector primes;
int off[10];

bool Perm(VI& p) {
	int x,k,i=0,s=p.size(), sum = 0;
	VI c(s, 1);
	vector<bool> pr(s, 1);
	c[s-1] = 0;
	while(i < s-1) {
		i=x=0;
		while(c[i] == s-i) {
			pr[i]=!pr[i];
			if(pr[i]) x++;
			c[i++]=1;
		}
		if(i < s-1) {
			k = pr[i] ? c[i]+x : s-i-c[i]+x;
			swap(p[k-1], p[k]);
			sum += off[k-1]*(p[k-1] - p[k]);
			if (abs(sum) < 1111111 && primes[abs(sum)])
				return true;
			c[i]++;
		}
	}
	return false;
}

VI Digit(int v) {
	VI res;
	while(v) {
		res.PB(v%10);
		v/=10;
	}
	return res;
}

int main() {
	int n,a,b;
	primes = Sieve(1111111);
	off[0] = 1;
	FOR(x,1,9) off[x] = 10*off[x-1];
	cin >> n;
	while(n--) {
		cin >> a >> b;
		int res = 0;
		FOR(x,a,b) {
			VI v = Digit(x);
			if (Perm(v)) res++;
		}
		cout << res << endl;
	}
	return 0;
}
