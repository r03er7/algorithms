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
#include <list>
// Struktura umozliwia dodawanie elementow z przypisana wartoscia oraz sprawdzanie sumy wartosci na dowolnym przedziale elementow
struct CountTree {
    int* el, s;
// Konstruktor przyjmuje jako parametr wysokosc konstruowanego drzewa (dziedzina kluczy to [0..2^size-1])
    CountTree(int size) {
	el=new int[2*(s=1<<size)];
	REP(x,2*s) el[x]=0;
    }
// Destruktor zwalnia zaalokowana pamiec
    ~CountTree(){delete[] el;}
// Funkcja zmienia wartosc klucza p na v
    void Set(int p,int v){
// Do wszystkich wezlow na sciezce do korzenia dodawana jest wartosc v
		for(p+=s;p;p>>=1) el[p]+=v;}
// Funkcja wyznacza sume wartosci w spojnym przedziale elementow [p..k]
    int Find(int p, int k) {
	int m=0;
	p+=s; k+=s;
	while(p<k) {
	    if(p&1) m+=el[p++];
	    if(!(k&1)) m+=el[k--];
	    p>>=1; k>>=1;
	}
	if(p==k) m+=el[p];
	return m;
    }
};
int main() { 
	int w1, w2, w3;
// Skonstruuj drzewo dla dziedziny elementow [0..15]
	CountTree tree(4);
// Wykonaj liste operacji...
	while(cin >> w1 >> w2 >> w3) {
		if (w1 == 0) {
// Operacja zmiany wartosci elementu...
			tree.Set(w2, w3);
			cout << "Zmiana wartosci elementu " << w2 << " o " << w3 << endl;
		} else
// Wyznaczenie sumy wartosci na przedziale [w2..w3]
		cout << "Suma na przedziale " << w2 << ".." << w3 << 
			" = " << tree.Find(w2, w3) << endl;
	}
	return 0;
}
