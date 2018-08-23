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
// Funkcja dodajaca do grafu nowa krawedz nieskierowana, laczaca wierzcholki b i e oraz zawierajaca dodatkowe informacje okreslone przez zmienna d. Krawedz nieskierowana jest reprezentowana przez dwie krawedzie skierowane - jedna prowadzaca z wierzcholka b do wierzcholka e, oraz druga z wierzcholka e do b. Struktura E w grafach nieskierowanych musi dodatkowo zawierac element int rev. Dla danej krawedzi skierowanej $(b,e)$, pole to przechowuje pozycje krawedzi $(e,b)$ na liscie incydencji wierzcholka $e$. Dzieki temu, dla dowolnej krawedzi w grafie w czasie stalym mozna znalezc krawedz o przeciwnym zwrocie.
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
// Zmienna out reprezentuje numer wierzcholka-zrodla 
  int out;
#define ITER typename vector<Ed>::iterator
// Wektor itL zawiera dla kazdego wierzcholka wskaznik na aktualnie przetwarzana krawedz
  vector<ITER> itL;
  VI vis;
// Funkcja wykorzystuje czasy odwiedzenia wierzcholkow z tablicy vis do wyznaczania sciezek poszerzajacych
int FlowDfs(int x,int fl) {
	int r=0, f;
// Jesli aktualny wierzcholek jest ujsciem, lub nie mozna powiekszyc przeplywu, to zwroc aktualny przeplyw
    if (x==out || !fl) return fl;
// Przetworz kolejne krawedzie wierzcholka w celu znalezienia sciezki poszerzajacej
    for (ITER &it=itL[x]; it!=g[x].end(); ++it) {
// Jesli krawedz nie jest nasycona i prowadzi miedzy kolejnymi warstwami...
		if (vis[x]+1 == vis[it->v] && it->c - it->f) {
// Wyznacz wartosc przeplywu, ktory mozna przeprowadzic przez przetwarzana krawedz oraz zaktualizuj odpowiednie zmienne
			it->f += f = FlowDfs(it->v, min(fl, it->c - it->f)); 
			g[it->v][it->rev].f -= f;
			r+=f; fl-=f;
// Jesli nie mozna powiekszyc przeplywu to przerwij
			if (!fl) break;
		}
	}
	return r;
}
// Funkcja wyznacza maksymalny przeplyw miedzy wierzcholkami s oraz f
	int MaxFlow(int s,int f){
// Inicjalizacja zmiennych
		int res=0,n=SIZE(g);
		vis.resize(n);
		itL.resize(n);
		out=f;
		REP(x,n) FOREACH(it,g[x]) it->f = 0;
		int q[n],b,e;
		while(1) {
// Ustaw wszystkie wierzcholki jako nieodwiedzone
			REP(x, n) vis[x] = -1, itL[x] = g[x].begin();
// Wykonaj algorytm BFS zaczynajac ze zrodla s i analizujac tylko nienasycone krawedzie
			for(q[vis[s]=b=e=0]=s;b<=e;++b)
				FOREACH(it,g[q[b]]) if (vis[it->v]==-1 && it->c > it->f)
					vis[q[++e] = it->v] = vis[q[b]] + 1;
// Jesli nie istnieje sciezka do ujscia f, to przerwij dzialanie
			if (vis[f]==-1) break;
// Zwieksz aktualny przeplyw
			res+=FlowDfs(s,INF);
		}
		return res;
	}
};
// Wzbogacenie struktury wierzcholkow oraz krawedzi o elementy wymagane przez algorytm Dinica
struct Ve {int rev, c, f;};
struct Vs {int t;};

int main() {
	int n, m, s, f, b, e;
// Wczytaj liczbe wierzcholkow i krawedzi w grafie oraz zrodlo i ujscie wyznaczanego przeplywu
	cin >> n >> m >> s >> f;
// Skonstruuj graf o odpowiedniej wielkosci, a nastepnie dodaj do niego wszystkie krawedzie
	Graph<Vs, Ve> g(n);
	Ve l; /* newpage */
	REP(x,m) {
		cin >> b >> e >> l.c;
		g.EdgeU(b, e, l);
	}
// Wypisz wielkosc przeplywu miedzy zrodlem a ujsciem
	cout << "Wielkosc calkowitego przeplywu: " << g.MaxFlow(s, f) << endl;
	cout << "Wartosci przeplywu dla kolejnych krawedzi:" << endl;
	REP(x, SIZE(g.g)) FOREACH(it, g.g[x]) if (it->f > 0) 
		cout << "f(" << x << ", " << it->v << ") = " << it->f << endl;
	return 0;
}
