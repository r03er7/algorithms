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
// Funkcja przeprowadza test Millera-Rabina dla liczby x przy podstawie n
bool MaR(LL x,LL n) {
    if (x>=n) return 0;
    LL d=1,y;
    int t=0,l=n-1;
    while (!(l&1)) {++t; l>>=1;}
    for(;l>0 || t--;l>>=1) {
	if(l&1) d=(d*x)%n;
	if(!l) {x=d; l=-1;}
        y=(x*x)%n;
// Jesli test Millera wykryl, ze liczba nie jest pierwsza, to zwroc prawde
	if(y==1 && x!=1 && x!=n-1) return 1;
	x = y;
    }
// Jesli nie jest spelnione zalozenie twierdzenia Fermata, to liczba jest zlozona
    return x!=1;
}
// Funkcja sprawdza, czy dana liczba x jest pierwsza. W tym celu wykonuje test Millera-Rabina przy podstawie 2, 3, 5, 7
bool IsPrime(int x) {
    return !(x<2 || MaR(2,x) || MaR(3,x) || MaR(5,x) || MaR(7,x));
}
int main() {
	int b, e, count = 0;
// Wczytaj przedzial testowanych liczb
	cin >> b >> e;
// Dla kazdej liczby z przedzialu sprawdz, czy jest pierwsza
	while(b<e) {
		if (IsPrime(b)) cout << b << (!(++count % 5) ? "\n" : "\t");
		b++;
	}
	return 0;
}
