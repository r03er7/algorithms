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
// Operator okreslajacy liniowy porzadek na zbiorze punktow po wspolrzednych (x, y)
bool OrdXY(POINT *a, POINT *b) {
	return a->x==b->x ? a->y<b->y : a->x<b->x;
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
// Makro wyznacza wartosc iloczynu wektorowego (a -> b)*(a -> c)
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
int sgn(double x){ return IsZero(x)?0:(x < 0 ? -1 : 1); }
int sgn(int x){ return !x?0:(x < 0 ? -1 : 1); }
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
inline bool SegmentCrossPoint(POINT p1, POINT p2, POINT l1, POINT l2, 
	vector<POINTD> &r) {
	r.clear(); 
	int w1 = sgn(Det(p1, p2, l1)), w2 = sgn(Det(p1, p2, l2)), 
		v1 = sgn(Det(l1, l2, p1)), v2 = sgn(Det(l1, l2, p2));
// Jesli punkty l1 i l2 znajduja sie po tej samej stronie prostej p1 -> p2 
// lub p1 i p2 znajduja sie po tej samej stronie prostej l1 -> l2, 
// to odcinki nie przecinaja sie
	if (w1*w2 > 0 || v1*v2 > 0) return false;
// Jesli punkty l1 i l2 leza na prostej p1 -> p2, to odcinki 
// l1 -> l2 i p1 -> p2 sa wspolliniowe
	if (!w1 && !w2) {
// Zamiana par punktow reprezentujacych odcinki, tak aby pierwsze punkty 
// w parach byly mniejsze w porzadku po wspolrzednych (x,y)
		if (OrdXY(&p2, &p1)) swap(p1, p2);
		if (OrdXY(&l2, &l1)) swap(l1, l2);
// Jesli odcinki sa rozlaczne, to nie ma punktow przeciecia
		if (OrdXY(&p2, &l1) || OrdXY(&l2,&p1)) return false;
// Wyznacz krañcowe punkty wspolne
		if (p2 == l1) r.PB(POINTD(p2.x, p2.y));
		else if (p1 == l2) r.PB(POINTD(l2.x, l2.y)); 
		else {
			r.PB(OrdXY(&p1, &l1) ? l1 : p1);
			r.PB(OrdXY(&p2, &l2) ? p2 : l2);
		}
	}
// Jesli jeden z odcinkow jest zdegenerowany, to jest on punktem przeciecia
	else if (l1 == l2) r.PB(l1);
	else if (p1 == p2) r.PB(p2);
	else {
// Wyznacz punkt przeciecia 
		double t = double(LL(l2.x - p2.x) * LL(l1.y - l2.y) - LL(l2.y - p2.y) * 
			LL(l1.x - l2.x)) / double(LL(p1.x - p2.x) * LL(l1.y - l2.y) - 
			LL(p1.y - p2.y) * LL(l1.x - l2.x));
		r.PB(POINTD(t * p1.x + (1.0 - t) * p2.x, t * p1.y + (1.0 - t) * p2.y));
	}
	return true;
}
int main() { 
	vector<POINT> b, e;
	vector<POINTD> l;
	int res;
	POINT p1, p2;
	POINTD p;
// Wczytaj wszystkie pary punktow wyznaczajace proste i odcinki
	while(cin >> p1.x >> p1.y >> p2.x >> p2.y) {
		b.PB(p1); e.PB(p2);
	}
// Dla kazdej pary punktow wykonaj funkcje LineCrossPoint oraz SegmentCrossPoint
	REP(x, SIZE(b)) REP(y, x) {
/* newpage */
		cout << b[x] << " - " << e[x] << 
			" oraz " << b[y] << " - " << e[y] << endl;
		cout << "Punkt przeciecia prostych: " << 
			(res = LineCrossPoint(b[x], e[x], b[y], e[y], p));
		if (res == 1) cout << " " << p;
		cout << endl;
		cout << "Punkt przeciecia odcinkow: " << 
			SegmentCrossPoint(b[x], e[x], b[y], e[y], l);
		FOREACH(it, l) cout << " " << (*it);
		cout << endl;
	}
	return 0;
}
