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
// Funkcja sprawdza, czy dwa dane teksty sa swoimi rownowaznosciami cyklicznymi
bool cycEq(const char *s1, const char *s2) {
    int n=strlen(s1),i=0,j=0,k=0;
    if (n!=strlen(s2)) return 0;
    while (i<n && j<n && k<n) {
		k=1;
		while(k<=n && s1[(i+k)%n] == s2[(j+k)%n]) k++;
		if (k<=n)
			if (s1[(i+k)%n] > s2[(j+k)%n]) i+=k; else j+=k;
    }
    return k>n;
}
int main() { 
	int n;
// Wczytaj liczbe tekstow oraz poszczegolne teksty
	cin >> n;
	vector<string> text(n);
	REP(x,n) cin >> text[x];
// Dla kazdej pary tekstow wyznacz, czy sa one rownowazne cyklicznie
	REP(x, n) REP(y, x)
		cout << "Slowa " << text[x] << " i " << text[y] << 
			(cycEq(text[x].c_str(), text[y].c_str()) ? "" : " nie") << 
			" sa rownowazne cyklicznie" << endl;
	return 0;
}
