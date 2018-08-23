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
#define TPL template<class T> inline
#define CR(t) const t&
#define RET return
TPL T gcd(CR(T)a,CR(T)b) { RET b?gcd(b,a%b):a; }
// Funkcja sluzaca do wyznaczania najwiekszego wspolnego dzielnika dwoch liczb
LL GCD(LL a,LL b) { 
	while(b) swap(a%=b,b);
	return a;
}
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
// Funkcja wylicza wspolrzedna calkowitoliczbowa, przez ktora przebiega kula bilardowa, poruszajaca sie wzdloz wektora [a,b]
LL Offset(LL a, LL b, LL c)
{
	if (a == 0) return b == 0 ? 0 : -1;
	LL v1, v2, dz;
	dz = GCDW(a, c, v1, v2);
	if (b % dz != 0) return -1;
	dz = b / dz;
	v1 *= dz;
	v2 *= dz;
	LL pos = -v1*a, layer = c*(a/GCD(a,c));
	pos %= layer;
	if (pos < 0) pos += layer;
	return pos;
}

int main()
{
	LL sx, sy, px, py, wx, wy;
// Wczytaj opis stolu oraz pozycje kuli
	cin >> sx >> sy >> px >> py >> wx >> wy;
	sx /= 2;
	bool rotx = false, roty = false;
// Jesli kula porusza sie w prawo, to dokonaj 'odbicia'
	if (wx < 0) {
		rotx = true;
		wx = -wx;
		px = 2*sx - px;
	}
// Jesli kula porusza sie w dol, to dokonaj 'odbicia'
	if (wy < 0) {
		roty = true;
		wy = -wy;
		py = sy - py;
	}
// Dokonaj zredukowania wektora do postaci nieskracalnej
	LL nw = GCD(wx, wy);
	if (nw) {
		wx /= nw;
		wy /= nw;
	}
	LL wsp = Offset(wx, px, sx);
	if (wsp == -1) {
		cout << "NIE" << endl;
		return 0;
	}
	if (wsp) {
		px = (px + wsp) % (4*sx);
		py = (py + (wsp/wx)*wy) % (2*sy);
	}
	wsp = Offset(wy*(sx/GCD(sx, wx)), py % sy, sy);
	if (wsp == -1) {
		cout << "NIE" << endl;
		return 0;
	}
	if (wsp) {
		py += wsp;
		px += (wsp/wy)*wx;
	}
	if (rotx)
		px = -px + sx*2;
	if (roty)
		py = -py + sy;
	cout << (((py % (2*sy)) == 0) ? 'D' : 'G');
	if ((px % (4*sx)) == 0) 
		cout << "L" << endl;
	else if ((px % (2*sx)) == 0)
		cout << "P" << endl;
	else
		cout << "S" << endl;
	return 0;
}
