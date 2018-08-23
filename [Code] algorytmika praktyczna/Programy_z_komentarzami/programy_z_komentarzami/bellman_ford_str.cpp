#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

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
// Wartosc INF jest wykorzystywana jako reprezentacja nieskonczonosci.
// Ma ona wartosc 1000000001, a nie 2147483647 (najwieksza wartosc typu int)
// ze wzgledu na dwie rzeczy - prosty zapis oraz brak przepelnienia wartosci
// zmiennej w przypadku dodawania dwoch nieskonczonosci do siebie:
// ((int) 2147483647 + (int) 2147483647 = -2).
const int INF = 1000000001;
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
// Funkcja dodajaca do grafu nowa krawedz skierowana z wierzcholka b do e,
// zawierajaca dodatkowe informacje okreslone przez zmienna d
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
bool BellmanFord(int v){
// Inicjowanie zmiennych
	FOREACH(it, g) it->t=INF; g[v].t=0; g[v].s=-1;
    int change,cnt=0;
// Dopoki przebieg petli poprawia wyznaczane odleglosci, ale petla nie zostala
// wykonana wiecej niz SIZE(g) razy...
    do {
      change=0;
// Dla kazdej krawedzi (v,u) zaktualizuj odleglosc do wierzcholka u
      REP(i,SIZE(g)) FOREACH(it,g[i])
        if (g[i].t+it->l<g[it->v].t){
          g[it->v].t=g[i].t+it->l;
          g[it->v].s=i; change=1;
        }
    } while (change && cnt++<SIZE(g));
// Jesli wagi caly czas ulegaly zmianom, oznacza to, ze w grafie istnieje
// cykl o ujemnej wadze
    return change;
  }
};
// Wzbogacenie struktury wierzcholkow oraz krawedzi wymagane przez 
// algorytm Bellmana-Forda
struct Ve {
	int l;
}; 
struct Vs {
	int t, s;
};

int main() {
	int n, m, s, b, e;
	Ve ed;
// Wczytaj liczbe wierzcholkow, krawedzi oraz wierzcholek zrodlowy
	cin >> n >> m >> s;
// Skonstruuj graf o odpowiedniej wielkosci oraz dodaj do niego 
// wszystkie krawedzie
	Graph<Vs, Ve> g(n);
	REP(x, m) {
		cin >> b >> e >> ed.l;
		g.EdgeD(b, e, ed);
	}
// Wykonaj algorytm Bellmana-Forda
	g.BellmanFord(s);
// Wypisz wynik
	REP(x, SIZE(g.g))
		cout << "Wierzcholek " << x << ": odleglosc od zrodla = " << 
		g.g[x].t << ", ojciec w drzewie najkrotszych sciezek = " << 
		g.g[x].s << endl;
	return 0;
}
