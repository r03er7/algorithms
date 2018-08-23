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
struct FAU {
     int n;
     VI p,w,ancestor;
// Konstruktor tworzacy reprezentacje n jednoelementowych zbiorow rozlacznych
     FAU(int n) : p(n), w(n), n(n), ancestor(n) {
          REP(x,n){ p[x]=w[x]=-1;
          ancestor[x]=x;//na wszelki wypadek
          }
     }
// Destruktor zwalniajacy wykorzystywana pamiec
     ~FAU() {
          // delete[] p;
          //delete[] w;
     }
// Funkcja zwraca numer reprezentanta zbioru, do ktorego nalezy element x
     int Find(int x) {
          return (p[x] < 0) ? x :p[x]=Find(p[x]);
     }
// Funkcja laczy zbiory zawierajace elementy x oraz y
     void Union(int x, int y) {
          if ((x=Find(x))==(y=Find(y))) return;
          if (w[x] > w[y]){
               p[y] = x;
               ancestor[y]=ancestor[x];
          }
          else {p[x] = y;
          ancestor[x]=ancestor[y];
          }
          if (w[x] == w[y])
               w[y]++;
     }
     void MakeSet(int x) {
          ++n;     //http://wazniak.mimuw.edu.pl/index.php?title=Algorytmy_i_struktury_danych/Find-Union
          p.PB(-1);
          w.PB(-1);
     }
};
template<class V, class E> struct Graph {
     struct Ed : E {
          int v;
          Ed(E p, int w) : E(p), v(w) {}
     };
     FAU fau;
     struct Ve : V,vector<Ed> {};
     vector<Ve> g;
     Graph(int n=0) : g(n),fau(n) {
          REP(x,n)g[x].color=g[x].ancestor=-1;
     }
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
     int TarjanOLCA(int u) {
          //fau.MakeSet(u);
          g[u].ancestor=u;
          //FOREACH(it,g[u])if(g[it->v].s==u) {
            FOREACH(it,g[u].c){
               TarjanOLCA(*it);
               fau.Union(u,*it);
               fau.ancestor[fau.Find(u)]= u;//tutaj dla wszytkich ze zbioru powinno chybab byc
          }
          g[u].color= 1;
          FOREACH(it,g[u]) if((abs(g[it->v].t-g[u].t))<2)
               if (g[it->v].color == 1)
                    return fau.ancestor[fau.Find(it->v)];
     }



     void Bfs(int s) {
// Dla kazdego wierzcholka w grafie ustawiana jest poczatkowa wartosc zmiennych
// t oraz s na -1. zrodlo wyszukiwania ma czas rowny 0
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
                    g[s].c.PB(it->v);
               }
          }
     }
     void write(){


     REP(y,fau.n) cout << "Find(" << y << ") = " << fau.Find(y) << "  ";
		cout << endl;
REP(y,SIZE(g));

     }
};

struct Ve {
     int rev;
};
struct Vs {
     int color; //o bily 1 black
     int ancestor;
     int t, s;
     VI c;
};
////




int main()
{
     int n, m, s, b, e;


     cin >> n >> m;
     Graph<Vs, Ve> g(n);
     REP(x,m) {
          cin >> b >> e;
          g.EdgeU(b, e);
     }
     g.Bfs(0);
     cin>>n;
    cout<<g.TarjanOLCA(n);
g.write();


     return 0;
}
