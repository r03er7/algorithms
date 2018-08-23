#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <vector>
#include <set>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()
const int INF = 1000000001;
const int MaxK=20;
const int MaxN=20000;
using namespace std;
typedef vector<int> VI;
typedef long long LL;
struct Kraw {
     int v, l;
} tmp;
vector<vector<Kraw> > gr;
int odl[MaxK+2][MaxK+2];
int ogr[MaxK+2];
int n, m, k;
int dist[MaxN];
void buildG()
{
     scanf("%d %d",&n,&m);
     gr.resize(n);
     REP(i,m) {
          int a,b,c;
          scanf("%d %d %d",&a, &b,&c);
          --a;
          --b;
          tmp.v=b;
          tmp.l=c;
          gr[a].push_back(tmp);
          tmp.v=a;
          gr[b].push_back(tmp);
     }
}
void dijsjstra_priority_queue(int x)
{

     bool vis[n+1];
     REP(y,n) {
          dist[y] = INF;
          vis[y] = 0;
     }
     priority_queue<PII> queue;
     queue.push(MP(0,x));

     while(!queue.empty()) {

          PII el = queue.top();
          queue.pop();
          if (!vis[el.ND]) {
               vis[el.ND] = 1;
               FOREACH(it, gr[el.ND]) if (dist[it->v] > dist[el.ND] + it->l) {
                    dist[it->v] = dist[el.ND] + it->l;
                    queue.push(MP(-dist[it->v], it->v));
               }
          }
     }
}
bool bellmanFord(int s)
{
     bool vis[n+1];
     int dist[n+1];
     REP(y,n) {
          dist[y] = INF;
          vis[y] = 0;
     }

     REP(x,n-1)
     REP(i,n)
     FOREACH(it, gr[i])
     if (dist[it->v] > dist[i] + it->l) {
          dist[it->v] = dist[i] + it->l;
     }

     REP(i,n)
     FOREACH(it, gr[i])
     if (dist[it->v] > dist[i] + it->l) {
          return 0;
     }

     return 1;
}
int main()
{
     buildG();

}

