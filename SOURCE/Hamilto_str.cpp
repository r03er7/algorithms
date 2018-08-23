// {{{
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

using namespace std;
#define VAR(a,b) __typeof(b) a=(b)
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
//#define REP(x, n) for(int x = 0; x < (n); ++x)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
//#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
//#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define FOREACH(it,c) for(VAR(it,(c).begin());it!=(c).end();++it)
typedef long long LL; typedef unsigned long long ULL;
typedef long double LD;
const int INF = 1000000000; const LL INFLL = LL(INF) * LL(INF);
template<class T> inline int size(const T&c) { return c.size(); }
inline bool myisspace(char c) { return c>=0 && c<=' '; }
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

template<class V, class E> struct Graph {
     struct Ed : E {
          int v;
          Ed(E p, int w) : E(p), v(w) {}
     };
     struct Ve : V,vector<Ed> {};
     vector<Ve> g;
     Graph(int n=0) : g(n) {}
     void EdgeU(int b, int e, E d = E()) {
          Ed eg(d,e);
          eg.rev=SIZE(g[e])+(b==e);
          g[b].PB(eg);
          eg.rev=SIZE(g[eg.v=b])-1;
          g[e].PB(eg);
     }

     void EdgeD(int b,int e,E d=E()) {
          g[b].PB(Ed(d,e));
     }



/////////


int n;
int v0;
int *X;
vector<int[] > haM;
bool *DOP;
void (*fun)(int[]);

void wypisz(int X[])
{
    // for(int i=1; i<=V+1; ++i) {
      REP(i,SIZE(g)+1) {   if(i) cout<< ", ";
          cout<<X[i];
     }
     cout<<"\n";
}


void HAMILT(int k)
{ FOREACH(it,g[X[k-1]]){
          int y=it->v;
          if(k==n&&y==v0) {
               X[k]=v0;
              // fun(X);
              wypisz(X);

          } else if(DOP[y]) {
               X[k]=y;
               DOP[y]=false;
               HAMILT(k+1);
               DOP[y]=true;
          }
     }
}
void CYKLE_HAMILTONA(/*void (*f)(int[])*/)
{
     n=SIZE(g);
//     fun=f;
     X=new int[n+2];
     DOP=new bool[n+1];
     //for(int v=1; v<=n; ++v) DOP[v]=true;
     REP(v,n)DOP[v]=true;
     //v0=1;
     v0=0;
     //X[1]=v0;
     X[0]=v0;
     DOP[v0]=false;
     HAMILT(1);
     delete[] X;
     delete[] DOP;


}


};

struct Ve {
     int rev;
};
struct Vs {
     int d, f, s;
};
int main()
{
     int n, m, s, b, e;
     cin >> n >> m;
     Graph<Vs, Ve> g(n);
     REP(x,m) {
          cin >> b >> e;
          g.EdgeU(b, e);
     }
     g.CYKLE_HAMILTONA();

     return 0;
}
