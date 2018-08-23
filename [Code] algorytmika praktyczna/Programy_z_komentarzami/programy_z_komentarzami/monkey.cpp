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
};
// Struktura danych do reprezentacji zbiorow rozlacznych
struct FAU {
    int *p,*w;
// Konstruktor tworzacy reprezentacje n jednoelementowych zbiorow rozlacznych
	FAU(int n) : p(new int[n]), w(new int[n]) {
		REP(x,n) p[x]=w[x]=-1;
    }
// Destruktor zwalniajacy wykorzystywana pamiec
    ~FAU() {delete[] p; delete[] w;}
// Funkcja zwraca numer reprezentanta zbioru, do ktorego nalezy element x
    int Find(int x) {
	return (p[x] < 0) ? x : p[x]=Find(p[x]);
    }
// Funkcja laczy zbiory zawierajace elementy x oraz y
    void Union(int x, int y) {
	if ((x=Find(x))==(y=Find(y))) return;
	if (w[x] > w[y])
		p[y] = x; else p[x] = y;
	if (w[x] == w[y])
		w[y]++;
	}
};
struct monkey {
// numer malpki trzymanej w lewej (0) i prawej (1) lapce 
	int hand[2];
// czy malpka puszcza kiedys lapke
	bool rel[2];
// czas upadku malpki na ziemie
	int time;
};

// Obiekt reprezentuje zdarzenie "malpka 'monkey' puszcza lapke 'hand'"
struct move {
	int monkey, hand;
};

struct Ve {int rev;};
struct Vs {};
// Graf nieskierowany pozwala na wyszukiwanie wszystkich malpek nalezacych do tej samej spojnej skladowej
Graph<Vs,Ve> gr;
vector<monkey> mon;
vector<move> act;

// Funkcja ustawia czas upadku na ziemie wszystkich malpek z tej samej spojnej skladowej
void SetTime(int v, int t) {
	if (mon[v].time == -1) {
		mon[v].time = t;
		FOREACH(it, gr.g[v]) SetTime(it->v, t);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	mon.resize(n);
	act.resize(m);
// Wczytaj informacje o malpkach
	REP(x, n) {
		cin >> mon[x].hand[0] >> mon[x].hand[1];
		--mon[x].hand[0];
		--mon[x].hand[1];
		mon[x].rel[0] = mon[x].rel[1] = false;
		mon[x].time = -1;
	}
// Wczytaj informacje o kolejnych zdarzeniach
	REP(x, m) {
		cin >> act[x].monkey >> act[x].hand;
		--act[x].monkey;
		--act[x].hand;
		mon[act[x].monkey].rel[act[x].hand] = true;
	}
	FAU fau(n);
	gr.g.resize(n);
// Polacz krawedziami te malpki, ktore po wykonaniu wszystkich operacji 'puszczania' caly czas sie trzymaja
	REP(x, n) REP(y, 2) if (!mon[x].rel[y] && mon[x].hand[y] != -2) {
		fau.Union(x, mon[x].hand[y]);
		gr.EdgeU(x, mon[x].hand[y]);
	}
	int e[2]; bool ground[2];
// Dla kolejnych zdarzeñ 'puszczania lapki' przetwarzanych w odwroconej kolejnosci chronologicznej, dokonaj polaczenia rozlacznych grup malpek oraz ewentualnie zaktualizuj czasy spadania
	FORD(x, m-1, 0) {
		e[0] = act[x].monkey;
		e[1] = mon[act[x].monkey].hand[act[x].hand];
		REP(y, 2) ground[y] = fau.Find(e[y]) != fau.Find(0);
		fau.Union(e[0], e[1]);
		REP(y, 2) if (ground[y] && fau.Find(e[y]) == fau.Find(0))
			SetTime(e[y], x);
		gr.EdgeU(e[0], e[1]);
	}
// Wypisz wynik
	REP(x, n) cout << mon[x].time << endl;
	return 0;
}
