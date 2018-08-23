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
// Struktura reprezentujaca punkt o wspolrzednych calkowitoliczbowych
struct POINT {
    int x,y;
// Konstruktor punktu pozwalajacy na skrocenie zapisu wielu funkcji wykorzystujacych punkty - w szczegolnosci operacje wstawiania punktow do struktur danych
    POINT(int x = 0, int y = 0) : x(x), y(y) {}
// Operator sprawdzajacy, czy dwa punkty sa sobie rowne.
    bool operator ==(POINT& a) {return a.x==x && a.y==y;}
}; /* newpage*/
// Operator uzywany przez przykladowe programy do wypisywania struktury punktu
ostream& operator<<(ostream& a, POINT& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
// Operator okreslajacy liniowy porzadek na zbiorze punktow po wspolrzednych (x, y)
bool OrdXY(POINT *a, POINT *b) {
	return a->x==b->x ? a->y<b->y : a->x<b->x;
}
// Makro wyznacza wartosc iloczynu wektorowego (a -> b)*(a -> c)
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
#define XCAL {while(SIZE(w) > m && Det((*w[SIZE(w) - 2]), (*w[SIZE(w) - 1]), \
	(*s[x])) <= 0) w.pop_back(); w.PB(s[x]);} 
// Funkcja wyznaczajaca wypukla otoczke dla zbioru punktow
vector<POINT*> ConvexHull(vector<POINT>& p) {
	vector<POINT*> s, w;
// Wypelnij wektor s wskaznikami do punktow, 
// dla ktorych konstruowana jest wypukla otoczka
	FOREACH(it, p) s.PB(&*it);
// Posortuj wskazniki punktow w kolejnosci 
// (niemalejace wspolrzedne x, niemalejace wspolrzedne y)
	sort(ALL(s), OrdXY);
	int m = 1;
// Wyznacz dolna czesc wypuklej otoczki - laczaca najbardziej lewy - dolny 
// punkt z najbardziej prawym - gornym punktem
	REP(x, SIZE(s)) XCAL
	m = SIZE(w);
// Wyznacz gorna czesc otoczki
	FORD(x, SIZE(s) - 2, 0) XCAL
// Usuñ ostatni punkt (zostal on wstawiony do otoczki dwa razy)
	w.pop_back();
	return w;
}
bool PointInsideConvexPol(vector<POINT>& l, POINT p){
	int a = 1, b = SIZE(l)-1, c;
// Jesli odcinek (l[0] -> l[a]) lezy na prawo od odcinka (l[0] -> l[b]) to nastepuje zamiana
	if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
// Jesli punkt p nie lezy po prawej stronie prostej (l[0] -> l[a]) lub po lewej stronie (l[0] -> l[b]) to nie nalezy do wielokata
	if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
// Wyszukiwanie binarne wycinka plaszczyzny zawierajacego punkt p
	while(abs(a-b) > 1) {
		c = (a+b)/2;
		if (Det(l[0], l[c], p) > 0) b = c; else a = c;
	}
// Jesli punkt p lezy w trojkacie (l[0],l[a],l[b]), to nalezy do wielokata
	return Det(l[a], l[b], p) < 0;
}
int main() {
	int n, m;
// Wczytaj liczbe Bito-serwerow oraz sugerowanych lokalizacji pomnikow
	cin >> n >> m;
	vector<POINT> l(n), l2;
	POINT p;
// Wczytaj kolejne pozycje Bito-serwerow
	REP(x,n) cin >> l[x].x >> l[x].y;
// Konstruuj wypukla otoczke dla zbioru serwerow
	vector<POINT*> hull = ConvexHull(l);
	l2.resize(SIZE(hull));
	REP(x, SIZE(hull)) l2[x] = *hull[x];
// Dla kolejnych sugerowanych lokalizacji pomnikow...
	REP(x,m) {
// Wczytaj pozycje
		cin >> p.x >> p.y;
// Jesli lokalizacja znajduje sie wewnatrz wypuklej otoczki, to pomnik moze zaklocac komunikacje
		cout << (PointInsideConvexPol(l2, p) ? "NIE" : "TAK") << endl;
	}
	return 0;
}
