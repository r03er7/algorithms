#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <vector>
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
#define FKR(x,g,q) for(int x=kra[q];x!=-1;x=zb[x])
struct Kraw {int v, l;};
vector<vector<Kraw> > gr;
int odl[MaxK+2][MaxK+2];
int ogr[MaxK+2];
int n, m, k;

void WczytajDane() {
  int pk, kk, g;
  scanf("%d %d %d", &n, &m, &k);
  k++;
  gr.resize(n);
  Kraw kr;
  REP(x,m) {
    scanf("%d %d %d", &pk, &kr.v, &kr.l);
    pk--; kr.v--;
    gr[pk].push_back(kr);
    swap(kr.v, pk);
    gr[pk].push_back(kr);
  }
  REP(x, k+1) ogr[x] = 0;
  scanf("%d", &g);
  REP(x, g) {
    scanf("%d %d", &pk, &kk);
    ogr[kk-1] |= (1<<(pk-2));
  }
}

void LiczOdl() {
  int dist[n+1];
  bool vis[n+1];
  FOR(x,0,k) {
    REP(y,n) dist[y] = INF, vis[y] = 0;
    dist[x==k ? n-1 : x] = 0;
    priority_queue<PII> queue;
    queue.push(MP(0, x==k ? n-1 : x));
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
    FOR(y,0,k) odl[x][y] = dist[y==k ? n-1 : y];
  }
}
void LiczOdl2() {
  int dist[n+1];
  bool vis[n+1];
  FOR(x,0,k) {
    REP(y,n) dist[y] = INF, vis[y] = 0;
    dist[x==k ? n-1 : x] = 0;
    priority_queue<PII> queue;
    queue.push(MP(0, x==k ? n-1 : x));
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
    FOR(y,0,k) odl[x][y] = dist[y==k ? n-1 : y];
  }
}
void LiczOdlDijkstraQueue() {
  int dist[n+1];
  bool vis[n+1];
  FOR(x,0,k+1) {
    REP(y,n+1) dist[y] = INF, vis[y] = 0;
    dist[x==k+1 ? n : x+1] = 0;
    priority_queue<PII> q;
    q.push(MP(0, x==k+1 ? n : x+1));
    while(!q.empty()) {
      PII el = q.top();
      q.pop();
      if (!vis[el.ND]) {
        vis[el.ND] = 1;
        FKR(it, gr, el.ND) if (dist[wie[it]] > dist[el.ND] + bf[it]) {
          dist[wie[it]] = dist[el.ND] + bf[it];
          q.push(MP(-dist[wie[it]], wie[it]));
        }
      }
    }
    FOR(y,0,k+1) odl[x][y] = dist[y==k+1 ? n : y+1];
  }
}
void LiczOdlDijkstraSet() {
  int dist[n+1];
  bool vis[n+1];
  FOR(x,0,k+1) {

    REP(y,n+1) dist[y] = INF, vis[y] = 0;
    dist[x==k+1 ? n : x+1] = 0;

    set<PII> q;
    q.insert(MP(0, x==k+1 ? n : x+1));
    while(!q.empty()) {
      PII el = *(q.begin());
      q.erase(q.begin());
      if (!vis[el.ND]) {
        vis[el.ND] = 1;
        FKR(it, gr, el.ND) if (dist[wie[it]] > dist[el.ND] + bf[it]) {
          q.erase(MP(dist[wie[it]], wie[it]));
          dist[wie[it]] = dist[el.ND] + bf[it];
          q.insert(MP(dist[wie[it]], wie[it]));
        }
      }
    }
    FOR(y,0,k+1) odl[x][y] = dist[y==k+1 ? n : y+1];
  }
}

     vi D(N, 987654321);

      // start vertex
      set<pair<int,int> > Q;
      D[0] = 0;
      Q.insert(pair<(0,0));

      while(!Q.empty()) {

           // again, fetch the closest to start element
           // from “queue” organized via set
           ii top = *Q.begin();
           Q.erase(Q.begin());
           int v = top.second, d = top.first;

           // here we do not need to check whether the distance
           // is perfect, because new vertices will always
           // add up in proper way in this implementation

           tr(G[v], it) {
                int v2 = it->first, cost = it->second;
                if(D[v2] > D[v] + cost) {
                     // this operation can not be done with priority_queue,
                     // because it does not support DECREASE_KEY
                     if(D[v2] != 987654321) {
                           Q.erase(Q.find(ii(D[v2],v2)));
                     }
                     D[v2] = D[v] + cost;
                     Q.insert(ii(D[v2], v2));
                }
           }
      }
int main() {
}return 0;}
