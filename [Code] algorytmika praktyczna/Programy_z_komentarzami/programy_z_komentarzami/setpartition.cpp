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
// Funkcja wyznacza wszystkie podzialy n-elementowego zbioru
void SetPartition(int n, void (*fun)(VI&)) { 
	VI B(n, 1), N(n + 1), P(n + 1);
	vector<bool> Pr(n + 1, 1);
	N[1] = 0;
	fun(B);
	for(int i, k, j = n; j > 1;) {
		k = B[j - 1];
		if(Pr[j]) {
			if(!N[k]) P[N[k] = j + (N[j] = 0)] = k;
		    	if(N[k] > j) N[P[j] = k] = P[N[j] = N[k]] = j;
// W tym miejscu nastepuje przydzielenie elementu j do zbioru o numerze N[k]
			B[j - 1] = N[k];
		} else {
// W tym miejscu nastepuje przydzielenie elementu j do zbioru o numerze P[k]
			B[j - 1] = P[k];
			if(k == j) N[k] ? P[N[P[k]] = N[k]] = P[k] : N[P[k]] = 0;
		}
		fun(B);
		j = n;
		while(j > 1 && ((Pr[j] && (B[j - 1] == j)) 
			|| (!Pr[j] && (B[j - 1] == 1)))) Pr[j--] = !Pr[j];
	}
}
// Funkcja wywolywana dla kazdego wyznaczonego podzialu zbioru
void Display(VI& v) {
	static int calc = 0;
	if (!(calc++ % 6)) cout << endl;
// Wypisz wyznaczony podzial zbioru
	FOREACH(it, v) cout << *it << " ";
	cout << "\t";
}

int main() {
// Wyznacz wszystkie podzialy 4-elementowego zbioru
	SetPartition(4, &Display);
	return 0;
}
