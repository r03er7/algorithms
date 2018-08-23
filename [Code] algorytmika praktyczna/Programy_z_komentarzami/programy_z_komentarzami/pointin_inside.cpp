#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach - 
// ich skrocenie jest bardzo istotne
typedef vector<int> VI;
typedef long long LL;

// W programach bardzo rzadko mozna znalezc w pelni zapisana instrukcje petli.
// Zamiast niej wykorzystywane sa trzy nastepujace makra:
// FOR - petla zwiekszajaca zmienna x od b do e wlacznie
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
// FORD - petla zmniejszajaca zmienna x od b do e wlacznie
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
// REP - petla zwiekszajaca zmienna x od 0 do n. Jest ona bardzo czesto
// wykorzystywana do konstruowania i przegladania struktur danych
#define REP(x, n) for(int x = 0; x < (n); ++x)
// Makro VAR(v,n) deklaruje nowa zmienna o nazwie v oraz typie i wartosci
// zmiennej n. Jest ono czesto wykorzystywane podczas operowania na iteratorach
// struktur danych z biblioteki STL, ktorych nazwy typow sa bardzo dlugie
#define VAR(v, n) __typeof(n) v = (n)
// ALL(c) reprezentuje pare iteratorow wskazujacych odpowiednio na pierwszy
// i za ostatni element w strukturach danych STL. Makro to jest bardzo 
// przydatne chociazby w przypadku korzystania z funkcji sort, ktora jako 
// parametry przyjmuje pare iteratorow reprezentujacych przedzial 
// elementow do posortowania
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL.
// Uzywa sie go w programach, zamiast pisac po prostu x.size() ze 
// wzgledu na to, iz wyrazenie x.size() jest typu unsigned int i w 
// przypadku porownywania
// z typem int w procesie kompilacji generowane 
// jest ostrzezenie
#define SIZE(x) ((int)(x).size())
// Bardzo pozyteczne makro sluzace do iterowania po wszystkich elementach 
// w strukturach danych STL
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
// Skrot - zamiast pisac push_back podczas wstawiania elementow na koniec 
// struktury danych, takiej jak vector, wystarczy napisac PB
#define PB push_back
// Podobnie - zamiast first bedziemy pisali po prostu ST
#define ST first
// a zamiast second - ND
#define ND second
// Stala EPS jest uzywana w wielu algorytmach geometrycznych do porownywania 
// wartosci bliskich zera
const double EPS = 10e-9;
inline double sqr(double a) {return a*a;}
// Struktura reprezentujaca punkt o wspolrzednych calkowitoliczbowych
struct POINT {
    int x,y;
// Konstruktor punktu pozwalajacy na skrocenie zapisu wielu funkcji 
// wykorzystujacych punkty - w szczegolnosci operacje wstawiania punktow 
// do struktur danych
    POINT(int x = 0, int y = 0) : x(x), y(y) {}
// Operator sprawdzajacy, czy dwa punkty sa sobie rowne
    bool operator ==(POINT& a) {return a.x==x && a.y==y;}
}; /* newpage*/
// Operator uzywany przez przykladowe programy do wypisywania struktury punktu
ostream& operator<<(ostream& a, POINT& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
// Makro wyznacza wartosc iloczynu wektorowego (a -> b)*(a -> c)
#define Det(a, b, c) (LL(b.x - a.x) * LL(c.y - a.y) - LL(b.y - a.y) * (c.x - a.x))
#define PointInRect(p1, p2, p3) (min(p1.x, p2.x) <= p3.x && \
min(p1.y, p2.y) <= p3.y && max(p1.x, p2.x) >= p3.x && max(p1.y, p2.y) >= p3.y)
#define PointInsideRect(p1, p2, p3) (min(p1.x, p2.x) < p3.x && \
min(p1.y, p2.y) < p3.y && max(p1.x, p2.x) > p3.x && max(p1.y, p2.y) > p3.y)
#define PointInSegment(p1, p2, l) (Det(p1, p2, l) == 0 && PointInRect(p1, p2, l))
#define PointInsideSegment(p1, p2, l) (Det(p1, p2, l) == 0 && PointInsideRect(p1, p2, l))
#define PointInCircle(c, r, p) (sqr(c.x - p.x) + sqr(c.y - p.y) - EPS < sqr(r))
#define PointInsideCircle(c, r, p) (sqr(c.x - p.x) + sqr(c.y - p.y) + EPS < sqr(r))
int main() { 
	POINT r1,r2,c,s1,s2,p;
	int r;
// Wczytaj wspolrzedne wierzcholkow wyznaczajacych prostokat
	cin >> r1.x >> r1.y >> r2.x >> r2.y;
// Wczytaj wspolrzedne punktow wyznaczajacych odcinek
	cin >> s1.x >> s1.y >> s2.x >> s2.y;
// Wczytaj srodek oraz promien okregu
	cin >> c.x >> c.y >> r;
	cout << "\t\t\t    Rectangle\t\t    Segment\t\t     Circle" << endl;
	cout << "\t\t\tInside\t In\t    Inside\t In\t    Inside\t In" << endl;
// Dla wszystkich punktow wyznacz wynik dzialania poszczegolnych makr
	while(cin >> p.x >> p.y) {
		cout << p << "\t\t" << PointInsideRect(r1, r2, p) << "\t\t" << 
			PointInRect(r1, r2, p) << "\t\t" << 
			PointInsideSegment(s1, s2, p) << "\t\t" << 
			PointInSegment(s1, s2, p) << "\t\t" << 
			PointInsideCircle(c, r, p) << "\t\t" << 
			PointInCircle(c, r, p) << endl;
	}
	return 0;
}
