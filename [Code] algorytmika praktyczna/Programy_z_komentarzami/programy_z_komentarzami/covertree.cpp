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
// Struktura umozliwia dodawanie i usuwanie odcinkow oraz wyznaczanie 
// wielkosci obszaru przez nie pokrytego
struct CoverTree { 
#define nr (wp + wk + 1) >> 1
	int *el, *ma, s, p, k, il;
// Konstruktor przyjmuje jako parametr wysokosc konstruowanego drzewa (koñce 
// odcinkow, na ktorych wykonywane sa operacje naleza do przedzialu [0..2^size-1])
	CoverTree(int size) {
// Tablica el przechowuje liczbe odcinkow pokrywajacych w calosci przedzial
// reprezentowany przez odpowiedni wezel
		el = new int[s = 1 << (size + 1)];
// Tablica ma przechowuje sumaryczna pokryta powierzchnie przedzialu 
// reprezentowanego przez odpowiedni wezel
		ma = new int[s];
		REP(x, s) el[x] = ma[x] = 0;
	}
// Destruktor zwalnia zaalokowana pamiec
	~CoverTree() {
		delete[] el;
		delete[] ma;
	}
// Funkcja pomocnicza wykorzystywana przez operacje dodawania i usuwania odcinkow. 
// Wykonuje ona aktualizacje wartosci w wezlach
	void Mark(int wp, int wk, int g) {
// Jesli dodawany/usuwany odcinek jest rozlaczny z przedzialem 
// reprezentowanym przez aktualny wezel, to przerwij
		if(k<=wp || p>=wk) return;
// Jesli odcinek pokrywa w calosci przedzial aktualnego wezla, to zmieñ wartosc el,
		if(p<=wp && k>=wk) el[g] += il; else {
// a jesli nie, to wykonaj aktualizacje zmiennych synow aktualnego wezla
			Mark(wp, nr, 2 * g); 
			Mark(nr, wk, 2 * g + 1);
		}
// Dokonaj aktualizacji pokrytego obszaru przetwarzanego przedzialu
		ma[g] = el[g] > 0 ? wk - wp : 
			(wk - 1 == wp ? 0 : ma[2 * g] + ma[2 * g + 1]);
	}
// Funkcja dodajaca i1 wystapieñ odcinka [p1..k1] do drzewa. W przypadku,
// gdy i1 jest wartoscia ujemna, nastepuje usuniecie odcinka
	void Add(int p1, int k1, int i1) {
		p = p1;
		k = k1;
		il = i1;
		Mark(0, s / 2, 1);
	}
// Funkcja pomocnicza sluzaca do wyznaczania wielkosci obszaru 
// [wp, wk] pokrytego przez odcinki
    int F(int wp, int wk, int g) {
// Jesli testowany odcinek jest rozlaczny z aktualnym przedzialem, 
// to pokrycie jest rowne 0
		if (wp >= k || wk <= p) return 0;
// Jesli przedzial jest w calosci pokryty, to zwroc wielkosc 
// czesci wspolnej testowanego odcinka i przedzialu
		if (el[g] > 0) return min(k, wk) - max(p, wp);
// Jesli odcinek pokrywa w calosci przedzial, to zwroc pokrycie przedzialu
		if (p <= wp && wk <= k) return ma[g];
// Zwroc jako wynik sume pokryc swoich synow
		return wp == wk - 1 ? 0 : F(wp, nr, 2 * g) + F(nr, wk, 2 * g + 1);
    }
// Wlasciwa funkcja realizujaca wyznaczanie wielkosci obszaru 
// [p1, k1] pokrytego przez odcinki
    int Find(int p1, int k1) { 
		p = p1;
		k = k1;
		return F(0, s / 2, 1);
	}
};
int main() { 
	int w1, w2, w3;
// Skonstruuj drzewo pokryciowe dla przedzialu [0..15]
	CoverTree tree(4);
// Wczytaj polecenia i wykonaj je...
	while(cin >> w1 >> w2 >> w3) {
		if (w1 == 0) {
// Operacja dodawania nowego odcinka
			tree.Add(w2, w3, 1);
			cout << "Dodanie odcinka [" << w2 << "," << w3 << "]" << endl;
		} else if (w1 == 1) {
// Operacja usuwania odcinka
			tree.Add(w2, w3, -1);
			cout << "Usuniecie odcinka [" << w2 << "," << w3 << "]" << endl;
		} else
// Wyznaczanie pokrycia na przedziale [w2..w3]
			cout << "Pokrycie odcinka [" << w2 << "," << w3 << 
				"] = " << tree.Find(w2, w3) << endl;
	}
	return 0;
}
