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
#include <list>
typedef pair<int,int> PII;
typedef vector<PII> VPII;
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
// Typ wierzcholka (Ve) dziedziczy po typie zawierajacym dodatkowe informacje z
// nim zwiazane (V) oraz po wektorze krawedzi. To drugie dziedziczenie moze 
// wydawac sie na pierwszy rzut oka stosunkowo dziwne, lecz jest ono przydatne - 
// umozliwia latwe iterowanie po wszystkich krawedziach wychodzacych z
// wierzcholka v: FOREACH(it, g[v])
	struct Ve : V,vector<Ed> {};
// Wektor wierzcholkow w grafie
	vector<Ve> g;
// Konstruktor grafu - przyjmuje jako parametr liczbe wierzcholkow
	Graph(int n=0) : g(n) {}
// Funkcja dodajaca do grafu nowa krawedz nieskierowana, laczaca wierzcholki
// b i e oraz zawierajaca dodatkowe informacje okreslone przez zmienna d.
// Krawedz nieskierowana jest reprezentowana przez dwie krawedzie skierowane -
// jedna prowadzaca z wierzcholka b do wierzcholka e oraz druga prowadzaca
// z wierzcholka e do wierzcholka b. Struktura E w grafach nieskierowanych musi 
// dodatkowo zawierac element int rev. Dla danej krawedzi skierowanej $(b,e)$ 
// pole to przechowuje pozycje krawedzi $(e,b)$ na liscie incydencji wierzcholka
// $e$. Dzieki temu dla dowolnej krawedzi w grafie mozna w czasie stalym znalezc
// krawedz o przeciwnym zwrocie
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
// Zmienna id uzywana jest do numerowania dwuspojnych skladowych, natomiast l do
// pamietania aktualnego czasu odwiedzenia wierzcholkow metoda DFS
  int id,l;
typedef typename vector<Ed>::iterator EIT;
  vector<EIT> qu;
// Makro ustawia odpowiednie wartosci zmiennych dcc i bri dla krawedzi
// nieskierowanej wskazywanej przez iterator e
#define DccMark(bri) e->dcc = g[e->v][e->rev].dcc = id, \
  e->bridge = g[e->v][e->rev].bridge = bri
  void Dcc(){
// Odpowiednie inicjowanie zmiennych
    id=l=0; qu.clear();
    FOREACH(it,g) it->d=-1; 
// Przetworz wszystkie jeszcze nieodwiedzone wierzcholki w grafie
    REP(i,SIZE(g)) if (g[i].d==-1) DccSearch(i,-1);
  }
  void DccSearch(int v,int u){
      EIT e;
// Ustawienie na odpowiednie wartosci pol d i low rekordu wierzcholka v
      g[v].d=g[v].low=l++;
// Dla wszystkich krawedzi wychodzacych z wierzcholka v
      FOREACH(it,g[v]){
        int w=it->v;
// Jesli wierzcholek docelowy nie zostal jeszcze odwiedzony...
        if (g[w].d==-1){
// Wstaw iterator wskazujacy na aktualnie przetwarzana krawedz na stos
          qu.PB(it);
// Odwiedz wierzcholek, do ktorego prowadzi krawedz
          DccSearch(w,v);
          if (g[w].low>=g[v].d){
// Znaleziono dwuspojna skladowa - dla kazdej krawedzi z tej skladowej ustaw
// odpowiednie wartosci zmiennych bri oraz dcc
			  int cnt=0;
            do{
              e=qu.back();
              DccMark(0);
              qu.pop_back(); cnt++;
            } while (e!=it);
// Znaleziony zostal most
            if (cnt==1) DccMark(1);
            id++;
          } else g[v].low = min(g[v].low, g[w].low);
        } else if (g[w].d<g[v].d && w!=u) qu.PB(it), g[v].low = min(g[v].low, g[w].d);
      }
  }
  int s;
  VPII *X;
// Funkcja dla kazdego mostu w grafie wstawia do wektora res pare numerow
// wierzcholkow polaczonych tym mostem
  void Bridges(VPII &res){
// Odpowiednie inicjowanie poszczegolnych zmiennych
    res.clear();
    X=&res;
    s=0;
    FOREACH(it,g) it->d=-1;
// Przetworzenie wszystkich jeszcze nieodwiedzonych wierzcholkow w grafie
    REP(i,SIZE(g)) if (g[i].d==-1) BriSearch(i,-1);
  }
// Funkcja realizuje przeszukiwanie grafu metoda DFS - odwiedza wierzcholek v,
// gdzie u jest ojcem v w drzewie DFS
  void BriSearch(int v,int u){
      g[v].d=g[v].low=s++;
// Dla kazdej krawedzi wychodzacej z wierzcholka v...
      FOREACH(it,g[v]){
        int w=it->v;
// Jesli wierzcholek w nie byl jeszcze odwiedzony, to go odwiedz
        if (g[w].d==-1){
          BriSearch(w,v);
// Jesli znaleziono w grafie most, to dodaj go do wyniku
          if (g[w].low>g[v].d){
            X->PB(MP(min(v, w), max(v, w) ));  
          } else g[v].low = min(g[v].low, g[w].low);
        } else if (w!=u) g[v].low = min(g[v].low, g[w].d);
      }
  }
// Zmienna wykorzystywana do przechowywania czasu odwiedzenia
// wierzcholkow przez algorytm DFS
int t;
// Wskaznik do konstruowanej listy znalezionych mostow
VPII *br;
// Funkcja przeszukuje poddrzewo wierzcholka v metoda DFS
// (p jest wierzcholkiem-ojcem v w drzewie DFS)
int BriArtR(int v, int p) {
	int l=g[v].d=++t;
// Dla kazdej krawedzi wychodzacej z wierzcholka v i nieprowadzacej do 
// wierzcholka-ojca w drzewie DFS...
	FOREACH(it, g[v]) if (it->v != p)
// Aktualizacja wartosci funkcji low dla wierzcholka v
		l = min(l, !g[it->v].d ? BriArtR(it->v, v) : g[it->v].d);
// Zaktualizowanie informacji o znalezionym punkcie artykulacji
	if(g[p].d<=l) g[p].art = 1;
// Jesli zostal znaleziony most, to jest on dodawany do wyniku
	if(g[p].d<l) br->PB(MP(min(v, p), max(v, p)));
	return l;
}
void BriArt(VPII &res) {
// Odpowiednie inicjowanie zmiennych
	res.clear(); br=&res;
	t=0;
	REP(x, SIZE(g)) g[x].art=g[x].d=0;
// Od kazdego jeszcze nieodwiedzonego wierzcholka rozpocznij przeszukiwanie w glab
	REP(x, SIZE(g)) if(!g[x].d) {
		g[x].d=++t;
		int c = 0;
		FOREACH(it, g[x]) if (!g[it->v].d) {c++; BriArtR(it->v, x);}
// Jesli z korzenia drzewa DFS wychodzi wiecej niz jedna krawedz drzewowa,
// to jest on punktem artykulacji
		g[x].art=(c>1);
	}
}
};
// Wzbogacenie struktur wierzcholkow i krawedzi wymagane 
// przez funkcje Bridges
struct VsBridges { 
	int d, low;
};
struct VeBridges {
	int rev;
};
// Wzbogacenie struktury wierzcholkow i krawedzi o elementy wymagane
// przez funkcje Dcc
struct VsDcc {
	int d, low;
};
struct VeDcc {
	int rev, dcc; 
	bool bridge;
};
// Wzbogacenie struktury wierzcholkow i krawedzi o elementy wymagane 
// przez funkcje BriArt
struct VsBriArt {
	int d; 
	bool art;
};
struct VeBriArt {
	int rev;
};
int main() {
	int n, m, b, e;
// Wczytaj liczbe wierzcholkow i krawedzi
	cin >> n >> m;
	Graph<VsBridges, VeBridges> g1(n);
	Graph<VsDcc, VeDcc> g2(n);
	Graph<VsBriArt, VeBriArt> g3(n);
// Dodaj do grafow wszystkie krawedzie
	REP(x, m) {
		cin >> b >> e;
		g1.EdgeU(b, e);
		g2.EdgeU(b, e);
		g3.EdgeU(b, e);
	}
// Zastosuj funkcje Bridges
	VPII res1;
	g1.Bridges(res1);
	FOREACH(it, res1) 
		cout << "E(" << it->ST << "," << it->ND << ")" << endl;
// Zastosuj funkcje Dcc
	g2.Dcc();
	REP(x, SIZE(g2.g)) FOREACH(it, g2.g[x]) if (x < it->v) {
		if (it->bridge)
			cout << "(" << x << "," << it->v << ") - most" << endl;
		cout << "E(" << x << "," << it->v << ") - " << 
			it->dcc << endl;
	}
// Zastosuj funkcje BriArt
	VPII res3;
	g3.BriArt(res3);
	FOREACH(it, res3) 
		cout << "E(" << it->ST << ", " << it->ND << ") - most" << endl;
	REP(x, SIZE(g3.g)) 
		if (g3.g[x].art) cout << x << " - punkt art." << endl;
	return 0;
}
