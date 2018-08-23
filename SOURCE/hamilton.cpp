#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <unistd.h>
#include <cassert>
#include <list>
using namespace std;
#define VAR(a,b) __typeof(b) a=(b)
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
//#define REP(x, n) for(int x = 0; x < (n); ++x)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
//#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
//#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define FOREACH(it,c) for(VAR(it,(c).begin());it!=(c).end();++it)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
const int INF = 1000000000;
const LL INFLL = LL(INF) * LL(INF);
template<class T> inline int size(const T&c)
{
     return c.size();
}
inline bool myisspace(char c)
{
     return c>=0 && c<=' ';
}
/////////////////
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
using namespace std;
typedef vector<int> VI;
typedef long long LL;
#include <ctime>
////
int V,E;
void wypisz(int X[])
{
     for(int i=1; i<=V+1; ++i) {
          if(i>1) cout<< ", ";
          cout<<X[i];
     }
     cout<<"\n";
}
////
int n;
list<int> *ZA;
void (*fun)(int[]);
int v0;
int *X;
bool *DOP;
void HAMILT(int k)
{
     for(list<int>::iterator it=ZA[X[k-1]].begin(); it!=ZA[X[k-1]].end(); ++it) {
          int y=*it;
          if(k==n+1&&y==v0) {
               X[k]=v0;
               fun(X);
          } else if(DOP[y]) {
               X[k]=y;
               DOP[y]=false;
               HAMILT(k+1);
               DOP[y]=true;
          }
     }
}
void CYKLE_HAMILTONA(int _n,list<int> _ZA[],void (*f)(int[]))
{
     n=_n;
     ZA=_ZA;
     fun=f;
     X=new int[n+2];
     DOP=new bool[n+1];
     for(int v=1; v<=n; ++v) DOP[v]=true;
     v0=1;
     X[1]=v0;
     DOP[v0]=false;
     HAMILT(2);
     delete[] X;
     delete[] DOP;


}
int main()
{
     cout<<"V : ";
     cin>>V;
     cout<<"E : ";
     cin>>E;
     list<int> *ZA=new list<int>[V+1];
     for(int i=1; i<=E;++i) {
          int a,b;
          cout<<"edge "<<i<<" : ";
          cin>>a>>b;
          ZA[a].PB(b);
          ZA[b].PB(a);
     }
     cout<<"hamilton\n";
     CYKLE_HAMILTONA(V,ZA,wypisz);



return 0;
}
