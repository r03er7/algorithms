#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
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
const int INF = 1000000001;
template<typename V, class E> struct Graph {

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
     void DelEdgeU(int b,int e, E d=E()) {
          //FOREACH(it,g[b])
          REP(x,SIZE(g[b])) {
               if (g[b][x].v==e) {
                    int c=g[b][x].rev;
//                    g[e].erase(&c);
                    //                  g[b].erase(&x);
                    //      --x;
                    g[2][0].v;
                    cout<<g.g[2][0].rev<<endl;
                    cout<<g.g[2][0].v<<endl;
                    cout<<g.g[g.g[2][0].v][g.g[2][0].rev].v<<endl;
                    //g[g.g[2][0].v][g.g[2][0].rev].v;
                    // c=g[b][it].rev;
                    // g[e][g[b][it].rev].erase();
                    // g[b][it].erase();

                    //g[it->v].v=g[b].back());
                    // swap(it,g[b].back());
                    //g[b].erase(it);
               }
          }
     }
     void DelEdgeD(int b,int e,E d=E()) {
          FOREACH(it,g[b]) {
               if ((it->v)==e) {

                    //  g[b][it].erase();
               }
          }
     }
     void Bfs(int s) {

          FOREACH(it, g) it->t=it->s=-1;
          g[s].t=0;

          int qu[SIZE(g)],b,e;

          qu[b=e=0]=s;

          while(b<=e) {
               s=qu[b++];

               FOREACH(it, g[s]) if (g[it->v].t==-1) {
                    g[qu[++e]=it->v].t=g[s].t+1;
                    g[it->v].s=s;
               }
          }
     }
     void Dfs(int e = -1) {
          VI st(SIZE(g));
          int t = -1 , i = 0, b = 0;
          e==-1 ? e=SIZE(g)-1 : b = e;
          REP(x,SIZE(g)) g[x].d = g[x].f = g[x].s = -1;

          FOR(s,b,e) if(g[s].d == -1) {

               g[st[i++] = s].d = ++t;
               g[s].f = SIZE(g[s]);

               while(i) {
                    int s = st[i-1];

                    if (!g[s].f) {
                         g[s].f = ++t;
                         --i;
                    } else {

                         if (g[s = g[s][--g[s].f].v].d == -1) {

                              g[s].s = st[i-1];
                              g[s].f = SIZE(g[s]);

                              g[st[i++] = s].d = ++t;
                         }
                    }
               }
          }
     }

     int t;
     void DfsV(int v) {
          g[v].d=++t;
          FOREACH(it,g[v]) if (g[it->v].s=-1) {
               g[it->v].s=v;
               DfsV(it->v);
          }
          g[v].f=++t;
     }
     void DfsR(int e=-1) {
          t=-1;
          int b=0;
          e==-1?e=SIZE(g)-1:b=e;

          REP(x,SIZE(g))g[x].d=g[x].f=g[x].s=-1;

          FOR(x,b,e) if(g[x].s==-1) DfsV(x);
     }
     void Write() {
          REP(x,SIZE(g)) {
               cout<<x<<" : ";
               FOREACH(it,g[x])cout<<" "<<it->v;
               cout<<endl;
          }


     }

     VI vis;
     Graph<V,E> *sccRes;

     void SccDfs(int v,int nr, bool phase) {
          g[v].t = 1;
//2 fazy
          if(!phase) vis[v] = nr;

          FOREACH(it, g[v]) if (g[it->v].t == -1)
               SccDfs(it->v, nr, phase);

          else if(!phase && nr > vis[it->v])
               sccRes->EdgeD(g[it->v].t, vis[it->v]=nr);
          if(phase) vis.PB(v);
          else g[v].t = nr;
     }

     Graph<V,E> Scc() {
          Graph<V,E> gt(SIZE(g)),res(SIZE(g)),*tab[]= {this, & gt};
          gt.sccRes=&res;
          gt.vis.resize(SIZE(g), -1);
          vis.clear();
          REP(i,SIZE(g)) FOREACH(it,g[i]) gt.EdgeD(it->v,i);
          REP(i,2) {
               FOREACH(it,tab[i]->g) it->t = -1;
               int comp=0,v;
               FORD(j,SIZE(g)-1,0)
               if (tab[i]->g[v=(i?vis[j]:j)].t == -1) tab[i]->SccDfs(v,comp++,1-i);
               if (i) res.g.resize(comp);
          }
          REP(i,SIZE(g)) g[i].t=gt.g[i].t;
          return res;
     }
int nr;
void SccSDfs(int v){
// Jesli wierzcholek nie byl odwiedzony, to go odwiedz
	if (g[v].t == -1) {
		g[v].t = nr;
// Odwiedz wszystkie wierzcholki, do ktorych prowadzi krawedz z v
		FOREACH(it, g[v]) SccSDfs(it->v);
// Jesli wykonywana jest pierwsza faza algorytmu, to ustaw zmienna t wierzcholka na czas przetworzenia (odejmowanie wartosci 3 gwarantuje przydzielanie numerow poczynajac od 0 wzwyz)
		if (nr < 0) g[v].t = -(--nr)-3;
	}
}
void SccS() {
// Zbuduj graf transponowany gt oraz ustaw wartosci zmiennych t wierzcholkow na -1 (nieodwiedzone)
	Graph<V,E> gt(SIZE(g));
	REP(x,SIZE(g)) {
		g[x].t = gt.g[x].t = -1;
		FOREACH(it, g[x]) gt.EdgeD(it->v, x);
	}
	gt.nr = -2; nr = 0;
	VI v(SIZE(g));
// Wykonaj pierwsza faze przeszukiwania w glab na grafie transponowanym oraz wypelnij wektor v numerami wierzcholkow w kolejnosci rosnacych czasow przetworzenia DFS
	REP(x, SIZE(g)) { gt.SccSDfs(x); v[gt.g[x].t] = x;}
// Wykonaj druga faze przeszukiwania w glab na oryginalnym grafie.
	FORD(x, SIZE(g)-1, 0) { SccSDfs(v[x]); nr++; }
}
};

struct Ve {
    // int rev;
};
struct Vs {
     int t;//,s,d,f;
};
/*
void Mark(Graph<Vs, Ve> &g, int v, int t)
{
     g.g[v].t = t;
     FOREACH(it, g.g[v]) if (g.g[v].s != it->v && g.g[it->v].t == INF)
          Mark(g, it->v, t);
}
#define Desc(n,m) (g->g[n].d <= g->g[m].d && g->g[n].f >= g->g[m].f)
int LCA(Graph<Vs, Ve> *g, int b, int e)
{
     int res = 0, p = SIZE(g->g[b].l)-1;

     while(!Desc(b, e)) {

          p = min(p, SIZE(g->g[b].l)-1);
          while(p>0 && Desc(g->g[b].l[p], e)) p--;

          res += (1<<p);
          b = g->g[b].l[p];
     }
     return res;
}


void GenLCA(Graph<Vs, Ve> *g, int v)
{
     if (v != 0 && !SIZE(g->g[v].l)) {
          int c = g->g[v].s;

          GenLCA(g, c);

          g->g[v].l.PB(c);

          while(SIZE(g->g[c].l) >= SIZE(g->g[v].l)) {
               c = g->g[c].l[SIZE(g->g[v].l)-1];
               g->g[v].l.PB(c);
          }
     }
}
//gr.Dfs(0);
//FOR(x,1,n-1) GenLCA(&gr, x);
*/
