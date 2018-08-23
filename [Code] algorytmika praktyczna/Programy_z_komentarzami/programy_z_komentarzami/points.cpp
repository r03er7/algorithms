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
inline double sqr(double a) {return a*a;}
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
// Struktura liczb 128 bitowych (potrzebna do porownywania wspolrzednych punktow)
typedef unsigned long long int ulli;
const ulli low_part  = 2147483647;
const ulli high_part = low_part * (low_part + 2);
struct superlong {
	ulli high, low;
	bool operator==(const superlong& a) {
		return a.high == high && a.low == low;
	}
	bool operator<(const superlong& a) {
		return high < a.high || (high == a.high && low < a.low);
	}
};

// Funkcja mnozy dwie liczby 64-bitowe i zwraca jako wynik liczbe 128-bitowa typu superlong
inline superlong multiply(ulli v1, ulli v2)
{
	superlong val;
	ulli x = (v1 & low_part) * (v2 >> 31) + (v1 >> 31) * (v2 & low_part);
	val.low = (v1 & low_part) * (v2 & low_part);
	val.high = (v1 >> 31) * (v2 >> 31);
	val.low  += (x & low_part) << 31;
	val.high += (x >> 31) + (val.low >> 62);
	val.low  = val.low & high_part;
	return val;
}

// Struktura reprezentuje zbior punktow
struct pSet {
// Zmienna okresla, czy zbior zawiera punkt bedacy jego srodkiem ciezkosci
	bool cen;
// Wielkosc zbioru rozumiana jako kwadrat odleglosci najdalszego punktu w zbiorze od punktu (0,0)
	LL size;
// Wektory kwadratow odleglosci kolejnych punktow w zbiorze od punktu (0,0) oraz od kolejnego punktu w kolejnosci katowej
	vector<LL> cdist, dist;
};

LL sqr(int x) {
	return LL(x)*LL(x);
}

// Funkcja wczytuje opis zbioru punktow i generuje dla niego odpowiednia reprezentacje w postaci 'obwodki' cyklicznej
pSet ReadSet() {
	int s;
	pSet res;
// Wczytaj liczbe punktow w zbiorze
	cin >> s;
	vector<POINT> pl(s);
	int wx = 0, wy = 0;
// Wczytaj wspolrzedne wszystkich punktow oraz wyznacz sume wspolrzednych x oraz y
	REP(x,s) {
		cin >> pl[x].x >> pl[x].y;
		wx += pl[x].x;
		wy += pl[x].y;
	}
// Przeskaluj wspolrzedne wszystkich punktow oraz przesuñ srodek ciezkosci zbioru do punktu (0,0)
	REP(x,s) {
		pl[x].x = pl[x].x*s - wx;
		pl[x].y = pl[x].y*s - wy;
	}
// Wyeliminuj (o ile istnieje) punkt bedacy srodkiem ciezkosci zbioru
	res.cen = false;
	REP(x,s) if (!pl[x].x && !pl[x].y) {
		res.cen = true;
		swap(pl[x], pl.back());
		pl.pop_back();
		s--;
		break;
	}
// Posortuj punkty katowo oraz wygeneruj koñcowa reprezentacje
	vector<POINT*> sorted = AngleSort(pl, POINT(0,0), POINT(1,0));
	res.cdist.resize(s);
	res.dist.resize(s);
	res.size = 0;
	REP(x, s) {
		res.cdist[x] = sqr(sorted[x]->x) + sqr(sorted[x]->y);
		res.dist[x] = sqr(sorted[x]->x - sorted[(x+1)%s]->x) + sqr(sorted[x]->y - sorted[(x+1)%s]->y);
		res.size >?= res.cdist[x];
	}
	return res;
}

// Funkcja porownuje punkty ze zbiorow l i r na pozycjach odpowiednio pl i pr
int CmpEl(pSet& l, int pl, pSet& r, int pr) {
	superlong v1 = multiply(l.cdist[pl], r.size);
	superlong v2 = multiply(r.cdist[pr], l.size);
// Jesli odleglosci od srodka ciezkosci sa takie same...
	if (v1 == v2) {
		v1 = multiply(l.dist[pl], r.size);
		v2 = multiply(r.dist[pr], l.size);
// Jesli odleglosci od poprzedniego punktu sa takie same to porownywane punkty sa rowne
		if (v1 == v2) return 0;
	}
	return v1 < v2 ? -1 : 1;
}

// Funkcja porownuje dwa zbiory punktow
bool equal(pSet& l, pSet& r) {
// Wstepny test podobieñstwa zbiorow
	if (SIZE(l.dist) != SIZE(r.dist) || l.cen != r.cen) return false;
// Modyfikacja funkcji cycEq sluzacej do sprawdzania rownowaznosci cyklicznej dwoch tekstow
	int n = SIZE(l.dist), i = 0, j = 0, k = 1;
	while(i < n && j < n && k < n) {
		k = 1;
		while(k <= n && CmpEl(l, (i+k)%n, r, (j+k)%n) == 0) k++;
		if (k<=n) if (CmpEl(l, (i+k)%n, r, (j+k)%n) == -1) i+=k;
		else j+=k;
	}
	return k > n;
}

int main() {
	int n;
// Wczytaj opis wzoru
	pSet p1 = ReadSet();
// Wczytaj liczbe innych zbiorow
	cin >> n;
// Dla kazdego zbioru...
	while(n--) {
// Wczytaj jego opis
		pSet p2 = ReadSet();
// Jesli zbiory nie sa podobne to nalezy odwrocic jeden ze zbiorow (co symuluje symetrie osiowa)
		if (!equal(p1, p2) && SIZE(p1.cdist) > 1) {
			reverse(ALL(p2.cdist));
			reverse(p2.dist.begin(), p2.dist.end()-1);
		}
// Wypisz wynik
		cout << (equal(p1, p2) ? "TAK" : "NIE") << endl;
	}
	return 0;
}
