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
VI HungarianG() {
	vector<char> l;
	VI re(SIZE(g), -1);
// Jesli graf nie jest dwudzielny, to zwroc puste skojarzenie
	if (!BiPart(l)) return re;
	int gr[SIZE(g)], rel[2][SIZE(g)], n = 0, m = 0;
// Przypisz wierzcholkom z oryginalnego grafu odpowiedniki w macierzy sasiedztwa
	REP(x, SIZE(g)) rel[l[x]][gr[x] = (l[x] ? n++ : m++)] = x;
// Skonstruuj macierz sasiedztwa
	int *w[n >?= m];
	REP(i,n) {
		w[i] = new int[n];
		REP(j,n) w[i][j] = -INF;
	}
// Dodaj do macierzy wagi krawedzi z grafu
	REP(x, SIZE(g)) FOREACH(it, g[x]) 
		w[min(gr[x], gr[it->v])][max(gr[x], gr[it->v])] = max(w[min(gr[x], gr[it->v])][max(gr[x], gr[it->v])], it->c);
// Wykonaj algorytm wegierski
	VI res = Hungarian(w, n);
// Zrekonstruuj wynik, uzywajac wyznaczonej macierzy skojarzenia
	REP(x,SIZE(res)) if (w[x][res[x]] != -INF) {
		re[rel[0][x]] = rel[1][res[x]];
		re[rel[1][res[x]]] = rel[0][x];
	}
	REP(i,n) delete []w[i];
	return re;
}
};
VI Hungarian(int **w,int n){
  int lx[n],ly[n],skojx[n],skojy[n];
  int markx[n],marky[n],sl[n],par[n],q[n];
  REP(i,n){ skojx[i]=skojy[i]=-1; ly[i]=0; lx[i]=*max_element(w[i], w[i]+n); }
  REP(k,n){
    int v=-1,qb=0,qe=0;
    REP(i,n){ marky[i]=markx[i]=0; sl[i]=-1; if (skojx[i]==-1) q[qe++]=i;}
    while (v==-1){
      while (qb<qe){
        int i=q[qb++]; markx[i]=1;
        REP(j,n)
          if (!marky[j] && (sl[j]==-1 || sl[j]>lx[i]+ly[j]-w[i][j])){
            if ((sl[j] = lx[ par[j]=i ]+ly[j]-w[i][j]) == 0){
              marky[j]=1;
              if (skojy[j]!=-1) q[qe++]=skojy[j]; else {v=j; goto end;}
            }
          }
      }
      int x=-1; REP(i,n) if (!marky[i] && (x==-1 || sl[i] < x)) x=sl[i];
      REP(i,n){
        if (markx[i]) lx[i]-=x; 
        if (marky[i]) ly[i]+=x; else
          if ((sl[i] -= x) == 0){
            marky[i]=1; if (skojy[i] != -1) q[qe++]=skojy[i]; else v=i;
          }
      }
    }
end:
    while (v!=-1){int y=skojx[par[v]]; skojx[par[v]]=v; skojy[v]=par[v]; v=y;}
  }
  return VI(skojx,skojx+n);
}
// Wzbogacenie wierzcholkow oraz krawedzi wymagane przez algorytm wyznaczania najciezszego maksymalnego skojarzenia
struct Vs {int t,s;};
struct Ve {int c,rev;};

int main(){
	int n, m, s, b, e;
// Konstruowanie grafu zgodnie z zadanym opisem
	cin >> n >> m;
	Graph<Vs, Ve> g(n);
	Ve l;
	REP(x,m) {
		cin >> b >> e >> l.c;
		g.EdgeU(b, e, l);
	}
// Wyznaczenie maksymalnego skojarzenia przy uzyciu metody wegierskiej, oraz wypisanie wyniku
	VI res = g.HungarianG();
	REP(x, SIZE(res)) if (res[x] > x) 
		cout << "Wierzcholek " << x << " skojarzono z " << res[x] << endl;
	return 0;
}
