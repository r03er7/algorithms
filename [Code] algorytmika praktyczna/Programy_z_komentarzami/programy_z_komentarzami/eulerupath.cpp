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
// Funkcja dodajaca do grafu nowa krawedz nieskierowana, laczaca wierzcholki b i e oraz zawierajaca dodatkowe informacje okreslone przez zmienna d. Krawedz nieskierowana jest reprezentowana przez dwie krawedzie skierowane - jedna prowadzaca z wierzcholka b do wierzcholka e, oraz druga z wierzcholka e do b. Struktura E w grafach nieskierowanych musi dodatkowo zawierac element int rev. Dla danej krawedzi skierowanej $(b,e)$, pole to przechowuje pozycje krawedzi $(e,b)$ na liscie incydencji wierzcholka $e$. Dzieki temu, dla dowolnej krawedzi w grafie w czasie stalym mozna znalezc krawedz o przeciwnym zwrocie.
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
bool EulerU(VI &ce) {
// Inicjalizacja wymaganych zmiennych
	int v=-1;
	ce.clear();
	VI l, st(SIZE(g), 0), of(SIZE(g)+1, 0);
// Nalezy wyznaczyc wierzcholek v, od ktorego rozpoczete zostanie wyszukiwanie sciezki Eulera
	REP(x, SIZE(g)) {
		of[x+1] = of[x] + (st[x] = SIZE(g[x]));
		if ((st[x] & 1) || (v == -1 && st[x])) v = x;
	}
// Wektor sluzacy do odznaczania wykorzystanych krawedzi.
	vector<bool> us(of[SIZE(g)],0);
// Konstrukcja sciezki Eulera jest rozpoczynana w wierzcholku v
	if (v != -1) l.PB(v);
// Dopoki istnieja wierzcholki na stosie, przeszukuj graf metoda DFS
	while(SIZE(l)) {
		v = l.back();
// Dopoki kolejne krawedzie zostaly juz przetworzone, pomiñ je
		while(st[v] && us[of[v]+st[v]-1]) --st[v];
// Jesli nie ma juz wiecej krawedzi, to wyjdz z wierzcholka i dodaj krawedz, po ktorej sie cofasz do wyniku
		if (!st[v]) {
			l.pop_back();
			ce.PB(v);
		} else {
// Przejdz po jeszcze niewykorzystanej krawedzi
			int u=g[v][--st[v]].v;
			us[of[u]+g[v][st[v]].rev]=1;
			l.PB(v=u);
		}
	}
// Algorytm zwraca prawde, jesli wykorzystane zostaly wszystkie krawedzie w grafie
	return 2*(SIZE(ce)-1) == of[SIZE(g)];
}
};
// Wymagane wzbogacenie krawedzi w grafie nieskierowanym
struct Ve{int rev;};
// Wierzcholki nie wymagaja dodatkowych wzbogaceñ
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
		g.EdgeU(b, e);
	}
// Jesli graf zawiera sciezke Eulera - wypisz ja, jesli nie - poinformuj o tym
	if (g.EulerU(res)) {
		FOREACH(it, res) cout << *it << " ";
		cout << endl;
	} else {
		cout << "No Euler Path" << endl;
	}
	return 0;
}
