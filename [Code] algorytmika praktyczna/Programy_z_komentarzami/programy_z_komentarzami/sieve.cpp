#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <bvector.h>

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
// Funkcja realizuje algorytm sita Eratostenesa
bit_vector Sieve(int s) { 
	bit_vector V(s+1,1);
	V[0] = V[1] = 0;
// Dla kolejnej liczby, jesli nie zostala ona wykreslona, to wykresl wszystkie jej wielokrotnosci
	FOR(x, 2, s) if(V[x] && LL(s) >= LL(x) * LL(x)) 
		for(int y = x * x; y <= s; y += x) V[y] = 0;
	return V;
}
int main() { 
	int n;
// Wczytaj wielkosc zakresu
	cin >> n;
	bit_vector V = Sieve(n);
// Dla kazdej liczby z zakresu wypisz, czy jest ona liczba pierwsza
	REP(x, n) cout << x << (V[x] ? " jest liczba pierwsza" 
		: " nie jest liczba pierwsza") << endl;
	return 0;
}
