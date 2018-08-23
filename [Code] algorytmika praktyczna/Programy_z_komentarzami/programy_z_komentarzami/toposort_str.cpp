#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach - ich skrocenie 
// jest bardzo istotne
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
// i za ostatni element w strukturach danych STL. Makro to jest bardzo przydatne 
// chociazby w przypadku korzystania z funkcji sort, ktora jako
// parametry 
// przyjmuje pare iteratorow reprezentujacych przedzial
// elementow do posortowania
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL.
// Uzywa sie go w programach, zamiast pisac po prostu x.size() ze wzgledu na to,
//
// iz wyrazenie x.size() jest typu unsigned int i w przypadku porownywania z 
// typem int w procesie kompilacji generowane jest ostrzezenie
#define SIZE(x) ((int)(x).size())
// Bardzo pozyteczne makro sluzace do iterowania po wszystkich elementach w
// strukturach danych STL
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
// wydawac sie na pierwszy rzut oka stosunkowo dziwne, lecz jest ono przydatne -
// umozliwia latwe iterowanie po wszystkich krawedziach wychodzacych
// z wierzcholka v: FOREACH(it, g[v])
	struct Ve : V,vector<Ed> {};
// Wektor wierzcholkow w grafie
	vector<Ve> g;
// Konstruktor grafu - przyjmuje jako parametr liczbe wierzcholkow
	Graph(int n=0) : g(n) {}
// Funkcja dodajaca do grafu nowa krawedz skierowana z wierzcholka b do e,
// zawierajaca dodatkowe informacje okreslone przez zmienna d
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
  int topo;
// Funkcja wykonujaca algorytm DFS z wierzcholka v i aktualizujaca
// wartosci zmiennych t
  void TopoDfs(int v){
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
  void TopoSort(){
    FOREACH(it,g) it->t=0; topo=SIZE(g);
// Odwiedz wszystkie wierzcholki w grafie
	FORD(x,topo-1,0) TopoDfs(x);
  }
  VI TopoSortV(){
    VI res(SIZE(g));
// Wyznacz porzadek topologiczny
    TopoSort();
// Na podstawie wartosci zmiennych t wierzcholkow wyznacz wektor z wynikiem
    REP(x,SIZE(g)) res[g[x].t] = x;
    return res;
  }
};
struct Ve {}; 
// Wzbogacenie wierzcholka o pole t, w ktorym umieszczany jest wynik
struct Vs {
	int t;
};
int main() {
	int n, m, b, e;
// Wczytaj liczbe wierzcholkow oraz krawedzi, utworz graf o odpowiedniej wielkosci
	cin >> n >> m;
	Graph<Vs, Ve> g(n);
// Dodaj do grafu wszystkie krawedzie skierowane
	REP(x,m) {
		cin >> b >> e;
		g.EdgeD(b, e);
	}
// Wyznacz porzadek topologiczny oraz wypisz wynik
	VI res = g.TopoSortV();
	cout << "Kolejnosc topologiczna wierzcholkow: ";
	FOREACH(it, res) cout << *it << " ";
	cout << endl;
	REP(x, SIZE(g.g)) cout << "Wierzcholek " << x << " ma pozycje " <<
		g.g[x].t << " w porzadku topologicznym" << endl;
	return 0;
}
