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
void Display(VI& v) {
	static int calc = 0;
	if (!(calc++ % 6)) cout << endl;
	FOREACH(it, v) cout << *it << " ";
	cout << "\t";
}

int main() {
	VI p;
	FOR(x,1,4) p.PB(x);
	PermAntyLex::Gen(p, &Display);
	return 0;
}
