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
VI numeruj(int n,vector<list<int> >&ZA) {
    VI LIDO(n+1);
    VI NR(n+1);

    FOR(v,1,n)LIDO[v]=0;
    FOR(u,1,n) {
        FOREACH(it,ZA[u]) {
            int v=*it;
            ++LIDO[v];
        }
    }
    stack<int> STOS;
    FOR(v,1,n)if(LIDO[v]==0)STOS.push(v);
    int num=0;
    while(!STOS.empty()) {
        int u=STOS.top();
        STOS.pop();
        NR[u]=++num;
        FOREACH(it,ZA[u]) {
            int v=*it;
            --LIDO[v];
            if(LIDO[v]==0)STOS.push(v);
        }
    }
    return NR;
}
int main() {

    return 0;
}
