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
// Zmienna nr w pierwszej fazie algorytmu uzywana jest do pamietania czasu odwiedzania wierzcholkow, natomiast w drugiej fazie algorytmu do numerowania silnie spojnych skladowych
int nr;
// Funkcja rekurencyjna, przeszukujaca poddrzewo wierzcholka v. Jest ona uzywana do realizacji obu faz przeszukiwania DFS
void SccSDfs(int v){
// Jesli wierzcholek nie byl odwiedzony, to go odwiedz
	if (g[v].t == -1) {
		g[v].t = nr;
// Odwiedz wszystkie wierzcholki, do ktorych prowadzi krawedz z v
		FOREACH(it, g[v]) SccSDfs(it->v);
// Jesli wykonywana jest pierwsza faza algorytmu, to ustaw zmienna t wierzcholka na czas przetworzenia (odejmowanie wartosci 3 gwarantuje przydzielanie numerow poczynajac od 0 wzwyz)
		if (nr < 0) g[v].t = -(--nr)-3;
	}
}
// Wlasciwa funkcja, wykonujaca wyznaczanie silnie spojnych skladowych
void SccS() {
// Zbuduj graf transponowany gt oraz ustaw wartosci zmiennych t wierzcholkow na -1 (nieodwiedzone)
	Graph<V,E> gt(SIZE(g));
	REP(x,SIZE(g)) {
		g[x].t = gt.g[x].t = -1;
		FOREACH(it, g[x]) gt.EdgeD(it->v, x);
	}
	gt.nr = -2; nr = 0;
	VI v(SIZE(g));
// Wykonaj pierwsza faze przeszukiwania w glab na grafie transponowanym oraz wypelnij wektor v numerami wierzcholkow w kolejnosci rosnacych czasow przetworzenia DFS
	REP(x, SIZE(g)) { gt.SccSDfs(x); v[gt.g[x].t] = x;}
// Wykonaj druga faze przeszukiwania w glab na oryginalnym grafie.
	FORD(x, SIZE(g)-1, 0) { SccSDfs(v[x]); nr++; }
}
};
// Wzbogacenie wierzcholkow zawiera pole t, w ktorym funkcja Scc umieszcza wynik swojego dzialania
struct Vs{int t;};
struct Ve{};

int main() {
	int n, m, b, e;
// Wczytaj liczbe miast oraz drog, stworz graf o odpowiedniej wielkosci
	cin >> n >> m;
	Graph<Vs,Ve> gr(n);
// Wczytaj wszystkie krawedzie oraz dodaj je do grafu
	REP(x, m) {
		cin >> b >> e;
		gr.EdgeD(b-1, e-1);
	}
// Wyznacz silnie spojne skladowe dla wszystkich wierzcholkow w grafie
	gr.SccS();
// Tablica inD zawiera informacje na temat tego, czy do odpowiedniej silnie spojnej skladowej wchodzi jakas krawedz, tablica outD odpowiednia informacje na temat krawedzi wychodzacych, natomiast notEmpty zawiera informacje na temat tego, czy silnie spojna skladowa o odpowiednim numerze wystepuje w grafie
	vector<bool> inD(n,false), outD(n,false), notEmpty(n,false);
	int inVal = 0, outVal = 0, sccC = 0;
// Dla kazdego wierzcholka w grafie, przetworz wszystkie krawedzie z niego wychodzace i aktualizuj zawartosc tablic
	REP(x, n) {
		if (!notEmpty[gr.g[x].t]) {
			notEmpty[gr.g[x].t] = true;
			sccC++;
		}
		FOREACH(it, gr.g[x]) if (gr.g[x].t != gr.g[it->v].t)
			outD[gr.g[x].t] = inD[gr.g[it->v].t] = true;
	}
// Zlicz liczbe silnie spojnych skladowych, z ktorych nie wychodza zadne krawedzie / do ktorych nie wchodza zadne krawedzie
	REP(x, n) {
		if (!inD[x] && notEmpty[x]) inVal++;
		if (!outD[x] && notEmpty[x]) outVal++;
	}
// Jesli w grafie jest tylko jedna silnie spojna skladowa, to wynikiem jest 0
	if (sccC == 1) inVal = outVal = 0;
// Wypisz wynik
	cout << max(inVal, outVal) << endl;
	return 0;
}
