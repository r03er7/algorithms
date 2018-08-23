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
     }  int topo;
// Funkcja wykonujaca algorytm DFS z wierzcholka v i aktualizujaca wartosci zmiennych t
     void TopoDfs(int v) {
// Jesli wierzcholek nie byl odwiedzony, to nalezy go odwiedzic
          if (!g[v].t) {
// Zaznacz wierzcholek jako odwiedzony
               g[v].t=1;
// Odwiedz wszystkie wierzcholki, do ktorych prowadzi krawedz z v
               FOREACH(it,g[v]) TopoDfs(it->v);
// Zaktualizuj wartosc t przetwarzanego wierzcholka
               g[v].t=--topo;
          }
     }
// Wlasciwa funkcja implementujaca sortowanie topologiczne
     void TopoSort() {
          FOREACH(it,g) it->t=0;
          topo=SIZE(g);
// Odwiedz wszystkie wierzcholki w grafie
          FORD(x,topo-1,0) TopoDfs(x);
     }
     VI TopoSortV() {
          VI res(SIZE(g));
// Wyznacz porzadek topologiczny
          TopoSort();
// Na podstawie wartosci zmiennych t wierzcholkow wyznacz wektor z wynikiem
          REP(x,SIZE(g)) res[g[x].t] = x;
          return res;
     }
// Po wykonaniu algorytmu BFS pole int t wierzcholka zawiera odleglosc od zrodla
// (-1, gdy wierzcholek jest nieosiagalny ze zrodla), pole int s zawiera numer
// ojca w drzewie BFS (dla wierzcholka bedacego zrodlem wyszukiwania oraz
// wierzcholkow nieosiagalnych jest to -1)
     void Bfs(int s) {
// Dla kazdego wierzcholka w grafie ustawiana jest poczatkowa wartosc zmiennych
// t oraz s na -1. Zrodlo wyszukiwania ma czas rowny 0
          FOREACH(it, g) it->t=it->s=-1;
          g[s].t=0;
// Algorytm BFS jest realizowany przy uzyciu kolejki FIFO, do ktorej wstawiane
// sa kolejne wierzcholki oczekujace na przetworzenie
          int qu[SIZE(g)],b,e;
// Do kolejki wstawione zostaje zrodlo
          qu[b=e=0]=s;
// Dopoki w kolejce sa jakies wierzcholki...
          while(b<=e) {
               s=qu[b++];
// Dla kazdej krawedzi wychodzacej z aktualnie przetwarzanego wierzcholka,
// jesli wierzcholek, do ktorego ona prowadzi, nie byl jeszcze wstawiony do
// kolejki, wstaw go i wyznacz wartosci zmiennych int t i int s
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
// Funkcja szuka sciezki prowadzacej do wierzcholka Ue (ujscia) przy
// uzyciu przeszukiwania w glab
     bool UFDfs(int v) {
// Jesli wierzcholek jest ujsciem, to zostala znaleziona sciezka powiekszajaca
          if (v==Ue) return true;
          g[v].s=1;
// Dla kazdej krawedzi wychodzacej z wierzcholka...
          FOREACH(it,g[v])
// Jesli laczy ona kolejne warstwy, a wierzcholek docelowy nie byl
// jeszcze odwiedzony, to odwiedz go...
          if (g[it->v].t==1+g[v].t && !g[it->v].s && UFDfs(it->v)) {
// W przypadku znalezienia sciezki powiekszajacej, zmien skierowanie krawedzi
               mvFlow(v,*it);
               return true;
          }
          return false;
     }
// Wlasciwa funkcja wyznaczajaca maksymalny jednostkowy przeplyw
// miedzy wierzcholkami v1 i v2
     int UnitFlow(int v1,int v2) {
          int res=0;
          Ue=v2;
          while (1) {
// Wyznacz drzewo przeszukiwania BFS
               Bfs(v1);
// Jesli ujscie nie zostalo odwiedzone, to nie da sie powiekszyc przeplywu
               if (g[v2].t==-1) break;
               FOREACH(it,g) it->s=0;
// Dla kazdej krawedzi wychodzacej z wierzcholka zrodlowego, jesli istnieje
// sciezka powiekszajaca zawierajaca te krawedz, to powieksz przeplyw
               FOREACH(it,g[v1]) if (UFDfs(it->v)) {
                    res++;
                    mvFlow(v1, *it--);
               }
          }
          return res;
     }
// UWAGA: Na skutek dzialania algorytmu graf ulega modyfikacji
     VI Hopcroft() {
// Inicjowanie zmiennych
          int n=SIZE(g);
          VI res(n,-1);
          vector<char> l;
// Jesli graf nie jest dwudzielny, to algorytm zwraca puste skojarzenie
          if (!BiPart(l)) return res;
// Do grafu dodawane sa dwa wierzcholki, jeden z nich jest laczony ze wszystkimi
// wierzcholkami z pierwszego zbioru wyznaczonego przez funkcje BiPart, a drugi
// z wierzcholkami z drugiego zbioru
          g.resize(n+2);
          REP(i,n) if (!l[i]) EdgeD(n,i);
          else EdgeD(i,n+1);
// Wyznaczany jest przeplyw jednostkowy w zmodyfikowanym grafie
          UnitFlow(n,n+1);
// Skojarzenie jest rekonstruowane na podstawie wyniku obliczonego przez algorytm
// wyznaczajacy przeplyw jednostkowy
          REP(i,n) if (l[i] && g[i][0].v!=n+1)
               res[ res[g[i][0].v]=i ]=g[i][0].v;
          return res;
     }
     bool BiPart(vector<char> &v) {
// Inicjowanie zmiennych
          v.resize(SIZE(g),2);
// Wykonaj sortowanie topologiczne grafu. W grafie moga wystepowac cykle,
// ale nie stanowi to problemu
          VI r = TopoSortV();
// Dla kazdego wierzcholka w grafie...
          FOREACH(x, r) {
// Jesli wierzcholek nie byl jeszcze odwiedzony, to jest on przydzielany do
// pierwszego zbioru wierzcholkow
               if(v[*x]==2) v[*x]=0;
// Przetworz kazdego sasiada biezacego wierzcholka - jesli nie byl on jeszcze
// odwiedzony, to przydziel go do innego zbioru niz wierzcholek x, a jesli byl
// odwiedzony i jest w tym samym zbiorze co x, to graf nie jest dwudzielny
               FOREACH(it, g[*x]) if (v[it->v]==2)
                    v[it->v] = 1-v[*x];
               else if (v[it->v] == v[*x])
                    return 0;
          }
          return 1;
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


   //  cout<<g.UnitFlow(16,17);


g.Write();

  //   g.Write2();
     return 0;
}
