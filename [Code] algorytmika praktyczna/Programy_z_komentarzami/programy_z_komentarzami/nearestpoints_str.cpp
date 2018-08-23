#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

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
#include <list>
// Wartosc INF jest wykorzystywana jako reprezentacja nieskonczonosci.
// Ma ona wartosc 1000000001, a nie 2147483647 (najwieksza wartosc typu int)
// ze wzgledu na dwie rzeczy - prosty zapis oraz brak przepelnienia wartosci
// zmiennej w przypadku dodawania dwoch nieskonczonosci do siebie:
// ((int) 2147483647 + (int) 2147483647 = -2).
const int INF = 1000000001;
inline double sqr(double a) {return a*a;}
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
// Operator okreslajacy liniowy porzadek na zbiorze punktow po wspolrzednych (y, x)
bool OrdYX(POINT *a, POINT *b) {
	return a->y==b->y ? a->x<b->x : a->y<b->y;
}
struct NearestPoints { 
	vector<POINT*> l;
// Wskazniki do dwoch punktow, stanowiacych znaleziona pare najblizszych punktow
	POINT *p1, *p2;
// Odleglosc miedzy punktami p1 i p2
	double dist;
// Funkcja usuwa z listy l wszystkie punkty, ktorych odleglosc 
// od prostej x=p jest wieksza od odleglosci miedzy para aktualnie 
// znalezionych najblizszych punktow
	void Filter(vector<POINT*> &l, double p) {
		int s = 0;
		REP(x, SIZE(l))
			if (sqr(l[x]->x - p) <= dist) l[s++] = l[x];
		l.resize(s);
	}
// Funkcja realizuje faze dziel i zwyciezaj dla zbioru punktow z wektora l
// od pozycji p do k. Wektor ys zawiera punkty 
// z przetwarzanego zbioru posortowane w kolejnosci niemalejacych wspolrzednych y
	void Calc(int p, int k, vector<POINT*> &ys) {
// Jesli zbior zawiera wiecej niz jeden punkt, to nastepuje faza podzialu
		if (k - p > 1) {
			vector<POINT*> lp, rp;
// Wyznacz punkt podzialu zbioru
			int c = (k + p - 1) / 2;
// Podziel wektor ys na dwa zawierajace odpowiednio punkty 
// na lewo oraz na prawo od punktu l[c]
			FOREACH(it, ys)
				if (OrdXY(l[c], *it)) rp.PB(*it); else lp.PB(*it);
// Wykonaj faze podzialow
			Calc(p, c + 1, lp);
			Calc(c + 1, k, rp);
// Nastepuje faza scalania. Najpierw z wektorow l i r usuwane 
// sa punkty polozone zbyt daleko od prostej wyznaczajacej podzial zbiorow
			Filter(lp, l[c]->x);
			Filter(rp, l[c]->x);
			int p = 0; double k;
// Nastepuje faza wyznaczania odleglosci miedzy kolejnymi parami punktow, 
// ktore moga polepszyc biezacy wynik
			FOREACH(it, lp) {
			    while (p < SIZE(rp) - 1 && rp[p + 1]->y < (*it)->y) p++;
				FOR(x, max(0, p - 2), min(SIZE(rp) - 1, p + 1))
// Jesli odleglosc miedzy para przetwarzanych punktow jest mniejsza od biezacego wyniku, 
// to zaktualizuj wynik
					if (dist > (k = sqr((*it)->x - rp[x]->x) + 
						sqr((*it)->y - rp[x]->y))) {
						dist = k;
						p1 = *it;
						p2 = rp[x];
					}
			}
		}
	}
// Konstruktor struktury NearestPoints wyznaczajacy pare najblizszych punktow
	NearestPoints(vector<POINT> &p) {
// Wypelnij wektor l wskaznikami do punktow z wektora p 
// oraz posortuj te wskazniki w kolejnosci niemalejacych wspolrzednych x
		FOREACH(it, p) l.PB(&(*it));
		sort(ALL(l), OrdXY);
// Jesli w zbiorze istnieja dwa punkty o tych samych wspolrzednych, 
// to punkty te sa poszukiwanym wynikiem
		FOR(x, 1, SIZE(l) - 1)
		    if (l[x - 1]->x == l[x]->x && l[x - 1]->y == l[x]->y) {
				dist = 0;
				p1 = l[x - 1]; p2 = l[x]; return;
		    }
		dist = double(INF) * double(INF);
// Skonstruuj kopie wektora wskaznikow do punktow i posortuj go w kolejnosci 
// niemalejacych wspolrzednych y
		vector<POINT*> v = l;
		sort(ALL(v), OrdYX);
// Wykonaj faze dziel i zwyciezaj dla wszystkich punktow ze zbioru
		Calc(0, SIZE(l), v);
		dist = sqrt(dist);
	}
};
int main() {
	int n;
	vector<POINT> l;
	POINT p;
// Wczytaj liczbe punktow
	cin >> n;
// Wczytaj kolejne punkty
	REP(x, n) {
		cin >> p.x >> p.y;
		l.PB(p);
	}
// Wyznacz pare najblizszych punktow oraz wypisz wynik
	NearestPoints str(l);
	cout << "Wyznaczona odleglosc: " << str.dist << endl;
	cout << "Znaleziona para najblizszych punktow:" << endl;
	cout << *(str.p1) << " " << *(str.p2) << endl;
	return 0;
}
