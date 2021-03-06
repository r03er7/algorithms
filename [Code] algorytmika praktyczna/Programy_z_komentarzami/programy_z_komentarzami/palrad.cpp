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
// Funkcja wylicza promienie palindromow danego tekstu
VI PalRad(const char *x, bool p) 
{
	int n = strlen(x), i = 1, j = 0, k;
	VI r(n, 0);
	while(i < n) {
// Dopoki kolejno sprawdzane litery palindromu o srodku na pozycji 
// i sa takie same, zwieksz promie�
		while(i + j + p < n && i > j && x[i - j - 1] == x[ i + j + p]) j++;
// Stosujac zaleznosci miedzy promieniami palindromow wyznacz 
// jak najwiecej kolejnych promieni
		for(r[i] = j, k = 0; ++k <= j && r[i - k] != j - k;) 
			r[i + k] = min(r[i - k], j - k);
		j = max(0, j - k);
		i += k;
	}
	return r;
}
int main() {
	string text;
// Wczytaj tekst
	cin >> text;
	cout << "Analizowany tekst: " << text << endl;
// Wyznacz promienie palindromow parzystych
	VI res = PalRad(text.c_str(), 0);
	cout << "Palindromy parzyste: ";
	FOREACH(it, res) cout << " " << (*it);
	cout << endl;
// Wyznacz promienie palindromow nieparzystych
	res = PalRad(text.c_str(), 1);
	cout << "Palindromy nieparzyste: ";
	FOREACH(it, res) cout << " " << (*it);
	cout << endl;
	return 0;
}
