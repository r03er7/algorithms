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
int main() {
	int n, m, e1, e2;
// Wczytaj liczbe elementow oraz operacji do wykonania
	cin >> n >> m;
	FAU fau(n);
	REP(x, m) {
// Wczytaj numery dwoch elementow oraz zlacz zbiory je zawierajace
		cin >> e1 >> e2;
		fau.Union(e1, e2);
		cout << "Zlaczenie zbiorow zawierajacych elementy " << 
			e1 << " i " << e2 << endl;
		REP(y, n) cout << "Find(" << y << ") = " << fau.Find(y) << "  ";
		cout << endl;
	}
	return 0;
}
