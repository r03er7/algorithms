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
#define TPL template<class T> inline
#define CR(t) const t&
#define RET return
TPL T gcd(CR(T)a,CR(T)b) { RET b?gcd(b,a%b):a; }
// Funkcja wyznacza najwiekszy wspolny dzielnik dwoch liczb oraz wspolczynniki l i k
int GCDW(int a, int b, LL &l, LL &k) {
    if (!a) { 
// gcd(0, b) = 0 * 0 + 1 * b
		l=0; k=1; return b; }
// Wyznacz rekurencyjnie wartosc najwiekszego wspolnego dzielnika oraz wspolczynniki l oraz k
    int d = GCDW(b%a, a, k, l);
// Zaktualizuj wartosci wspolczynnikow oraz zwroc wynik
    l -= (b/a)*k;
    return d;
}
// Funkcja wyznacza odwrotnosc modularna liczby a (mod m)
int RevMod(int a, int m){ 
	LL x, y;
	if (GCDW(a, m, x, y) != 1) return -1;
// Dokonaj przesuniecia zmiennej x, tak aby znajdowala sie w przedziale [0..m-1]
	x %= m;
	if (x < 0) x += m;
	return x;
}
// Funkcja rozwiazuje dany uklad rownañ w ciele Zp
int Gauss(vector<VI>& A, VI &b, VI &x, int P){ 
	int m = SIZE(A), n = SIZE(A[0]), k, r;
	VI q;
	for (k = 0; k < min(m, n); k++) {
		int i, j;
		for (j = k; j < n; j++)
			for (i = k; i < m; i++)
				if (A[i][j] != 0) goto found;
		break;
		found:
		if (j != k) REP(t, m) swap(A[t][j], A[t][k]);
		q.PB(j);
		if (i != k) {
			swap(A[i], A[k]); 
			swap(b[i], b[k]);
		}
		FOR(j, k + 1, m - 1) if (A[j][k] != 0) {
			int l = (A[j][k] * RevMod(A[k][k], P)) % P;
			FOR(i, k + 1, n - 1) A[j][i] = (P + A[j][i] - (l * A[k][i]) % P) % P;
			b[j] = (P + b[j] - (l * b[k]) % P) % P;
		}
	}
	r = k;
	x.clear(); 
	x.resize(n, 0);
	FOR(k, r, m - 1) if (b[k] != 0) return -1;
	FORD(k, r - 1, 0) {
		int s = b[k];
		FOR(j, k + 1, r - 1) s = (P + s - (A[k][j] * x[j]) % P) % P;
		x[k] = (s * RevMod(A[k][k], P)) % P;
	}
	FORD(k, r - 1, 0) swap(x[k], x[q[k]]);
	return n - r;
}
int main() {
	int s,p;
// Wczytaj liczbe szyfratorow oraz dozwolonych pozycji
	cin >> s >> p;
	vector<int> szyfratory(s), blokada(s), res(s);
	vector<vector<int> > pos(s, vector<int>(s));
// Wczytaj pozycje kolejnych szyfratorow
	REP(x, s) cin >> szyfratory[x];
// Wczytaj pozycje blokad
	REP(x, s) {
		cin >> blokada[x];
		blokada[x] = (p - blokada[x]) % p;
	}
// Wczytaj opisy kolejnych szyfratorow
	REP(x, s) REP(y, s) cin >> pos[y][x];
// Rozwiaz ukladu rownañ modularnych stworzony na podstawie opisu sejfu
	Gauss(pos, blokada, res, p);
// Wypisz wynik
	REP(x, s) {
		if(x) cout << " ";
		cout << ((res[x] + szyfratory[x]) % p);
	}
	cout << endl;
	return 0;
}
