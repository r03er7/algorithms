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

list<int> *ZA;
list<list<PI > > WYNIK;
int num;
int *L;
int *WGN;
stack<PI > STOS;
//dfs(v) p=parent(v);
//wynik krawêdzie dwuspujnej skladowej
void DWUSP(int v,int p) {
    WGN[v]=++num;
    L[v]=WGN[v];
    FOREACH(it,ZA[v]) {
        int u=*it;
        if(WGN[u]==0) { // u jest nowy (v,u)jest galesia
            STOS.push(MP(v,u));
            DWUSP(u,v);
            L[v]=min(L[v],L[u]);
            if(L[u]>=WGN[v]) {
                //v jest korzeniem lub punktem artykulacji a szytowa partia stosu az do (v,u)wlacznie
                //zawiera skladowa dwuspujna
                list<PI >skl;
                PI e;
                do {
                    e=STOS.top();
                    STOS.pop();
                    skl.PB(e);
                } while (e!=MP(v,u));
                WYNIK.PB(skl);
            }
        } else {//juz odwiedzony
            if(u!=p&&WGN[u]<WGN[v]) {
                //(v,u) jest cieciwa i nie wystepuje na stosie
                STOS.push(MP(v,u));
                L[v]=min(L[v],WGN[u]);
            }
        }
    }
}
list<list<PI > > DWUSPUJNE(int v,list<int>_ZA[]) {
    ZA=_ZA;
    WYNIK.clear();
    WGN=new int[v+1];
    FOR(u,1,v) WGN[u]=0;
    num=0;
    STOS=stack<PI >();
    L=new int[v+1];
    FOR(u,1,v)
    if(WGN[v]==0) DWUSP(u,0);
    delete[] WGN;
    delete[] L;
    return WYNIK;
}
int main() {

    return 0;
}
