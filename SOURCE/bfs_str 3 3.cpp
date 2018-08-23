#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
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
// Funkcja odwraca skierowanie krawedzi e wychodzacej z wierzcholka v
     void mvFlow(int v, Ed &e) {
          int u=e.v;
          g[u].PB(e);
          g[u].back().v=v;
          swap(g[v].back(),e);
          g[v].pop_back();
     }
     int Ue;
// Funkcja szuka sciezki prowadzacej do wierzcholka Ue (ujscia) przy uzyciu przeszukiwania w glab
     bool UFDfs(int v) {
// Jesli wierzcholek jest ujsciem, to zostala znaleziona sciezka poszerzajaca
          if (v==Ue) return true;
          g[v].s=1;
// Dla kazdej krawedzi wychodzacej z wierzcholka...
          FOREACH(it,g[v])
// Jesli laczy ona kolejne warstwy oraz wierzcholek docelowy nie byl jeszcze odwiedzony, to odwiedz go...
          if (g[it->v].t==1+g[v].t && !g[it->v].s && UFDfs(it->v)){//&&g[it->v].value<=g[v].value) {
// W przypadku znalezienia sciezki poszerzajacej, zamieñ skierowanie krawedzi
             if(g[it->v].value) {--g[it->v].value;
               mvFlow(v,*it);
               return true;
             }
          }
          return false;
     }
// Wlasciwa funkcja wyznaczajaca maksymalny przeplyw jednostkowy miedzy wierzcholkami v1 i v2
     int UnitFlow(int v1,int v2) {
          int res=0;
          Ue=v2;
          while (1) {
// Wyznacz drzewo przeszukiwania BFS
               Bfs(v1);
// Jesli ujscie nie zostalo odwiedzone, to nie da sie powiekszyc przeplywu
               if (g[v2].t==-1) break;
               FOREACH(it,g) it->s=0;
// Dla kazdej krawedzi wychodzacej z wierzcholka zrodlowego, jesli istnieje sciezka poszerzajaca zawierajaca te krawedz, to powieksz przeplyw
               FOREACH(it,g[v1]) if (UFDfs(it->v)) {
                    res++;
                    mvFlow(v1, *it--);
               }
          }
          return res;
     }

     void Write() {
          REP(x,SIZE(g)) {
               cout<<x<<" "<<g[x].value<<"    "<<SIZE(g[x])<<"   ";
               FOREACH(it,g[x])cout<<" "<<it->v;
               cout<<endl;
          }


     }
     void Write2() {
          REP(x,SIZE(g)) {
               cout<<x<<" "<<g[x].value<<"    "<<SIZE(g[x])<<"   ";
               FOREACH(it,g[x])if((it->v)<x)cout<<" "<<it->v;
               cout<<endl;
          }



     }
     void wer(int s) {
          g[s-1].color=0;
          set<int> A;
          A.clear();

          REP(x,s) {
               if(g[x].color)
                    FOREACH(it,g[x]) if(!(g[it->v].color)) A.insert(it->v);

          }
          set<int>::iterator it;
          it = A.begin();
          while (it != A.end()) {
               //cout<<*it;
               EdgeU(s-1,*it);
               it++;
          }

     }
     void wypisz(int n,int m) {


          cout<<endl;
          REP(x,SIZE(g)-1) {
               if(g[x].color)g[x].t=0;
               cout<<g[x].t;
               if((x%m)==m-1)cout<<endl;
               else cout<<" ";


          }
     }
     void EdgeD(int b,int e,E d=E()) {
          g[b].PB(Ed(d,e));
     }
     void CUBE(int n,int m) {
          char c;
          REP(x,n) {
               REP(y,m) {
                    cin >> c;
                    g[x*m+y].color=c-97;
               }
          }
          FOR(x,1,n*m)if(x%(m)) {
               EdgeU(x-1,x);//zle
          }

          REP(x,n-1) {
               REP(y,m) {
                    EdgeU(m*x+y,m*x+y+m);
               }
          }
     }
};

struct Ve {
     int rev;
     bool good;
};

struct Vs {
     int t, s;
     int value;

};
int main()
{
   //  ios_base::sync_with_stdio(0);
     int n, m, s, b, e,liczba;

     char c;
     //  FILE *plik=fopen("skaner.txt","r");

     // fscanf(plik, "%d%c", &n, &c);
     // REP(y,73)fscanf(plik, "%d%c", &xx[y], &c);
     int xx[]= {2,1,1,    1,0,3,0,0         ,2,1,1,    1,0,2,0,1};
     Graph<Vs,Ve> g(18);
     int edges=0;
     REP(x,3)edges+=xx[x];

     g.g[16].value=edges;
     g.g[17].value=edges;
     REP(x,16)g.g[x].value=xx[x];

//74 s
     REP(x,3) {
          REP(y,xx[x])
          g.EdgeD(16,x);
     }


     REP(x,3) {
          FOR(y,3,7) {
               REP(z,min(g.g[x].value,xx[y]))g.EdgeD(x,y);
          }
     }

     FOR(x,3,7) {
          FOR(y,8,10) {
               REP(z,min(g.g[x].value,xx[y]))g.EdgeD(x,y);
          }


     }
     FOR(x,8,10) {
          FOR(y,11,15) {
               REP(z,min(g.g[x].value,xx[y]))g.EdgeD(x,y);
          }
     }



     FOR(y,11,15) {
          REP(z,xx[y])g.EdgeD(y,17);
     }


     cout<<g.UnitFlow(16,17);




     g.Write2();
     return 0;
}
