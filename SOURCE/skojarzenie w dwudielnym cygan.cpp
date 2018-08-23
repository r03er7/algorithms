#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
using namespace std;
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
const int INF = 1000000001;
const int N=500;
const int N1=300;
const int N2=400;
////
vector<int> g[N1+N2+4];
int skojx[N1];//-1nie skojarzony numer po drugiej stornei
int skojy[N2];
bool vis[N1];

bool dfs(int x)
{
     vis[x]=1;
     FOREACH(it,g[x])
     if(   (skojy[*it]==-1)  ||   (!vis[skojy[*it]])   &&  dfs(skojy[*it]) ) {
          skojx[x]=*it;
          skojy[*it]=x;
          return 1;
     }
     return 0;
}

int  skojarzenie()
{
     REP(x,N1)skojx[x]=-1;
     REP(x,N2)skojy[x]=-1;

     int res=0;
     REP(x,N1) {
          REP(y,N1)vis[y]=0;
          if(dfs(x))++res;
     }
}
int skojarzenie2()
{
     bool zmiana=1;
     int wyn=0;
     REP(x,N1)skojx[x]=-1;
     REP(x,N2)skojy[x]=-1;

     while(zmiana) {
          zmiana=0;
          REP(y,N1)vis[y]=0;

          REP(x,N1)
          if(   (skojx[x]==-1)  &&   (vis[x])   &&  dfs(x )) {
               zmiana=1;
               ++wyn;
          }
     }
     return wyn;
}
int main()
{

     skojarzenie();
     return 0;
}
