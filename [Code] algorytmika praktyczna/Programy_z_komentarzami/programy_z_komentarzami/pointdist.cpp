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
// Funkcja wyznacza odleglosc punktu p od prostej (p1 -> p2)
double PointLineDist(POINTD p1, POINTD p2, POINTD p) {
    double A=p2.y-p1.y, B=p2.x-p1.x;
    return abs(A*(p1.x-p.x)+B*(p.y-p1.y))/sqrt(A*A+B*B);
}
int main() { 
	POINT l1, l2, p;
// Wczytaj pozycje punktow wyznaczajacych prosta
	cin >> l1.x >> l1.y >> l2.x >> l2.y;
// Dla wszystkich punktow wyznacz odleglosc od prostej
	while(cin >> p.x >> p.y)
		cout << "Odleglosc punktu " << p << " od prostej (" << 
		l1 << "," << l2 << ") wynosi " << PointLineDist(l1, l2, p) << endl;
	return 0;
}
