#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <cstdio>
#include <vector>
#include <queue>
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
#define INF 1000000000 //nieskończoność
#define MAX 10000 //maksymalna liczba wierzchołków
using namespace std;
int n;
vector<int>  kraw[MAX];
vector<int>g[MAX];
bool vis[MAX];
int val[MAX];
bool w[MAX];
vector<int> _post,post;
void dfs_rev(int x){
//g'mamy krawedz xi->xj <=>w g ~xj->~xi
vis[x]=1;
FOREACH(it,g[x^1])
if(vis[*it^1])dfs_rev(*it^1);
_post.PB(x);
}
void dfs_mark(int x){
vis[x]=1;
val[x]=val[x^1]==-1;
FOREACH(it,g[x])
if(!vis[x^1])dfs_mark(*it);
}
bool _2sat(int n){
//n zmienne
REP(i,2*n)vis[i]=0,val[i]=-1;

REP(i,2*n)if(!vis[i])
dfs_rev(i);//postorder w grafie odwruconym//przeszukiwanie w grafie odwruconym,transponowanym

REP(i,2*n)vis[i]=0;

FORD(i,2*n-1,0)//od max postorder
if(!vis[_post[i]]) dfs_mark(_post[i]);

REP(i,2*n)FOREACH(it,g[i])
if(val[i]&val[*it]==0)return 0;
return 1;
}
///////errro
void dfs(int x)
{
     vis[x]=1;
     FOREACH(it,kraw[x])
     if(!vis[*it])dfs(*it);
     _post.PB(x);//z wywolania rekurencyjnego
     //
}
void sat_or(int a,int b)
{
     kraw[a^1].PB(b);
     kraw[b^1].PB(a);
}
void ustaw(int x)
{
     w[x]=1;
     FOREACH(it,kraw[x])if(!w[*it])ustaw(*it);
//sprawdzanie kolizji elentualne
}
int main()
{
     //x2i 2i+1 x zapreczenie
     //xi^xj => ~xi => xj   ^ ~xj => xi
     REP(i,2*n)vis[i]=false,w[i]=0;

     REP(i,2*n)if(!vis[i])dfs(i);

     FOREACH(it,post)if(!w[*it]&&!w[*it^1])ustaw(*it);
     REP(i,n)if(w[2*i]&&w[2*i+1])cout<<"NIE"<<endl;

     return 0;
}
