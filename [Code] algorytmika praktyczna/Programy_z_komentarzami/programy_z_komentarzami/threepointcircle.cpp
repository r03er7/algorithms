#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>

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
// Stala EPS jest uzywana w wielu algorytmach geometrycznych do porownywania wartosci bliskich zera
const double EPS = 10e-9;
inline double sqr(double a) {return a*a;}
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
// Struktura reprezentujaca punkt o wspolrzednych rzeczywistych
struct POINTD {
    double x,y;
// Konstruktor punktu
    POINTD(double wx = 0, double wy = 0) : x(wx), y(wy) {}
// Konstruktor POINTD z typu POINT - jest on potrzebny w celu wykonywania automatycznej konwersji miedzy POINT a POINTD.
	POINTD(const POINT& p) : x(p.x), y(p.y) {}
// Operator sprawdzajacy, czy dwa punkty sa sobie rowne. Ze wzgledu na reprezentowanie wspolrzednych punktow przy uzyciu zmiennych double, operator porownuje wspolrzedne punktow z pewna tolerancja
    bool operator ==(POINTD& a) {return IsZero(a.x-x) && IsZero(a.y-y);}
};
// Operator uzywany przez przykladowe programy do wypisywania struktury punktu
ostream& operator<<(ostream& a, POINTD& p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}
int LineCrossPoint(POINTD p1, POINTD p2, POINTD l1, POINTD l2, POINTD &prz){
// Iloczyn wektorowy (p1 -> p2) i (l1 -> l2)
  double s, t = (p1.x - p2.x) * (l1.y - l2.y) - (p1.y - p2.y) * (l1.x - l2.x);
// Iloczyn wektorowy (l2 -> p2) i (l1 -> l2)
  s = (l2.x - p2.x) * (l1.y - l2.y) - (l2.y - p2.y) * (l1.x - l2.x);
// Jesli proste sa rownolegle (t == 0), to istnieje nieskoñczenie wiele punktow wspolnych wtw gdy proste sie pokrywaja (iloczyn wektorowy s == 0)
  if (IsZero(t)) return IsZero(s) ? 2 : 0;
  s = s/t;
// Istnieje jeden punkt wspolny - wyznacz jego wspolrzedne
  prz.x = s * p1.x + (1-s) * p2.x;
  prz.y = s * p1.y + (1-s) * p2.y;
  return 1;
}
// Funkcja znajduje okrag wyznaczony przez trzy punkty lub zwraca falsz, 
// jesli taki okrag nie istnieje
bool ThreePointCircle(POINTD p1, POINTD p2, POINTD p3, POINTD &c, double &r){ 
// Wyznacz punkt przeciecia symetralnych trojkata (p1, p2, p3)
	if (LineCrossPoint(POINTD((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0), 
		POINTD((p1.x + p2.x) / 2.0 + p2.y - p1.y, (p1.y + p2.y) / 2.0 + p1.x 
		- p2.x), POINTD((p1.x + p3.x) / 2.0, (p1.y + p3.y) / 2.0), 
		POINTD((p1.x + p3.x) / 2.0 + p3.y - p1.y, 
			(p1.y + p3.y) / 2.0 + p1.x - p3.x) ,c) != 1)
	return false;
// Wylicz promieñ okregu o srodku w punkcie c
	r = sqrt(sqr(p1.x - c.x) + sqr(p1.y - c.y));
	return true;
}
int main() {
	vector<POINT> l;
	POINT p;
	POINTD po;
	double r;
	bool res;
// Wczytaj liste punktow
	while(cin >> p.x >> p.y) l.PB(p);
// Dla kazdej trojki punktow, wyznacz okrag na nich opisany
	REP(x, SIZE(l)) REP(y, x) REP(z, y) {
		cout << "Punkty: " << l[x] << ", " << l[y] << ", " << l[z] << endl;
		if (!ThreePointCircle(l[x], l[y], l[z], po, r))
			cout << "Punkty sa wspolliniowe" << endl;
		else
			cout << "Srodek okregu = " << po << ", promien = " << r << endl;
	}
	return 0;
}
