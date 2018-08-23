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

//__builtin_ctz  -  podaje numer najm�odszego zapalonego bitu (skr�t od count trailing zeros)
//__builtin_clz  -  podaje ilo�� zer wiod�cych, co po odj�ciu od d�ugo�ci reprezentacji (32 lub 64 bity), daje nam pozycj� najstarszego zapalonego bitu (skr�t od count leading zeros)
//__builtin_popcount  -  podaje ilo�� zapalonych bit�w liczby, moc zbiotu
//REP(0,2^n-1) iteracja po maskach zbiotu n elementowego
const int INF = 1000000001;
const int MaxK=19;
const int MaxN=20000;

int sol[(1<<MaxK)+1][MaxK+2];
struct Kraw {int v, l;};
vector<vector<Kraw> > gr;
int odl[MaxK+3][MaxK+3];
int ogr[MaxK+3];
int n, m, k;

inline int RI()
{
     int x;
     scanf("%d",&x);
     return x;
}
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
  int dist[n];
  bool vis[n];
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

int Rozwiaz() {
  int zak = (1<<(k-1)) - 1;
  REP(x,(1<<(k-1))) FOR(y,0,k) sol[x][y] = INF;
  FOR(x,1,k-1) if (!ogr[x])
    sol[1<<(x-1)][x] = odl[0][x];
  FOR(x,1,zak) {//przetwarzanie aktualego zbioru z maska x
    FOR(y,1,k-1) if (!(x & (1<<(y-1))) && (ogr[y] | x) == x)//jescli elemenu nie ma w zbiorze i nie jest ograncizony przez elenty z poza zbioru
      FOR(z,1,k-1) if (x & (1<<(z-1)))// jesli elemen jest w zbiorze
        sol[x | (1<<(y-1))][y] = min(sol[x | (1<<(y-1))][y], odl[z][y] + sol[x][z]);//stosule odkowiednia formule dla zbiotu powiekrzonego o x
  }
  int res = INF;
  FOR(x,1,k-1) res = min(res, sol[zak][x]+odl[x][k]);
  return res;
}

int main() {
  WczytajDane();
  LiczOdl();
  printf("%d\n", Rozwiaz());
  return 0;
}
