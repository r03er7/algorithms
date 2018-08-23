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

#include <list>
int num,d;
int *STOS;
list<int> *ZA;
int *WGN;
list<list<int> > WYNIK;
//znajdowanie fundamentalnego zbioru cykli dla skladowej
//zawierajacej wierzchollek v
void CYKLE(int v) {
    STOS[++d]=v;
    ++num;
    WGN[v]=num;
    FOREACH(it,ZA[v]) {
        int u = *it;
        if(WGN[u]==0) CYKLE(u);
        else if(u!=STOS[d-1]&& WGN[v]>WGN[u]) {
//u,v zamyka cykl d....u
            list<int> cykl;
            int i=d;
            for(;;) {
                cykl.PB(STOS[i]);
                if(STOS[i]==u)break;
                --i;
            }
            WYNIK.PB(cykl);
        }
    }
    --d;
}
list<list<int> > CYKLE_ELEMENTARNE(int n,list<int>_ZA[]) {
    ZA=_ZA;
    WYNIK.clear();
    WGN=new int[n+1];
    FOR(v,1,n) WGN[v]=0;
    num=0;
    STOS=new int[n+1];
    STOS[0]=0;
    d=0;
    FOR(v,1,n)
    if(WGN[v]==0) CYKLE(v);
    delete[] WGN;
    return WYNIK;
}
int main() {

    return 0;
}
