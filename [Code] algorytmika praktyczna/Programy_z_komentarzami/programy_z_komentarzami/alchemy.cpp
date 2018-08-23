#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach - ich skrocenie jest bardzo istotne
typedef vector<int> VI;
typedef long long LL;

// W programach bardzo rzadko mozna znalezc w pelni zapisana instrukcje petli. Zamiast niej, wykorzystywane sa trzy nastepujace makra:
// FOR - petla zwiekszajaca zmienna x od b do e wlacznie
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
// FORD - petla zmniejszajaca zmienna x od b do e wlacznie
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
// REP - petla zwiekszajaca zmienna x od 0 do n. Jest ona bardzo czesto wykorzystywana do konstruowania i przegladania struktur danych
#define REP(x, n) for(int x = 0; x < (n); ++x)
// Makro VAR(v,n) deklaruje nowa zmienna o nazwie v oraz typie i wartosci zmiennej n. Jest ono czesto wykorzystywane podczas operowania na iteratorach struktur danych z biblioteki STL, ktorych nazwy typow sa bardzo dlugie
#define VAR(v, n) __typeof(n) v = (n)
// ALL(c) reprezentuje pare iteratorow wskazujacych odpowiednio na pierwszy i za ostatni element w strukturach danych STL. Makro to jest bardzo przydatne chociazby w przypadku korzystania z funkcji sort, ktora jako parametry przyjmuje pare iteratorow reprezentujacych przedzial elementow do posortowania.
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL. Uzywa sie go w programach, zamiast pisac po prostu x.size() z uwagi na fakt, iz wyrazenie x.size() jest typu unsigned int i w przypadku porownywania z typem int, w procesie kompilacji generowane jest ostrzezenie.
#define SIZE(x) ((int)(x).size())
// Bardzo pozyteczne makro, sluzace do iterowania po wszystkich elementach w strukturach danych STL.
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
// Skrot - zamiast pisac push_back podczas wstawiania elementow na koniec struktury danych, takiej jak vector, wystarczy napisac PB
#define PB push_back
// Podobnie - zamiast first bedziemy pisali po prostu ST
#define ST first
// a zamiast second - ND.
#define ND second
#include <set>
// Wartosc INF jest wykorzystywana jako reprezentacja nieskoñczonosci. Ma ona wartosc 1000000001, a nie 2147483647 (najwieksza wartosc typu int) ze wzgledu na dwa fakty - prosty zapis oraz brak przepelnienia wartosci zmiennej w przypadku dodawania dwoch nieskoñczonosci do siebie: ((int) 2147483647 + (int) 2147483647 = -2).
const int INF = 1000000001;
template<class V, class E> struct Graph {
// Typ krawedzi (Ed) dziedziczy po typie zawierajacym dodatkowe informacje zwiazane z krawedzia (E). Zawiera on rowniez pole v, okreslajace numer wierzcholka, do ktorego prowadzi krawedz. Zaimplementowany konstruktor pozwala na skrocenie zapisu wielu funkcji korzystajacych ze struktury grafu.
	struct Ed : E {
		int v; 
		Ed(E p, int w) : E(p), v(w) {}
	};
// Typ wierzcholka (Ve) dziedziczy po typie zawierajacym dodatkowe informacje z nim zwiazane (V) oraz po wektorze krawedzi. To drugie dziedziczenie moze wydawac sie na pierwszy rzut oka stosunkowo dziwne, lecz jest ono przydatne - umozliwia latwe iterowanie po wszystkich krawedziach wychodzacych z wierzcholka v: FOREACH(it, g[v])
	struct Ve : V,vector<Ed> {};
// Wektor wierzcholkow w grafie
	vector<Ve> g;
// Konstruktor grafu - przyjmuje jako parametr liczbe wierzcholkow
	Graph(int n=0) : g(n) {}
// Funkcja dodajaca do grafu nowa krawedz skierowana z wierzcholka b do e, zawierajaca dodatkowe informacje okreslone przez zmienna d.
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
// Operator okreslajacy porzadek liniowy (w kolejnosci rosnacych odleglosci od zrodla) na wierzcholkach grafu
  struct djcmp{
    bool operator()(const Ve* a, const Ve* b) const{
      return (a->t==b->t) ? a<b : a->t < b->t;
    }
  };
// Funkcja realizujaca algorytm Dijkstry. Dla kazdego wierzcholka wyznaczana jest odleglosc od zrodla wyszukiwania s i umieszczana w zmiennej t oraz numer wierzcholka-ojca w drzewie najkrotszych sciezek - umieszczany w zmiennej s. Dla wierzcholkow nieosiagalnych ze zrodla t = INF, s = -1
  void Dijkstra(int s){
// Kolejka priorytetowa sluzaca do wyznaczania najblizszych wierzcholkow
    set<Ve*, djcmp> k;
    FOREACH(it, g) it->t = INF, it->s = -1;
// Na poczatku wstawiany jest do kolejki wierzcholek zrodlo
    g[s].t = 0; g[s].s = -1; k.insert(&g[s]);
// Dopoki sa jeszcze nieprzetworzone wierzcholki...
	while(!k.empty()){
// Wybierz wierzcholek o najmniejszej odleglosci i usuñ go z kolejki
      Ve *y = *(k.begin());
      k.erase(k.begin());
// Dla kazdej krawedzi, wychodzacej z aktualnie przetwarzanego wierzcholka, sprobuj zmniejszyc odleglosc do wierzcholka, do ktorego ta krawedz prowadzi
      FOREACH(it, *y) if (g[it->v].t > y->t+it->l){
        k.erase(&g[it->v]); g[it->v].t=y->t+it->l;
        g[it->v].s=y-&g[0]; k.insert(&g[it->v]);
      }
    }
  }
};
struct Vs {int t,s;};
struct Ve {int l;};

int main() {
	int n,m,b,e;
// Wczytaj liczbe roznych metali
	cin >> n;
	int price[n];
// Wczytaj ceny metali
	REP(x, n) cin >> price[x];
	Graph<Vs,Ve> gr(n), grTr(n);
// Wczytaj liczbe znanych przemian
	cin >> m;
	Ve str;
// Stworz graf opisujacy dozwolone przemiany (grTr jest grafem transponowanym przemian)
	REP(x, m) {
		cin >> b >> e >> str.l;
		gr.EdgeD(--b, --e, str);
		grTr.EdgeD(e, b, str);
	}
// Dla kazdego metalu wyznacz koszt uzyskania go ze zlota
	gr.Dijkstra(0);
// Dla kazdego metalu wyznacz koszt przemiany go w zloto
	grTr.Dijkstra(0);
	int res = INF;
// Wyznacz najbardziej oplacalny koszt
	REP(x, n) res = min(res, price[x]/2+gr.g[x].t+grTr.g[x].t);
// Wypisz wynik
	cout << res << endl;
	return 0;
}
