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
// Typ krawedzi (Ed) dziedziczy po typie zawierajacym dodatkowe informacje
// zwiazane z krawedzia (E). Zawiera on rowniez pole v, okreslajace numer
// wierzcholka, do ktorego prowadzi krawedz. Zaimplementowany konstruktor
// pozwala na skrocenie zapisu wielu funkcji korzystajacych ze struktury grafu
     struct Ed : E {
          int v;
          Ed(E p, int w) : E(p), v(w) {}
     };
// Typ wierzcholka (Ve) dziedziczy po typie zawierajacym dodatkowe informacje
// z nim zwiazane (V) oraz po wektorze krawedzi. To drugie dziedziczenie moze
// wydawac sie na pierwszy rzut oka stosunkowo dziwne, lecz jest ono
// przydatne - umozliwia latwe iterowanie po wszystkich krawedziach wychodzacych
// z wierzcholka v: FOREACH(it, g[v])
     struct Ve : V,vector<Ed> {};
// Wektor wierzcholkow w grafie
     vector<Ve> g;
// Konstruktor grafu - przyjmuje jako parametr liczbe wierzcholkow
     Graph(int n=0) : g(n) {}
// Funkcja dodajaca do grafu nowa krawedz nieskierowana, laczaca wierzcholki
// b i e oraz zawierajaca dodatkowe informacje okreslone przez zmienna d.
// Krawedz nieskierowana jest reprezentowana przez dwie krawedzie
// skierowane - jedna prowadzaca z wierzcholka b do wierzcholka e oraz druga
// prowadzaca z wierzcholka e do wierzcholka b. Struktura E w grafach
// nieskierowanych musi dodatkowo zawierac element int rev. Dla danej krawedzi
// skierowanej $(b,e)$ pole to przechowuje pozycje krawedzi $(e,b)$ na liscie
// incydencji wierzcholka $e$. Dzieki temu dla dowolnej krawedzi w grafie mozna
// w czasie stalym znalezc krawedz o przeciwnym zwrocie
     void EdgeU(int b, int e, E d = E()) {
          Ed eg(d,e);
          eg.rev=SIZE(g[e])+(b==e);
          g[b].PB(eg);
          eg.rev=SIZE(g[eg.v=b])-1;
          g[e].PB(eg);
     }
// Po wykonaniu algorytmu BFS pole int t wierzcholka zawiera odleglosc od zrodla
// (-1, gdy wierzcholek jest nieosiagalny ze zrodla), pole int s zawiera numer
// ojca w drzewie BFS (dla wierzcholka bedacego zrodlem wyszukiwania oraz
// wierzcholkow nieosiagalnych jest to -1)
      void Bfs(int s) {
// Dla kazdego wierzcholka w grafie ustawiana jest poczatkowa wartosc zmiennych
// t oraz s na -1. zrodlo wyszukiwania ma czas rowny 0
	FOREACH(it, g) it->t=it->s=-1; g[s].t=0;
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

       void Write()
    {
        REP(x,SIZE(g))
        {
            cout<<x<<" "<<g[x].value<<"    "<<SIZE(g[x])<<"   ";
            FOREACH(it,g[x])cout<<" "<<it->v;
            cout<<endl;
        }


    }
    void wer(int s)
    {g[s-1].color=0;
set<int> A;
A.clear();

        REP(x,s)
        {
         if(g[x].color)
        FOREACH(it,g[x]) if(!(g[it->v].color)) A.insert(it->v);

        }
        set<int>::iterator it;
        it = A.begin();
	while (it != A.end())
	{//cout<<*it;
		EdgeU(s-1,*it);
		it++;
	}

    }
void wypisz(int n,int m){


cout<<endl;
REP(x,SIZE(g)-1){if(g[x].color)g[x].t=0;
cout<<g[x].t;
if((x%m)==m-1)cout<<endl;
else cout<<" ";


}
}
void EdgeD(int b,int e,E d=E())
    {
        g[b].PB(Ed(d,e));
    }
void CUBE(int n,int m){
char c;//buduje graf kwadratowy
     REP(x,n) {
          REP(y,m) {
              cin >> c;
               g[x*m+y].color=c-97;
          }
     }
     FOR(x,1,n*m)if(x%(m)) {
          EdgeU(x-1,x);//zle
     }//else ++x;

     REP(x,n-1) {
     REP(y,m) {
               EdgeU(m*x+y,m*x+y+m);
          }}
}
};
// Krawedzie grafu nieskierowanego wymagaja dodatkowego pola int rev
struct Ve {
     int rev;
     bool good;
};
// Wzbogacenie wierzcholkow musi zawierac pola wymagane przez algorytm BFS
struct Vs {
     int t, s;
      int value;

};
int main()
{ ios_base::sync_with_stdio(0);
     int n, m, s, b, e,liczba;
// Wczytaj liczbe wierzcholkow, krawedzi oraz numer wierzcholka startowego
   int xx[73];
   char c;
    FILE *plik=fopen("skaner.txt","r");

    fscanf(plik, "%d%c", &n, &c);
   REP(y,73)fscanf(plik, "%d%c", &xx[y], &c);
Graph<Vs,Ve> g(75);
int edges=0;
REP(x,10)edges+=xx[x];
g.g[74].value=edges;
g.g[73].value=edges;
REP(x,73)g.g[x].value=xx[x];


//74 s
REP(x,10)
{REP(y,xx[x])
g.EdgeD(73,x);
}

//1 warstwa 0 9
REP(x,10)
{
    FOR(y,10,32)
{
    REP(z,min(g.g[x].value,xx[y]))g.EdgeD(x,y);
}
}
//2 warsztwa
FOR(x,10,32)
{
    FOR(y,33,48){
     REP(z,min(g.g[x].value,xx[y]))g.EdgeD(x,y);
    }


}
FOR(x,33,48)
{
    FOR(y,49,72){
     REP(z,min(g.g[x].value,xx[y]))g.EdgeD(x,y);
    }
}



FOR(y,49,72){
     REP(z,xx[y])g.EdgeD(y,74);
    }


g.Write();
cout<<SIZE(g.g[74]);
          return 0;
     }
