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
// Struktura umozliwia dodawanie elementow i wyznaczanie statystyk pozycyjnych
struct PosTree {
    int* el, s;
// Konstruktor przyjmuje jako parametr wysokosc konstruowanego drzewa (dziedzina elementow to [0..2^size-1])
    PosTree(int size) {
	el = new int[1<<((s=size)+1)];
	REP(x,1<<(s+1)) el[x]=0;
    }
// Destruktor zwalnia zaalokowana pamiec
    ~PosTree(){delete[] el;}
// Funkcja dodaje v wystapie� elementu p (v moze byc ujemne)
    void Add(int p,int v){
// Dla kazdego wezla drzewa od liscia p do korzenia, aktualizowana jest liczba elementow w poddrzewie
		for(p=(1<<s)+p;p>0;p=p>>1) el[p]+=v;}
// Funkcja wyznacza p-ta statystyke pozycyjna
    int Find(int p) {
// Przeszukiwanie rozpoczynane jest od korzenia drzewa
		int po=1;
		REP(x,s) {
// Nastepuje przejscie do lewego syna aktualnego wezla
			po<<=1;
// Jesli aktualne poddrzewo zawiera mniej elementow niz wynosi numer wyszukiwanej statystyki pozycyjnej, to nastepuje przejscie do prawego syna
			if (el[po] < p) p-=el[po++];
		}
// Zwracany jest numer znalezionego elementu
		return po-(1<<s);
	}
};
int b[1000001], a[1000001], n;
PosTree tree(20);

int main() {
// Wczytaj liczbe elementow permutacji
	cin >> n;
// Wczytaj kolejne elementy kodu permutacji oraz zaznacz wszystkie elementy permutacji [1..n] jako aktywne
	REP(x, n) {
		cin >> b[x];
		tree.Add(x+1, 1);
	}
// Dla kolejnych elementow kodu permutacji, zaczynajac od prawej strony...
	FORD(x, n-1, 0) {
// Jesli kod permutacji jest nieprawidlowy, to wypisz wynik 'NO'
		if (b[x] > x) {
			cout << "NIE" << endl;
			return 0;
		}
// Wyznacz kolejny element permutacji jako 'x-b[x]+1' najmniejszy aktywny element oraz zaznacz jako jako nieaktywny
		tree.Add(a[x] = tree.Find(x-b[x]+1), -1);
	}
// Wypisz wynik
	REP(x, n) cout << a[x] << endl;
	return 0;
}
