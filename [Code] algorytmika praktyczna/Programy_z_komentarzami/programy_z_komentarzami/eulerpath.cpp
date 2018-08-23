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
bool EulerD(VI &r) { 
// Inicjalizacja wymaganych zmiennych
	int v = -1, kr = 1, h;
	r.clear();
	VI l, st(SIZE(g), 0);
// Dla wszystkich wierzcholkow wyliczany jest stopieñ wejsciowy
	FOREACH(it, g) FOREACH(it2, *it) ++st[it2->v];
// Nalezy wyznaczyc wierzcholek v, od ktorego rozpoczete
// zostanie wyszukiwanie sciezki Eulera.
	REP(x, SIZE(g)) {
// Jesli wierzcholek ma wiekszy stopieñ wyjsciowy od wejsciowego, 
// to jest wierzcholkiem startowym
		if ((h = SIZE(g[x])) > st[x]) v = x; else
// Jesli wierzcholek ma jakies wychodzace krawedzie oraz nie znaleziono 
// jeszcze wierzcholka poczatkowego, to uzyj go jako wierzcholek startowy
		if (h && v == -1) v = x;
		kr += st[x] = h;
	}
// Konstrukcja sciezki Eulera jest rozpoczynana w wierzcholku v
	if (v != -1) l.PB(v);
// Dopoki istnieja wierzcholki na stosie, przeszukuj graf metoda DFS
	while(SIZE(l)) if (!st[v = l.back()]) {
		l.pop_back();
		r.PB(v);
	} else l.PB(v = g[v][--st[v]].v);
// Wyznaczona sciezka Eulera zostala skonstruowana w odwrotnym kierunku, 
// wiec trzeba ja odwrocic
	reverse(ALL(r));
// Algorytm zwraca prawde, jesli wykorzystane zostaly wszystkie krawedzie
// w grafie
	return SIZE(r) == kr;
}
};
// Zarowno krawedzie, jak i wierzcholki nie wymagaja dodatkowych wzbogaceñ
struct Ve{};
struct Vs{};
int main() {
	VI res;
	int n, m, b, e;
// Wczytaj liczbe wierzcholkow oraz krawedzi w grafie
	cin >> n >> m;
	Graph<Vs,Ve> g(n);
// Dodaj do grafu odpowiednie krawedzie
	REP(x,m) {
		cin >> b >> e;
		g.EdgeD(b, e);
	}
// Jesli graf zawiera sciezke Eulera - wypisz ja, jesli nie - poinformuj o tym
	if (g.EulerD(res)) {
		FOREACH(it, res) cout << *it << " ";
		cout << endl;
	} else {
		cout << "No Euler Path" << endl;
	}
	return 0;
}
