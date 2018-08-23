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
// Wartosc INF jest wykorzystywana jako reprezentacja nieskoñczonosci. Ma ona wartosc 1000000001, a nie 2147483647 (najwieksza wartosc typu int) ze wzgledu na dwa fakty - prosty zapis oraz brak przepelnienia wartosci zmiennej w przypadku dodawania dwoch nieskoñczonosci do siebie: ((int) 2147483647 + (int) 2147483647 = -2).
const int INF = 1000000001;
// Stala EPS jest uzywana w wielu algorytmach geometrycznych do porownywania wartosci bliskich zera
const double EPS = 10e-9;
int sgn(LL x) { if (x==0LL) return 0; return (x>0LL) ? 1 : -1;}
// Funkcja sprawdza, czy podana liczba jest dostatecznie bliska 0
inline bool IsZero(double x){ return x>=-EPS && x<=EPS; }
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
// Makro wyznacza wartosc iloczynu wektorowego (a -> b)*(a -> c)
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
int sgn(double x){ return IsZero(x)?0:(x < 0 ? -1 : 1); }
int sgn(int x){ return !x?0:(x < 0 ? -1 : 1); }
#define PointInRect(p1,p2,p3) (min(p1.x, p2.x) <= p3.x && \
min(p1.y, p2.y) <= p3.y && max(p1.x, p2.x) >= p3.x && max(p1.y, p2.y) >= p3.y)
#define PointInSegment(p1,p2,l) (Det(p1,p2,l)==0 && PointInRect(p1,p2,l))
inline bool SegmentCross(POINT& p1, POINT& p2, POINT& l1, POINT& l2) {
    return sgn(Det(p1,p2,l1))*sgn(Det(p1,p2,l2)) == -1 && sgn(Det(l1,l2,p1))*sgn(Det(l1,l2,p2)) == -1;
}
bool PointInPol(vector<POINT>& l, POINT p) {
    int v=0,s=SIZE(l); POINT d(INF, p.y+1);
// Jesli punkt lezy na jednym z bokow wielokata, to zwroc prawde
    REP(x,s) if (PointInSegment(l[x], l[(x+1)%s], p)) return true;
// Wyznacz liczbe przeciec obwodu wielokata z polprosta (p -> d)
    REP(x,s) v += SegmentCross(p, d, l[x], l[(x+1)%s]);
// Jesli polprosta przecina obwod nieparzysta liczbe razy, to punkt nalezy do wielokata
    return v&1;
}
bool PointInsidePol(vector<POINT>& l, POINT p) {
    int v=0,s=SIZE(l); POINT d(INF, p.y+1);
// Jesli punkt lezy na jednym z bokow wielokata, to nie nalezy do wnetrza wielokata
    REP(x,s) if (PointInSegment(l[x], l[(x+1)%s], p)) return false;
// Wyznacz liczbe przeciec obwodu wielokata z polprosta (p -> d)
    REP(x,s) v += SegmentCross(p, d, l[x], l[(x+1)%s]);
// Jesli polprosta przecina obwod nieparzysta liczbe razy, to punkt nalezy do wielokata
	return v&1;
}
bool PointInConvexPol(vector<POINT>& l, POINT p){
	int a = 1, b = SIZE(l)-1, c;
// Jesli odcinek (l[0] -> l[a]) lezy na prawo od odcinka (l[0] -> l[b]) to nastepuje zamiana
	if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
// Jesli punkt p lezy po lewej stronie prostej (l[0] -> l[a]) lub po prawej stronie (l[0] -> l[b]) to nie nalezy do wielokata
	if (Det(l[0], l[a], p) > 0 || Det(l[0], l[b], p) < 0) return false;
// Wyszukiwanie binarne wycinka plaszczyzny zawierajacego punkt p
	while(abs(a-b) > 1) {
		c = (a+b)/2;
		if (Det(l[0], l[c], p) > 0) b = c; else a = c;
	}
// Jesli punkt p lezy w trojkacie (l[0],l[a],l[b]), to nalezy do wielokata
	return Det(l[a], l[b], p) <= 0;
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
	vector<POINT> pol;
	POINT p;
	int n;
// Wczytaj liczbe wierzcholkow wielokata
	cin >> n;
// Wczytaj kolejne wierzcholki wielokata oraz dodaj je do wektora
	REP(x, n) {
		cin >> p.x >> p.y;
		pol.PB(p);
	}
	cout << "\t\t\t\t Polygon\t\t\t\t  Convex Polygon" << endl;
	cout << "\t\t    Inside\t\t  In\t\t  Inside\t\t   In" << endl;
// Dla kolejnych punktow wyznacz ich przynaleznosc do wielokata przy uzyciu 
// poszczegolnych funkcji
	while(cin >> p.x >> p.y) cout << p << "\t\t" << 
		PointInsidePol(pol, p) << "\t\t\t" <<
		PointInPol(pol, p) << "\t\t\t" << 
		PointInsideConvexPol(pol, p) << "\t\t\t" << 
		PointInConvexPol(pol, p) << endl;
	return 0;
}
