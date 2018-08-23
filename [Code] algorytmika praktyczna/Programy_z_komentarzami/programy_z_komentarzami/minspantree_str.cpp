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
typedef pair<int,int> PII;
#define MP make_pair
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
// Funkcja dodajaca do grafu nowa krawedz nieskierowana, laczaca wierzcholki b i e
// oraz zawierajaca dodatkowe informacje okreslone przez zmienna d. Krawedz 
// nieskierowana jest reprezentowana przez dwie krawedzie skierowane - jedna 
// prowadzaca z wierzcholka b do wierzcholka e oraz druga prowadzaca 
// z wierzcholka e do wierzcholka b. Struktura E w grafach nieskierowanych musi 
// dodatkowo zawierac element int rev. Dla danej krawedzi skierowanej $(b,e)$ 
// pole to przechowuje pozycje krawedzi $(e,b)$ na liscie incydencji wierzcholka 
// $e$. Dzieki temu dla dowolnej krawedzi w grafie mozna w czasie stalym znalezc 
// krawedz o przeciwnym zwrocie
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
// W polu bool span krawedzi algorytm wstawia wartosc prawda, gdy krawedz nalezy
// do wyznaczonego minimalnego drzewa rozpinajacego. Funkcja zwraca wage 
// znalezionego drzewa
int MinSpanTree() {
// Tablica d dla kazdego wierzcholka nienalezacego jeszcze do drzewa rozpinajacego
// zawiera dlugosc najkrotszej krawedzi laczacej go z dowolnym wierzcholkiem drzewa
	int r = 0, d[SIZE(g)];
// Tablica sluzaca do odznaczania wierzcholkow dodawanych do drzewa
	bool o[SIZE(g)];
	REP(x, SIZE(g)) { d[x] = INF; o[x] = 0;}
// Kolejka priorytetowa wierzcholkow osiagalnych z budowanego drzewa,
// przechowywana w kolejnosci niemalejacych kosztow krawedzi
	set<PII> s;
	s.insert(MP(d[0]=0,0));
// Dopoki istnieja wierzcholki nienalezace do drzewa
	while(!s.empty()) {
// Wybierz wierzcholek, ktorego dodanie jest najtansze
		int v = (s.begin())->ND; s.erase(s.begin());
		bool t = 0;
// Zaznacz wierzcholek jako dodany do drzewa oraz zwieksz sumaryczna wage drzewa
		o[v] = 1;
		r += d[v];
// Dla wszystkich krawedzi wychodzacych z dodawanego wierzcholka...
		FOREACH(it, g[v]) {
			it->span = 0;
// Jesli jest to krawedz, ktora dodano do drzewa, to zaznacz ten fakt
			if (!t && o[it->v] && it->l == d[v])
				t = it->span = g[it->v][it->rev].span = 1; else
// Proba zaktualizowania odleglosci od drzewa dla wierzcholkow jeszcze niedodanych...
			if (!o[it->v] && d[it->v] > it->l) {
				s.erase(MP(d[it->v], it->v));
				s.insert(MP(d[it->v] = it->l, it->v));
			}
		}
	}
// Zwroc wage skonstruowanego drzewa rozpinajacego
	return r;
}
};
// Wzbogacenie krawedzi wymagane przez funkcje wyznaczajaca minimalne drzewo 
// rozpinajace
struct Ve { 
	int rev, l; 
	bool span;
};
struct Vs {};
int main() {
	int n, m, b, e;
// Wczytaj liczbe wierzcholkow oraz krawedzi w grafie
	cin >> n >> m;
	Ve l;
// Skonstruuj graf o odpowiedniej wielkosci i dodaj do niego krawedzie
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e >> l.l;
		g.EdgeU(b, e, l);
	}
// Wyznacz minimalne drzewo rozpinajace
	cout << "Waga minimalnego drzewa rozpinajacego: " << 
		g.MinSpanTree() << endl << "Krawedzie nalezace do drzewa:";
// Wypisz wszystkie krawedzie nalezace do drzewa rozpinajacego
	REP(x, SIZE(g.g)) FOREACH(it, g.g[x]) if (it->span && it->v < x) 
		cout << " (" << it->v << ", " << x << ")";
	cout << endl;
	return 0;
}
