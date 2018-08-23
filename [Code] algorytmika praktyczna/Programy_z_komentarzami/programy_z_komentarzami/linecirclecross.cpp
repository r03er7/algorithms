#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

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
// Funkcja wyznacza punkty przeciecia okregu i prostej
vector<POINTD> LineCircleCross(POINTD p, double cr, POINTD p1, POINTD p2){ 
	double a = sqr(p1.x) + sqr(p1.y) + sqr(p2.x) + sqr(p2.y) - 
		2.0 * (p1.x * p2.x + p1.y * p2.y);
	double b = 2.0 * (p.x * (p2.x - p1.x) + p.y * (p2.y - p1.y) +
		p1.x * p2.x + p1.y * p2.y - sqr(p2.x)-sqr(p2.y));
	double c = -sqr(cr) + sqr(p2.x) + sqr(p2.y) + sqr(p.x) +
		sqr(p.y) - 2.0 * (p.x * p2.x + p.y * p2.y);
	double d = b * b - 4.0 * a * c;
	vector<POINTD> r;
// Jesli nie istnieje rozwiazanie rownania kwadratowego, 
// to brak punktow przeciecia
	if (d < -EPS) return r;
	double t = -b / (2.0 * a), e = sqrt(abs(d)) / (2.0 * a);
	if (IsZero(d))
// Istnieje tylko jeden punkt przeciecia...
		r.PB(POINTD(t * p1.x + (1.0 - t) * p2.x, t * p1.y + (1.0 - t) * p2.y));
  else {
// Istnieja dwa punkty przeciecia
		r.PB(POINTD((t + e) * p1.x + (1.0 - t - e) * p2.x, 
			(t + e) * p1.y + (1.0 - t - e) * p2.y));
		r.PB(POINTD((t - e) * p1.x + (1.0 - t + e) * p2.x, 
			(t - e) * p1.y + (1.0 - t + e) * p2.y));
	}
	return r;
}
vector<POINTD> CirclesCross(POINTD c1, double c1r, POINTD c2, double c2r){
  vector<POINTD> r;
  c2.x -= c1.x; c2.y-= c1.y;
// Jesli okregi sa wspolsrodkowe, to nie wyznaczamy punktow przeciecia
  if (IsZero(c2.x) && IsZero(c2.y)) return r;
  double A = (-sqr(c2r)+sqr(c1r)+sqr(c2.x)+sqr(c2.y))/2.0;
// Jesli srodki okregow maja ta sama wspolrzedna y...
  if (IsZero(c2.y)){
    double x = A/c2.x; double y2=sqr(c1r)-sqr(x);
    if (y2 <-EPS) return r;
// Jesli okregi sa styczne...
    if(IsZero(y2)) r.PB(POINTD(c1.x+x,c1.y));
    else{
// Okregi przecinaja sie
      r.PB(POINTD(c1.x+x,c1.y+sqrt(y2)));
      r.PB(POINTD(c1.x+x,c1.y-sqrt(y2)));
    }
    return r;
  }
  double a = sqr(c2.x) + sqr(c2.y);
  double b = -2.0 *A * c2.x;
  double c = A*A - sqr(c1r)*sqr(c2.y);
  double d = b*b-4.0*a*c;
  if (d<-EPS) return r;
  double x = -b/(2.0*a);
// Jesli okregi sa styczne...
  if (IsZero(d)) r.PB(POINTD(c1.x + x, c1.y+(A - c2.x*x)/c2.y));
  else{
// Okregi przecinaja sie
    double e = sqrt(d)/(2.0*a);
    r.PB(POINTD(c1.x+x+e, c1.y+(A-c2.x*(x+e))/c2.y));
    r.PB(POINTD(c1.x+x-e, c1.y+(A-c2.x*(x-e))/c2.y));
  }
  return r;
}
int main() { 
	vector<POINT> cCen;
	VI cR;
	vector<POINTD> res;
	POINT l1, l2, p; int r;
/* newpage */
// Wczytaj wspolrzedne punktow wyznaczajacych prosta
	cin >> l1.x >> l1.y >> l2.x >> l2.y;
// Wczytaj opisy kolejnych okregow
	while(cin >> p.x >> p.y >> r) {
		cR.PB(r); cCen.PB(p);
	}
// Wyznacz punkty przeciecia prostej i okregu
	cout << "Przeciecie prostej " << l1 << " - " << l2 << 
		" i okregu:" << endl;
	REP(x, SIZE(cCen)) {
		res = LineCircleCross(cCen[x], cR[x], l1, l2);
		cout << "\t(" << cCen[x].x << ", " << cCen[x].y << 
			", " << cR[x] << ") - ";
		if (!SIZE(res)) cout << "brak punktow przeciecia";
		FOREACH(it, res) cout << " " << (*it);
		cout << endl;
	}
// Wyznacz punkty przeciecia dwoch okregow
	cout << "Przeciecie okregow:" << endl;
	REP(x, SIZE(cCen)) REP(y, x) {
		res = CirclesCross(cCen[x], cR[x], cCen[y], cR[y]);
		cout << "\t(" << cCen[x].x << ", " << cCen[x].y << ", " << cR[x] << 
			") oraz (" << 
			cCen[y].x << ", " << cCen[y].y << ", " << cR[y] << ") - ";
		if (!SIZE(res)) cout << "brak punktow przeciecia";
		FOREACH(it, res) cout << " " << *(it);
		cout << endl;
	}
	return 0;
}
