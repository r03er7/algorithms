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
#include <bitset>
// Funkcja rozwiazuje uklad rownañ w ciele Z2
template<const int s> int GaussZ2(vector<bitset<s> > equ, VI vals, VI &res) {
	int n=SIZE(equ),a=0,b=0,c;
// ustaw odpowiednia wielkosc wektora wynikowego
	res.resize(s, 0);
// Dla kolejnej niewiadomej xb...
	for(;a<n && b<s;b++) {
// Wyznacz pierwsze rownanie sposrod rownañ [a..n-1], w ktorym wspolczynnik przy zmiennej xb jest niezerowy
		for(c=a; c<n && !equ[c][b]; c++);
// Jesli znaleziono takie rownanie...
		if (c<n) {
// Jesli w rownaniu numer a wspolczynnik przy xb jest rowny 0, to dodaj (modulo 2) rownanie numer c do a
			if (a!=c) {equ[a]^=equ[c]; vals[a]^=vals[c];}
// Dla wszystkich rownañ roznych od a, wyeliminuj z nich wspolczynnik przy xb
			REP(y,n) if(a!=y && equ[y][b]) {equ[y]^=equ[a]; vals[y]^=vals[a];}
// Zapamietaj numer rownania, w ktorym wspolczynnik przy zmiennej xb jest rozny od 0
			res[b]=++a;
		}
  }
// Dla kazdej niewiadomej, jesli istnieje dla niej rownanie z niezerowym wspolczynnikiem, to wyznacz jej wartosc z tego rownania
  REP(x,b) if (res[x]) res[x] = vals[res[x]-1];
// Sprawdz, czy wyznaczone rozwiazanie spelnia uklad rownañ
  REP(x,n) {
    c=0;
    REP(z,s) if(equ[x][z]) c^=res[z];
    if (c!=vals[x]) return -1;
  }
// Zwroc wymiar przestrzeni rozwiazañ
  return s-a;
}
#define Nr(x,y) (wy*(x)+y)
// Makro zaznacza odpowiednia zmienna w macierzy rownania liniowego
#define Mark(ox,oy) if (ox >= 0 && oy >= 0 && ox < wx && oy < wy) equ[Nr(x,y)][Nr(ox,oy)] = 1;

int main() {
	int wx, wy;
// Wczytaj wymiary parkietu
	cin >> wx >> wy;
	vector<bitset<225> > equ(wx*wy);
	vector<string> mp(wy);
	VI vals(wx*wy,0), res;
// Wczytaj opis parkietu
	REP(y, wy) cin >> mp[y];
// Skonstruuj uklad rownañ
	REP(x, wx) REP(y, wy) {
		Mark(x, y);
		Mark(x-1, y);
		Mark(x+1, y);
		Mark(x, y-1);
		Mark(x, y+1);
		if (mp[y][x] == '0') vals[Nr(x,y)] = 1;
	}
// Rozwiaz uklad rownañ
	int r = GaussZ2<225>(equ, vals, res);
// Wypisz wynik
	if (r < 0) cout << "-1"  << endl; else {
		int count = 0;
		REP(x, wx*wy) if (res[x]) count++;
		cout << count << endl;
		REP(x, wx) REP(y, wy) if (res[Nr(x,y)]) cout << y+1 << " " << x+1 << endl;
	}
	return 0;
}
