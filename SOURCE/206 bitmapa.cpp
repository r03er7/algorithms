#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach
// - ich skrocenie jest bardzo istotne
typedef vector<int> VI;
typedef long long LL;

// W programach bardzo rzadko mozna znalezc w pelni zapisana instrukcje petli.
// Zamiast niej wykorzystywane sa trzy nastepujace makra:
// FOR - petla zwiekszajaca zmienna x od b do e wlacznie
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
// FORD - petla zmniejszajaca zmienna x od b do e wlacznie
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
// REP - petla zwiekszajaca zmienna x od 0 do n. Jest ona bardzo czesto
// wykorzystywana do konstruowania i przegladania struktur danych
#define REP(x, n) for(int x = 0; x < (n); ++x)
// Makro VAR(v,n) deklaruje nowa zmienna o nazwie v oraz typie i wartosci
// zmiennej n. Jest ono czesto wykorzystywane podczas operowania na
// iteratorach struktur danych z biblioteki STL, ktorych nazwy typow sa bardzo dlugie
#define VAR(v, n) __typeof(n) v = (n)
// ALL(c) reprezentuje pare iteratorow wskazujacych odpowiednio na pierwszy
// i za ostatni element w strukturach danych STL. Makro to jest bardzo
// przydatne chociazby w przypadku korzystania z funkcji sort, ktora jako
// parametry przyjmuje pare iteratorow reprezentujacych przedzial
// elementow do posortowania
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL.
// Uzywa sie go w programach, zamiast pisac po prostu x.size() ze wzgledu na to,
// iz wyrazenie x.size() jest typu unsigned int i w przypadku porownywania
// z typem int w procesie kompilacji generowane jest ostrzezenie
#define SIZE(x) ((int)(x).size())
// Bardzo pozyteczne makro sluzace do iterowania po wszystkich elementach
// w strukturach danych STL
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
// Skrot - zamiast pisac push_back podczas wstawiania elementow na koniec
// struktury danych, takiej jak vector, wystarczy napisac PB
#define PB push_back
// Podobnie - zamiast first bedziemy pisali po prostu ST
#define ST first
// a zamiast second - ND
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
     void EdgeD(int b,int e,E d=E()) {
          g[b].PB(Ed(d,e));
     }

     void Bfs(int s) {
          FOREACH(it, g) it->t=it->s=-1;
          g[s].t=0;
          int qu[SIZE(g)],b,e;
          qu[b=e=0]=s;
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

     void Write() {
          REP(x,SIZE(g)) {
               cout<<x<<" "<<g[x].color<<" ";
               FOREACH(it,g[x])cout<<" "<<it->v;
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
     void CUBE(int n,int m) {
          char c;//buduje graf kwadratowy
          REP(x,n) {
               REP(y,m) {
                    g[x*m+y].color=false;
                    cin >> c;
                    if (c=='1') g[x*m+y].color=true;
               }
          }
          FOR(x,1,n*m)if(x%(m)) {
               EdgeU(x-1,x);//zle
          }//else ++x;

          REP(x,n-1) {
               REP(y,m) {
                    EdgeU(m*x+y,m*x+y+m);
               }
          }
     }
};
struct Ve {
     int rev;
};
struct Vs {
     int t, s,T;
     short int color;

};
int main()
{
     ios_base::sync_with_stdio(0);
     int n, m, s, b, e,liczba;
// Wczytaj liczbe wierzcholkow, krawedzi oraz numer wierzcholka startowego
     cin>>liczba;
     while(liczba--) {


          cin >> n >> m;
          Graph<Vs, Ve> g(n*m+1);
// Dodaj do grafu wszystkie krawedzie
          g.CUBE( n, m);
// Wykonaj algorytm BFS
          g.wer(n*m+1);
          g.Bfs(n*m);
          g.wypisz(n,m);
//g.Write();
     }
// Wypisz wynik
     return 0;
}
