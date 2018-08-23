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
// Makro wyznacza wartosc iloczynu wektorowego (a -> b)*(a -> c)
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
// Wskaznik na punkt centralny (uzywane przez funkcje porownujaca)
POINT* RSK; 
// Funkcja porownujaca punkty
bool Rcmp(POINT *a, POINT *b) {
	LL w = Det((*RSK), (*a), (*b));
	if (w == 0) return abs(RSK->x - a->x) + abs(RSK->y - a->y) < 
		abs(RSK->x - b->x) + abs(RSK->y - b->y);
	return w > 0;
}
// Funkcja sortuje po kacie odchylenia zbior punktow wzgledem punktu centralnego 
// s zaczynajac od wektora s -> k
vector<POINT*> AngleSort(vector<POINT>& p, POINT s, POINT k) {
	RSK = &s;
	vector<POINT*> l, r;
// Kazdy punkt, ktory podlega sortowaniu, zostaje wstawiony do jednego 
// z wektorow l lub r, w zaleznosci od tego, 
// czy znajduje sie po lewej czy po prawej stronie prostej s -> k
	FOREACH(it, p) {
		LL d = Det(s, k, (*it));
		(d > 0 || (d==0 && (s.x == it->x ? s.y < it->y : s.x < it->x))) 
			? l.PB(&*it) : r.PB(&*it);
	}
// Posortuj niezaleznie punkty w obu wyznaczonych wektorach
	sort(ALL(l), Rcmp);
	sort(ALL(r), Rcmp);
// Wstaw wszystkie punkty z wektora r na koniec wektora l
	FOREACH(it, r) l.PB(*it);
	return l;
}
int main() {
	POINT c, k;
	int n;
// Wczytaj liczbe punktow oraz wspolrzedne wektora, wzgledem ktorego wykonywane bedzie sortowanie
	cin >> n >> c.x >> c.y >> k.x >> k.y;
	vector<POINT> l(n);
// Wczytaj wszystkie punkty
	REP(x, n) cin >> l[x].x >> l[x].y;
// Posortuj punkty
	vector<POINT*> res = AngleSort(l, c, k);
	FOREACH(it, res) cout << " " << *(*it);
	return 0;
}
