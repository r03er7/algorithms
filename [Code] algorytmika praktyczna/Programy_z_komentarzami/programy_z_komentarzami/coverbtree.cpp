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
// Struktura umozliwia dodawanie i usuwanie odcinkow oraz wyznaczanie obszaru przez nie pokrytego
struct CoverBTree {
// Struktura wierzcholka drzewa
	struct Vert {
// Wskazniki na odpowiednio lewego i prawego syna
		Vert *s[2];
// Zmienna v reprezentuje pokryty obszar aktualnego wierzcholka, natomiast c zlicza liczbe odcinkow, ktore pokrywaja w calosci przedzial reprezentowany przez wierzcholek
		int v,c;
		Vert(){s[v=c=0]=s[1]=0;}
	};
// Korze� drzewa
	Vert *root;
// Wartosc reprezentujaca poczatek i koniec przedzialu, dla ktorego zostalo skonstruowane drzewo
	int zp, zk;
// Funkcja usuwa pamiec zaalokowana dla danego wierzcholka oraz jego poddrzewa
	void Rem(Vert* p){ if (p) {Rem(p->s[0]); Rem(p->s[1]); delete p;}}
// Destruktor zwalnia cala pamiec przydzielona na drzewo
	~CoverBTree() {Rem(root);}
// Konstruktor tworzy nowe drzewo dla przedzialu [p..k]
	CoverBTree(int p,int k) : zp(p), zk(k) {root=new Vert;}
// Zmienne pomocnicze dla operatorow (przypisywane sa im odpowiednio poczatek i koniec odcinka oraz licznik okreslajacy ile kopii odcinka jest dodawanych / usuwanych)
	int pp,kk,cc;
// Funkcja pomocnicza dla Add, dodajaca lub usuwajaca odcinek [pp..kk]. Parametry p i k oznaczaja przedzial, ktory reprezentuje wierzcholek v
	void Ad(int p, int k, Vert* v) {
		if(kk<=p || pp>=k) return;
// Jesli odcinek w calosci pokrywa aktualny przedzial, to nastepuje modyfikacja zmiennej c aktualnego wierzcholka
		if (p>=pp && k<=kk) v->c+=cc;
		else
		{
			int c=(p+k)/2;
// Jesli odcinek zachodzi na przedzial lewego syna, to aktualizuj go
			if (pp<=c) {
				if (!v->s[0]) v->s[0]=new Vert;
				Ad(p,c,v->s[0]);
			}
// Jesli odcinek zachodzi na przedzial prawego syna, to aktualizuj go
			if (kk>=c) {
				if (!v->s[1]) v->s[1]=new Vert;
				Ad(c,k,v->s[1]);
			}
		}
// Aktualizacja pokrycia przedzialu. Jesli zmienna c jest dodatnia, to odcinek jest pokryty w calosci, a jesli nie, to wielkosc jego pokrycia jest zalezna od jego synow
		v->v = v->c ? k-p : 
			(v->s[0] ? v->s[0]->v : 0) + (v->s[1] ? v->s[1]->v : 0);
	}
// Funkcja dodaje lub usuwa z drzewa odcinek [p..k]. Parametr c okresla, czy odcinek jest dodawany (1), czy usuwany (-1)
	void Add(int p, int k, int c) {
		pp=p; kk=k; cc=c;
		Ad(zp,zk,root);
	}
// Funkcja pomocnicza, wyznaczajaca wielkosc pokrycia przedzialu [pp..kk]
	int Fi(int p, int k, Vert* v) {
// Jesli wierzcholek nie istnieje lub jego przedzial jest rozlaczny z odcinkiem to wyjdz
		if (!v || p>=kk || k<=pp) return 0;
// Jesli przedzial jest pokryty w calosci, to zwroc wielkosc przeciecia z odcinkiem
		if (v->c) return min(k,kk)-max(p,pp);
// Jesli odcinek zawiera caly przedzial, to zwroc pokrycie przedzialu
		if (p>=pp && k<=kk) return v->v;
// Wyznacz pokrycie dla obu synow
		int c=(p+k)/2;
		return Fi(p,c,v->s[0])+Fi(c,k,v->s[1]);
	}
// Funkcja wyznaczajaca pokrycie przedzialu [p..k]
	int Find(int p, int k) {
		pp=p; kk=k;
		return Fi(zp,zk,root);
	}
};
int main() { 
	int w1, w2, w3;
// Skonstruuj dynamiczne drzewo pokryciowe dla przedzialu [0..10^9]
	CoverBTree tree(0, 1000000000);
// Wczytaj polecenia i wykonaj je...
	while(cin >> w1 >> w2 >> w3) {
		if (w1 == 0) {
// Operacja dodawania nowego odcinka
			tree.Add(w2, w3, 1);
			cout << "Dodanie odcinka [" << w2 << "," << w3 << "]" << endl;
		} else if (w1 == 1) {
// Operacja usuwania odcinka
			tree.Add(w2, w3, -1);
			cout << "Usuniecie odcinka [" << w2 << "," << w3 << "]" << endl;
		} else
// Wyznaczanie pokrycia na przedziale [w2..w3]
			cout << "Pokrycie odcinka [" << w2 << "," << w3 << 
				"] = " << tree.Find(w2, w3) << endl;
	}
	return 0;
}
