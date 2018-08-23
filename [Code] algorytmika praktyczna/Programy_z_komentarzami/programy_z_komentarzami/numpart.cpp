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
// Funkcja generuje wszystkie podzialy liczby n
void NumPart(int n, void (*fun)(VI&, VI&, int)) {
    VI S(n+1), R(n+1);
    int d,sum,l;
    S[0]=n;
    R[0]=d=1;
    while(1) {
		int summ=0,x,s;
		fun(R, S, d);
		if (S[0]==1) break;
		sum=0;
		if(S[d-1]==1) sum+=R[--d];
		sum+=S[d-1];
		R[d-1]--;
		l=S[d-1]-1;
		if(R[d-1]) d++;
		S[d-1]=l;
		R[d-1]=sum/l;
		l=sum%l;
		if(l) {
			S[d]=l; 
			R[d++]=1;
		}
	}
}
// Funkcja wywolywana dla kazdego wyznaczonego podzialu liczby
void Display(VI& s, VI& r, int n) {
	bool ch=0;
// Wypisz kolejne elementy podzialu
	REP(x, n) REP(y, s[x]) {
		if (ch) cout << " + ";
//		REP(y, s[x]) 
		cout << r[x];
		ch = 1;
	}
	cout << endl;
}

int main() {
// Wygeneruj wszystkie podzialy liczby 5
	NumPart(5, &Display);
	return 0;
}
