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
struct PosTree {
    int* el, s;
    PosTree(int size) {
	el = new int[1<<((s=size)+1)];
	REP(x,1<<(s+1)) el[x]=0;
    }
    ~PosTree(){delete[] el;}
    void Add(int p,int v){
		for(p=(1<<s)+p;p>0;p=p>>1) el[p]+=v;}
    int Find(int p) {
		int po=1;
		REP(x,s) {
			po<<=1;
			if (el[po] < p) p-=el[po++];
		}
		return po-(1<<s);
	}
};
int main() {
	int w1, w2, w3;
	PosTree tree(4);
	while(cin >> w1 >> w2) {
		if (w1 == 0) {
			cin >> w3;
			tree.Add(w2, w3);
			if (w3 == 1)
				cout << "Do drzewa dodano element " << w2 << endl; else
				cout << "Z drzewa usunieto element " << w2 << endl;
		} else
		cout << w2 << "-statystyka pozycyjna = " << tree.Find(w2) << endl;
	}
	return 0;
}
