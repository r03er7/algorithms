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
#include <set>
struct el {
	int x, y;
	LL size;
	el(int x, int y) : x(x), y(y) {
		size = LL(x)*LL(y);
	}
};

// Reprezentuje punkt (x,y,z)
struct obj {
	int x,y,z;
};

// Operator okreslajacy porzadek na obiektach el w kolejnosci niemalejacych wielkosci
struct sizeOrder
{
  bool operator()(const el& a, const el& b) const
  {
	if (a.size != b.size)
		return a.size > b.size;
	return (a.x != b.x) ? a.x < b.x : a.y < b.y;
  }
};

// Operator okreslajacy porzadek na obiektach el w kolejnosci niemalejacych wspolrzednych x
struct xOrder
{
  bool operator()(const el& a, const el& b) const
  {
	return (a.x != b.x) ? a.x < b.x : a.y < b.y;
  }
};

// Operator okreslajacy porzadek na punktach w kolejnosci niemalejacych wspolrzednych z
bool zOrder(const obj& a, const obj& b) {
	if (a.z != b.z)
		return a.z < b.z;
	return (a.x != b.x) ? a.x < b.x : a.y < b.y;
}

// Struktura przechowujaca obiekty el w kolejnosci malejacych wielkosci
set<el, sizeOrder> sizeSet;
// Struktura przechowujaca obiekty el w kolejnosci niemalejacych wspolrzednych x
set<el, xOrder> xSet;

int main() {
	int n;
// Wczytaj liczbe punktow
	cin >> n;
	vector<obj> l(n+1);
// Wczytaj wspolrzedne kolejnych punktow
	REP(x, n) cin >> l[x].x >> l[x].y >> l[x].z;
// Dodaj punkt-straznika 
	l[n].x=l[n].y=l[n].z=1000000;
// Posortuj punkty w kolejnosci niemalejacych wspolrzednych z
	sort(ALL(l), zOrder);
	LL res = 0;
	obj ores;
// Dodaj do struktur sizeSet i xSet punkt (1000000, 1000000) - jest on ogranicznikiem wielkosci prostopadloscianu
	sizeSet.insert(el(1000000, 1000000));
	xSet.insert(el(1000000, 1000000));
// Dla kazdego punktu w kolejnosci niemalejacych wspolrzednych z...
	REP(x, n+1) {
// Wybierz ogranicznik wielkosci prostopadloscianu w wymiarach [x,y] o najwiekszej wielkosci
		VAR(it2, sizeSet.begin());
// Jesli aktualny wynik jest mniejszy od wielkosci ogranicznika * wysokosc aktualnego punktu, to zaktualizuj wynik
		if (res < it2->size * (LL)l[x].z) {
			res = it2->size * (LL)l[x].z;
			ores.x = it2->x;
			ores.y = it2->y;
			ores.z = l[x].z;
		}
		el e = el(l[x].x, l[x].y);
// Nalezy dodac aktualny punkt do struktur ogranicznikow - najpierw znajdz ogranicznik najblizszy aktualnemu punktowi
		VAR(it, xSet.lower_bound(e));
// Jesli aktualny punkt bardziej ogranicza niz poprzedni ogranicznik, to nalezy wymienic ograniczniki...
		if (it != xSet.end() && it->y > e.y) {
			el f = el(l[x].x, it->y);
// Usuñ stary ogranicznik
			sizeSet.erase(*it);
			xSet.erase(*it);
			e.x = it->x;
// Dopoki istnieja ograniczniki, ktore powinnismy usunac ze wzgledu na aktualny punkt, zrob to...
			while(1) {
			    VAR(it2, xSet.lower_bound(e));
			    if (it2 == xSet.end() || it2->y < e.y) break;
			    e.x = it2->x;
    			sizeSet.erase(*it2);
			    xSet.erase(*it2);
			}
// Dodaj aktualny punkt jako ogranicznik
			e.size = (LL)e.x*(LL)e.y;
			xSet.insert(e);
			xSet.insert(f);
			sizeSet.insert(e);
			sizeSet.insert(f);
		}
	}
// Wypisz wynik
	cout << ores.x << " " << ores.y << " " << ores.z << endl;
	return 0;
}
