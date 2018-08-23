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
// Po wykonaniu algorytmu BFS, pole int t wierzcholka zawiera odleglosc od zrodla (-1 w przypadku, gdy wierzcholek jest nieosiagalny ze zrodla), pole int s zawiera numer ojca w drzewie BFS (dla wierzcholka bedacego zrodlem wyszukiwania oraz wierzcholkow nieosiagalnych jest to -1)
  void Bfs(int s) {
// Dla kazdego wierzcholka w grafie ustawiana jest poczatkowa wartosc zmiennych t oraz s na -1. rodlo wyszukiwania ma czas rowny 0
	FOREACH(it, g) it->t=it->s=-1; g[s].t=0;
// Algorytm BFS jest realizowany przy uzyciu kolejki FIFO, do ktorej wstawiane sa kolejne wierzcholki oczekujace na przetworzenie
	int qu[SIZE(g)],b,e;
// Do kolejki wstawione zostaje zrodlo
    qu[b=e=0]=s;
// Dopoki w kolejce sa jakies wierzcholki...
    while(b<=e) {
      s=qu[b++];
// Dla kazdej krawedzi wychodzacej z aktualnie przetwarzanego wierzcholka, jesli wierzcholek do ktorego ona prowadzi nie byl jeszcze wstawiony do kolejki, wstaw go i wyznacz wartosci zmiennych int t i int s
      FOREACH(it, g[s]) if (g[it->v].t==-1) {
        g[qu[++e]=it->v].t=g[s].t+1;
		g[it->v].s=s;
      }
    }
  }
// Funkcja odwraca skierowanie krawedzi e wychodzacej z wierzcholka v
  void mvFlow(int v, Ed &e){
    int u=e.v;
    g[u].PB(e); g[u].back().v=v;
    swap(g[v].back(),e); g[v].pop_back();
  }
  int Ue;
// Funkcja szuka sciezki prowadzacej do wierzcholka Ue (ujscia) przy uzyciu przeszukiwania w glab
  bool UFDfs(int v){
// Jesli wierzcholek jest ujsciem, to zostala znaleziona sciezka poszerzajaca
    if (v==Ue) return true;
    g[v].s=1;
// Dla kazdej krawedzi wychodzacej z wierzcholka...
    FOREACH(it,g[v])
// Jesli laczy ona kolejne warstwy oraz wierzcholek docelowy nie byl jeszcze odwiedzony, to odwiedz go...
      if (g[it->v].t==1+g[v].t && !g[it->v].s && UFDfs(it->v)){
// W przypadku znalezienia sciezki poszerzajacej, zamieñ skierowanie krawedzi
        mvFlow(v,*it); return true;
    }
    return false;
  }
// Wlasciwa funkcja wyznaczajaca maksymalny przeplyw jednostkowy miedzy wierzcholkami v1 i v2
  int UnitFlow(int v1,int v2){
    int res=0; Ue=v2;
    while (1){
// Wyznacz drzewo przeszukiwania BFS
      Bfs(v1);
// Jesli ujscie nie zostalo odwiedzone, to nie da sie powiekszyc przeplywu
      if (g[v2].t==-1) break;
      FOREACH(it,g) it->s=0;
// Dla kazdej krawedzi wychodzacej z wierzcholka zrodlowego, jesli istnieje sciezka poszerzajaca zawierajaca te krawedz, to powieksz przeplyw
      FOREACH(it,g[v1]) if (UFDfs(it->v)) {res++; mvFlow(v1, *it--);}
    }
    return res;
  }
// UWAGA: Na skutek dzialania algorytmu graf ulega modyfikacji
  VI Hopcroft(){
// Inicjalizacja zmiennych
    int n=SIZE(g); 
	VI res(n,-1);
	vector<char> l;
// Jesli graf nie jest dwudzielny, to algorytm zwraca puste skojarzenie
	if (!BiPart(l)) return res;
// Do grafu dodawane sa dwa wierzcholki, jeden z nich jest laczony ze wszystkimi wierzcholkami z pierwszego zbioru wyznaczonego przez funkcje BiPart, natomiast drugi z wierzcholkami z drugiego zbioru.
	g.resize(n+2);
	REP(i,n) if (!l[i]) EdgeD(n,i); else EdgeD(i,n+1);
// Wyznaczany jest przeplyw jednostkowy w zmodyfikowanym grafie
	UnitFlow(n,n+1);
// Skojarzenie jest rekonstruowane na podstawie wyniku wyliczonego przez algorytm wyznaczajacy przeplyw jednostkowy
	REP(i,n) if (l[i] && g[i][0].v!=n+1)
		res[ res[g[i][0].v]=i ]=g[i][0].v;
    return res;
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
struct Ve {};
// Pola t oraz s sa wykorzystywane przez algorytm wyznaczania maksymalnego skojarzenia, natomiast pole rem sluzy do pamietania, czy pole zostalo usuniete z szachownicy
struct Vs {int t, s; bool rem; Vs() : rem(0){}};

// Makro zamienia wspolrzedne pola szachownicy na numer wierzcholka
#define Vnr(x,y) ((x)*n+y)

int main() {
	int n,m,wx,wy;
// Wczytaj wielkosc szachownicy oraz liczbe usunietych pol
	cin >> n >> m;
// Stworz graf o odpowiedniej wielkosci
	Graph<Vs,Ve> gr(n*n);
// Zaznacz wszystkie usuniete pola
	REP(x, m) {
		cin >> wx >> wy;
		gr.g[Vnr(wx-1,wy-1)].rem = 1;
	}
// Dodaj odpowiednie krawedzie do grafu, reprezentujace dozwolone ruchy skoczkow
	REP(x,n) REP(y,n) if ((x+y)&1 && !gr.g[Vnr(x,y)].rem) {
#define Add(px,py) if (px >= 0 && py >= 0 && px < n && py < n && !gr.g[Vnr(px,py)].rem) gr.EdgeD(Vnr(x,y),Vnr(px,py));
		Add(x-1,y-2);
		Add(x-2,y-1);
		Add(x-1,y+2);
		Add(x-2,y+1);
		Add(x+1,y-2);
		Add(x+2,y-1);
		Add(x+1,y+2);
		Add(x+2,y+1);
	}
// Wyznacz maksymalne skojarzenie
	VI res = gr.Hopcroft();
	int val = 0;
// Wyznacz wielkosc wyznaczonego skojarzenia
	REP(x, SIZE(res)) if (res[x] != -1) val++;
// Wypisz wynik
	cout << n*n - m - val/2 << endl;
	return 0;
}
