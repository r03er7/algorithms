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
/*zmienne globalne*/
int n;
bool*NOWY;
list<int> *ZA;
list<PI >T;
//DFS znajduje krawedzie drzewa
void wgd(int v) {
    NOWY[v]=false;
    FOREACH(it,ZA[v]) {
        int u=*it;
        if(NOWY[u]) { //(v,u)jest nowa galezia
            T.PB(MP(v,u));
            wgd(u);
        }
    }
}
//funkcja glowna
list<PI > drzewo_rospinajace(int _n,list<int> _ZA[]) {
    n=_n;
    NOWY=new bool[n+1];
    ZA=_ZA;
    FOR(u,1,n)NOWY[u]=true;
    T.clear();
    wgd(1);
    delete[] NOWY;
    return T;
}
int main() {

    return 0;
}
