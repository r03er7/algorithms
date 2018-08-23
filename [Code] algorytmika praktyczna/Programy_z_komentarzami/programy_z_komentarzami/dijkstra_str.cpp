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
#include <set>
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
// Funkcja dodajaca do grafu nowa krawedz nieskierowana, laczaca wierzcholki b i e
// oraz zawierajaca dodatkowe informacje okreslone przez zmienna d. Krawedz
// nieskierowana jest reprezentowana przez dwie krawedzie skierowane - jedna
// prowadzaca z wierzcholka b do wierzcholka e oraz druga prowadzaca z
// wierzcholka e do wierzcholka b. Struktura E w grafach nieskierowanych
// musi dodatkowo zawierac element int rev. Dla danej krawedzi skierowanej
// $(b,e)$ pole to przechowuje pozycje krawedzi $(e,b)$ na liscie incydencji
// wierzcholka $e$. Dzieki temu dla dowolnej krawedzi w grafie mozna w czasie
// stalym znalezc krawedz o przeciwnym zwrocie
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
// Operator okreslajacy porzadek liniowy (w kolejnosci rosnacych odleglosci od zrodla)
// na wierzcholkach grafu
  struct djcmp{
    bool operator()(const Ve* a, const Ve* b) const{
      return (a->t==b->t) ? a<b : a->t < b->t;
    }
  };
// Funkcja realizujaca algorytm Dijkstry. Dla kazdego wierzcholka wyznaczana jest
// odleglosc od zrodla wyszukiwania s i umieszczana w zmiennej t oraz numer
// wierzcholka-ojca w drzewie najkrotszych sciezek - umieszczany w zmiennej s.
//Dla wierzcholkow nieosiagalnych ze zrodla t = INF, s = -1
  void Dijkstra(int s){
// Kolejka priorytetowa sluzaca do wyznaczania najblizszych wierzcholkow
    set<Ve*, djcmp> k;
    FOREACH(it, g) it->t = INF, it->s = -1;
// Na poczatku wstawiany jest do kolejki wierzcholek-zrodlo
    g[s].t = 0; g[s].s = -1; k.insert(&g[s]);
// Dopoki sa jeszcze nieprzetworzone wierzcholki...
	while(!k.empty()){
// Wybierz wierzcholek o najmniejszej odleglosci i usun go z kolejki
      Ve *y = *(k.begin());
      k.erase(k.begin());
// Dla kazdej krawedzi wychodzacej z aktualnie przetwarzanego wierzcholka
// sprobuj zmniejszyc odleglosc do wierzcholka, do ktorego ta krawedz prowadzi
      FOREACH(it, *y) if (g[it->v].t > y->t+it->l){
        k.erase(&g[it->v]); g[it->v].t=y->t+it->l;
        g[it->v].s=y-&g[0]; k.insert(&g[it->v]);
      }
    }
  }
};
// Wzbogacenie wierzcholkow oraz krawedzi wymagane przez algorytm Dijkstry
struct Vs { 
	int t, s;
};
struct Ve {
	int l, rev;
};
int main() {
	int n, m, s, b, e;
	Ve ed;
// Wczytaj liczbe wierzcholkow, krawedzi oraz wierzcholek startowy
	cin >> n >> m >> s;
// Skonstruuj graf o odpowiednim rozmiarze oraz dodaj do niego krawedzie
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e >> ed.l;
		g.EdgeU(b, e, ed);
	}
// Wykonaj algorytm Dijkstry
	g.Dijkstra(s);
// Wypisz dla wszystkich wierzcholkow znaleziona odleglosc od zrodla 
// oraz numer wierzcholka, z ktorego prowadzi ostatnia krawedz 
// wyznaczonej najkrotszej sciezki
	REP(x, SIZE(g.g)) cout << "Wierzcholek " << x << 
		": odleglosc od zrodla = " << g.g[x].t << 
		", ojciec w drzewie najkrotszych sciezek = " << g.g[x].s << endl;
	return 0;
}
