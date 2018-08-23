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

int n;
list<int>*ZA;
void (*fun)(int[]);//funkcja pobierajaca cykle
int v0;
int *X;
bool *DOP;
void hamilt(int k) {
    FOREACH(it,ZA[X[k-1]]) {
        int y=*it;
        if(k==n+1&&y==v0) {
            X[k]=v0;
            fun(X);
        } else if(DOP[y]) {
            X[k]=y;
            DOP[y]=false;
            hamilt(k+1);
            DOP[y]=true;
        }
    }
}
void cykle_hamiltona(int _n,list<int>_ZA[], void(*f)(int[])) {
    n=_n;
    ZA=_ZA;
    fun=f;
    X=new int[n+2];
    DOP=new bool[n+1];
    FOR(v,1,n)DOP[v]=true;
    v0=1;
    X[1]=v0;
    DOP[v0]=false;
    hamilt(2);
    delete[] X;
    delete[] DOP;
}
int main() {

    return 0;
}
