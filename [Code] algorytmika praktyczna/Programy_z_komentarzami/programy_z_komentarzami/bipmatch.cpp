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
  int topo;
// Funkcja wykonujaca algorytm DFS z wierzcholka v i aktualizujaca wartosci zmiennych t
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
// Wyznacz sortowanie topologiczne
    TopoSort();
// Na podstawie wartosci zmiennych t wierzcholkow, wyznacz wektor z wynikiem
    REP(x,SIZE(g)) res[g[x].t] = x;
    return res;
  }
// Funkcja realizujaca wyszukiwanie sciezki naprzemiennej w grafie przy uzyciu przeszukiwania w glab
bool MDfs(int x){
// Jesli wierzcholek nie zostal jeszcze odwiedzony...
	if (!g[x].t) {
		g[x].t=1;
// Dla kazdej krawedzi wychodzacej z wierzcholka, jesli koniec krawedzi nie jest skojarzony lub istnieje mozliwosc wyznaczenia rekurencyjnie sciezki naprzemiennej...
		FOREACH(it,g[x]) if (g[it->v].m==-1 || MDfs(g[it->v].m)){
// Skojarz wierzcholki wzdluz aktualnie przetwarzanej krawedzi
			g[ g[it->v].m=x ].m=it->v; return true;
		}
	}
    return false;
}
// Funkcja wyznacza maksymalne skojarzenie w grafie dwudzielnym. Umieszcza ona w polu m kazdego wierzcholka numer wierzcholka z nim skojarzonego (lub -1 dla wierzcholkow nieskojarzonych).
bool BipMatching(){
	vector<char> l;
// Jesli graf nie jest dwudzielny, zwroc falsz
	if (!BiPart(l)) return 0;
// Inicjalizacja zmiennych
	int n=SIZE(g),p=1; 
	FOREACH(it,g) it->m=-1;
// Dopoki istnieje sciezka naprzemienna...
	while (p) {
		p=0; FOREACH(it,g) it->t=0;
// Wykonaj przeszukiwanie w glab w celu znalezienia sciezki naprzemiennej
		REP(i,n) if (l[i] && g[i].m==-1) p|=MDfs(i);
	}
	return 1;
}
bool BiPart(vector<char> &v) {
// Inicjalizacja zmiennych
	v.resize(SIZE(g),2);
// Wykonaj sortowanie topologiczne grafu. W grafie moga wystepowac cykle, ale nie stanowi to problemu
	VI r = TopoSortV();
// Dla kazdego wierzcholka w grafie
	FOREACH(x, r) {
// Jesli wierzcholek nie byl jeszcze odwiedzony, to przydzielany jest on do pierwszego zbioru wierzcholkow
		if(v[*x]==2) v[*x]=0;
// Przetworz kazdego sasiada aktualnego wierzcholka - jesli nie byl on jeszcze odwiedzony, to przydziel go do innego zbioru niz wierzcholek x, a jesli byl odwiedzony i jest w tym samym zbiorze co x, to graf nie jest dwudzielny
		FOREACH(it, g[*x]) if (v[it->v]==2)
				v[it->v] = 1-v[*x];
			else if (v[it->v] == v[*x])
				return 0;
	}
	return 1;
}
};
struct Ve{int rev;};
// Wzbogacenie wierzcholkow grafu wymagane przez funkcje BipMatching
struct Vs{int m,t;};

int main() {
	int n, m, s, b, e;
// Skonstruuj odpowiedni graf na podstawie danych wejsciowych
	cin >> n >> m;
	Graph<Vs, Ve> g(n);
	REP(x,m) {
		cin >> b >> e;
		g.EdgeU(b, e);
	}
// Wyznacz maksymalne skojarzenie oraz wypisz wynik
	if (g.BipMatching()) REP(x, SIZE(g.g)) if (g.g[x].m > x) 
		cout << "Wierzcholek " << x << " skojarzono z " << g.g[x].m << endl;
	return 0;
}
