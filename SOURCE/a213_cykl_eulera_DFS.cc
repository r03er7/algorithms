#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <bitset>
#include <iterator>
#include <set>
#include <cstring>//clr
#include <complex>
#include <list>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) VAR(v,n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define CLR(A,v) memset((A),v,sizeof((A)))
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
//ios_base::sync_with_stdio(0);
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PI;
const int INF = 1000000000;
const LL INFLL = LL(INF) * LL(INF);

template<class T> inline int size(const T&c) {
    return c.size();
}

struct Krawedz {
    int x;
    list<Krawedz>::iterator rev;
};
list<int> cykl_eulera(int n,list<Krawedz>ZA[]) {
    stack<int>STOS;
    list<int>CE;
    int v=1;
    STOS.push(v);

    while(!STOS.empty()) {
        v=STOS.top();
        if(!ZA[v].empty()) {
            list<Krawedz>::iterator it=ZA[v].begin();
            int u=it->x;
            STOS.push(u);
//usun krawedz (v,u)
            ZA[u].erase(it->rev);
            ZA[v].erase(it);
            v=u;
        } else {
            STOS.pop();
            CE.PB(v);
        }
    }
    return CE;
}
int main() {

    return 0;
}
