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
typedef pair<int,int> PII;
#define MP make_pair
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
    void EdgeD(int b, int e, E d = E()) {
        g[b].PB(Ed(d,e));
    }
// Funkcja wyznacza wielkosc oraz koszt maksymalnego, jednostkowego przeplywu o minimalnym koszcie w sieci miedzy wierzcholkami v1 oraz v2. Na skutek jej dzialania graf podlega modyfikacjom.
    PII MinCostFlow(int v1,int v2) {
        int n=SIZE(g);
        PII res=MP(0,0);
        vector<typename vector<Ed>::iterator> vit(SIZE(g));
        while (1) {
// Ustaw aktualne odleglosci dla wszystkich wierzcholkow (poza zrodlem) na INF oraz zaznacz wierzcholek v1 jako zrodlo wyszukiwania
            FOREACH(it, g) it->t=INF;
            g[v1].t=0;
            g[v1].s=-1;
// Wykonaj co najwyzej SIZE(g) faz wyznaczania najkrotszych sciezek metoda Bellmana-Forda
            for(int chg=1,cnt=0; chg && ++cnt<SIZE(g);) {
                chg=0;
                REP(i,SIZE(g)) FOREACH(it,g[i])
                if (g[i].t+it->l<g[it->v].t) {
                    g[it->v].t=g[i].t+it->l;
                    g[it->v].s=i;
                    vit[it->v]=it;
                    chg=1;
                }
            }
// Jesli nie wyznaczono sciezki miedzy v1 a v2, to przerwij
            if (g[v2].t==INF) break;
// Zwieksz wynik
            res.ST++;
            res.ND+=g[v2].t;
// Odwroc skierowanie krawedzi na wyznaczonej sciezce oraz zmieñ znaki wag krawedzi na przeciwne
            int x=v2;
            while (x!=v1) {
                int v=g[x].s;
                swap(*vit[x],g[v].back());
                Ed e=g[v].back();
                e.l*=-1;
                e.v=v;
                g[x].PB(e);
                g[x=v].pop_back();
            }
        }
        return res;
    }
};
// Wzbogacenie dla wierzcholkow oraz krawedzi wymagane przez funkcje
// MinCostFlow
struct Vs {
    int t,s;
};
struct Ve {
    int l;
};
int main() {
    int n, m, s, f, b, e;

    n=12;
    s=0;
    f=11;
    m=28;
    Graph<Vs, Ve> g(n);
    Ve l;
    l.l=0;
    REP(i,5)g.EdgeD(0,1+i,l);
    printf("das");
    REP(i,5)g.EdgeD(6+i,11,l);
    l.l=25;
    g.EdgeD(1,7,l);
    l.l=21;
    g.EdgeD(1,8,l);
    l.l=18;
    g.EdgeD(1,9,l);
    l.l=13;
    g.EdgeD(1,10,l);

    l.l=11;
    g.EdgeD(2,6,l);
    l.l=28;
    g.EdgeD(2,7,l);
    l.l=32;
    g.EdgeD(2,8,l);
    l.l=12;
    g.EdgeD(2,9,l);
    l.l=11;
    g.EdgeD(2,10,l);

    l.l=20;
    g.EdgeD(3,6,l);
    l.l=210;
    g.EdgeD(3,7,l);
    l.l=19;
    g.EdgeD(3,8,l);
    l.l=17;
    g.EdgeD(3,9,l);
    l.l=6;
    g.EdgeD(3,10,l);

    l.l=19;
    g.EdgeD(4,9,l);
    l.l=25;
    g.EdgeD(4,9,l);

    l.l=17;
    g.EdgeD(5,6,l);
    l.l=12;
    g.EdgeD(5,9,l);

// Wyznacz maksymalny, najtañszy przeplyw oraz wypisz wynik
    cout << "Wyznaczanie przeplywu z " << s << " do " << f << endl;
    PII res = g.MinCostFlow(s, f);
    cout << "Wielkosc przeplywu: " << res.ST;
    cout << ", koszt przeplywu: " << res.ND << endl;
    return 0;
}
