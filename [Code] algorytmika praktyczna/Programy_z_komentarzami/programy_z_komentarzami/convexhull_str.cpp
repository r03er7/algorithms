#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach
// - ich skrocenie jest bardzo istotne
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
// zmiennej n. Jest ono czesto wykorzystywane podczas operowania na
// iteratorach struktur danych z biblioteki STL, ktorych nazwy typow sa bardzo dlugie
#define VAR(v, n) __typeof(n) v = (n)
// ALL(c) reprezentuje pare iteratorow wskazujacych odpowiednio na pierwszy
// i za ostatni element w strukturach danych STL. Makro to jest bardzo
// przydatne chociazby w przypadku korzystania z funkcji sort, ktora jako
// parametry przyjmuje pare iteratorow reprezentujacych przedzial
// elementow do posortowania
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL.
// Uzywa sie go w programach, zamiast pisac po prostu x.size() ze wzgledu na to,
// iz wyrazenie x.size() jest typu unsigned int i w przypadku porownywania
// z typem int w procesie kompilacji generowane jest ostrzezenie
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
// Struktura reprezentujaca punkt o wspolrzednych calkowitoliczbowych
struct POINT {
    int x,y;
// Konstruktor punktu pozwalajacy na skrocenie zapisu wielu funkcji
// wykorzystujacych punkty - w szczegolnosci operacje wstawiania punktow do
// struktur danych
    POINT(int x = 0, int y = 0) : x(x), y(y) {}
// Operator sprawdzajacy, czy dwa punkty sa sobie rowne
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
#define Det(a, b, c) (LL(b.x - a.x) * LL(c.y - a.y) - LL(b.y - a.y) * (c.x - a.x))
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
// Wyznacz dolna czesc otoczki wypuklej - laczaca najbardziej lewy-dolny 
// punkt z najbardziej prawym-gornym punktem
	REP(x, SIZE(s)) XCAL
	m = SIZE(w);
// Wyznacz gorna czesc otoczki
	FORD(x, SIZE(s) - 2, 0) XCAL
// Usun ostatni punkt (zostal on wstawiony do otoczki dwa razy)
	w.pop_back();
	return w;
}
int main() {
	int n;
	vector<POINT> l;
	POINT p;
// Wczytaj liczbe punktow
	cin >> n;
// Wczytaj wszystkie punkty
	REP(x, n) {
		cin >> p.x >> p.y;
		l.PB(p);
	}
// Wyznacz wypukla otoczke
	vector<POINT*> res = ConvexHull(l);
	FOREACH(it, res)
		cout << " " << (**it);
	return 0;
}
