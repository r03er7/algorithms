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
#include <map>
#define MP make_pair
// Funkcja wyszukuje wystapienia wzorca w tekscie i dla kazdego znalezionego wystapienia wywoluje funkcje fun
void KMP(const char* str,const char* wzo, void (*fun)(int)) { 
#define KMPH(z) while(k > 0 && wzo[k] != z[q]) k = p[k]; if(wzo[k] == z[q]) k++;
	int p[strlen(wzo) + 1], k = 0, q, m;
	p[1] = 0;
// Wyznacz tablice prefiksowa dla wyszukiwanego wzorca
	for (q = 1; wzo[q]; q++) {
		KMPH(wzo);
		p[q + 1] = k;
	}
	m = q;
	k = 0;
// Dla kolejnych liter przeszukiwanego tekstu...
	for (q = 0; str[q]; q++) {
// Uzywajac tablicy prefiksowej, wyznacz dlugosc sufiksu tekstu 
// str[0..q], bedacego jednoczesnie prefiksem wzorca
		KMPH(str);
// Jesli wyznaczony prefiks jest rowny dlugosci wzorca, to wywolaj 
// funkcje fun dla znalezionego wystapienia wzorca
		if(m == k) {
			fun(q - m + 1); 
			k = p[k];
		}
	}
}
struct mkmp {
// Struktura reprezentujaca wierzcholek w drzewie wzorcow
    struct leaf {
// Mapa son sluzy do reprezentowania krawedzi wychodzacych z wierzcholka
	map<char, leaf*> son;
// Element lnk wierzcholka v reprezentuje wartosc funkcji prefiksowej wierzcholka, natomiast wo jest wskaznikiem na najdluzszy wzorzec bedacy sufiksem tekstu wierzcholka v
	leaf *lnk, *wo;
// Zmienna reprezentujaca numer wzorca wierzcholka (jesli wierzcholek nie reprezentuje zadnego wzorca, jest to -1)
	int el;
	leaf() : el(-1) {}
    };
// Wektor zawierajacy dlugosci poszczegolnych wzorcow wstawionych do struktury
	VI len;
// Korzeñ drzewa
    leaf root;
// Pomocnicza funkcja przetwarzajaca litere tekstu i dokonujaca odpowiedniego przejscia w drzewie
	leaf* mv(leaf* w, char l) {
// Dopoki wierzcholek w nie ma syna dla litery l przesuwaj sie wzdluz funkcji prefiksowej
		while(w!=&root && w->son.find(l) == w->son.end()) w = w->lnk;
// Jesli wierzcholek w posiada syna dla litery l, to przejdz do tego wierzcholka
		if (w->son.find(l) != w->son.end()) w = w->son[l];
		return w;
	}
// Funkcja wstawia nowy wzorzec do struktury
    int addWord(const char *s) {
		int l = strlen(s);
		leaf *p = &root;
// Przejdz od korzenia drzewa do wierzcholka reprezentujacego caly wzorzec, ewentualnie tworzac jeszcze nieistniejace wierzcholki
		for(;*s;++s) {
			VAR(e, p->son.find(*s));
			p = (e == p->son.end()) ? p->son[*s] = new leaf : e->second;
		}
// Jesli aktualny wierzcholek nie reprezentuje jeszcze zadnego wzorca, to przypisz mu nowy identyfikator i zapamietaj jego dlugosc (wpp. wykorzystywany jest poprzedni identyfikator)
		if (p->el==-1) {
			p->el=SIZE(len);
			len.PB(l);
		}
// Zwroc identyfikator wzorca
		return p->el;
    }
// Funkcja wyznacza funkcje prefiksowa dla wierzcholkow drzewa. Wylicza ona rowniez wartosci pol wo
    void calcLink() {
// Wektor l jest uzywany jako kolejka dla przeszukiwania drzewa metoda BFS
	vector<leaf*> l;
	leaf* w;
	root.lnk = root.wo = 0;
// Wstaw do kolejki wszystkich synow korzenia oraz ustaw ich funkcje prefiksowa na korzeñ
	FOREACH(it, root.son) {
	    l.PB(it->ND);
	    it->ND->lnk = &root;
	}
// Dla wszystkich elementow z kolejki...
	REP(x, SIZE(l)) {
// Wyliczenie pola wo - jego wartosc to wierzcholek wskazywany przez funkcje prefiksowa (jesli reprezentuje on wzorzec), lub w przeciwnym przypadku wartosc pola wo tego wierzcholka
	    l[x]->wo = (l[x]->lnk->el != -1) ? l[x]->lnk : l[x]->lnk->wo;
// Dla kazdego syna aktualnego wierzcholka (litere prowadzaca do syna reprezentuje it->ST)...
	    FOREACH(it, l[x]->son) {
// Wstaw go do kolejki
		l.PB(it->ND);
// Wyznaczanie wartosc funkcji prefiksowej
		w = l[x]->lnk;
// Dokonaj przejscia z wierzcholka w
		w = mv(w, it->ST);
// Ustaw wierzcholek w jako wartosc funkcji prefiksowej
		it->ND->lnk=w;
	    }
	}
    }
// Funkcja wyszukuje wszystkie wystapienia wzorcow w zadanym tekscie i dla kazdego znalezionego wystapienia wywoluje funkcje fun
    void searchAll(const char* s, void (*fun)(int, int)) {
	leaf *p = &root;
// Dla kazdej kolejnej litery przeszukiwanego tekstu...
	for(int x=0;s[x];++x) {
// Dokonaj przejscia dla litery s[x]
		p = mv(p, s[x]);
// Jesli aktualny wierzcholek (lub pewne jego sufiksy) reprezentuja wzorzec, to wywolaj dla nich funkcje fun
	    for(VAR(r,p); r; r=r->wo) if (r->el != -1) fun(x-len[r->el]+1, r->el);
	}
    }
// Funkcja wyszukuje pierwsze wystapienia kazdego ze wzorcow w zadanym tekscie i dla kazdego znalezionego wystapienia wywoluje funkcje fun
    void searchFirst(const char* s, void (*fun)(int, int)) {
	leaf *p = &root, *r, *t;
// Dla kazdej kolejnej litery przeszukiwanego tekstu...
	for(int x=0;s[x];++x) {
// Dokonaj przejscia dla litery s[x]
		p=mv(p,s[x]);
// Wywolaj funkcje fun dla wszystkich znalezionych wzorcow oraz usuñ informacje o tych wzorcach, aby nie zostaly znalezione ponownie
	    r = p;
	    while(r) {
// Jesli wierzcholek reprezentuje wzorzec, to wywolaj funkcje fun
		if (r->el != -1) fun(x-len[r->el]+1, r->el);
// Usuñ identyfikator wzorca, aby nie zostal on znaleziony po raz kolejny
		r->el = -1;
// Przejdz do kolejnego wzorca i wyzeruj wskaznik wo (aby nie wykonywac tego ruchu w przyszlosci)
		t = r;
		r = r->wo;
		t->wo = 0;
	    }
	}
    }
};
const int MAX = 1001;
char text[MAX][MAX];
char text2[MAX][MAX];
char pattern[MAX];
char pattern2[MAX];
int nr, res = 0;

// Funkcja zaznacza wyszukane wzorce w tekscie podczas pierwszej fazy wyszukiwania
void Found1(int x, int p) {
	text2[x][nr] = (char)(p+2);
}

// Funkcja zlicza liczbe znalezionych wzorcow w tekscie podczas drugiej fazy wyszukiwania
void Found2(int v) {
	res++;
}

int main() {
	int cx, cy, mx, my, val;
// Wczytaj wymiary calego labiryntu oraz zwiedzonego obszaru
	cin >> cx >> cy >> mx >> my;
	mkmp find1;
// Wczytaj opis labiryntu
	REP(y, cy) {
		REP(x, cx) {
			cin >> val;
			text[y][x] = (char) val;
			text2[x][y] = (char) 1;
		}
		text[y][cx] = 0;
	}
// Wczytaj opis zwiedzonego obszaru
	REP(y, my) {
		REP(x, mx) {
			cin >> val;
			pattern[x] = val;
		}
		pattern[mx] = 0;
// Kazdy wiersz opisu zwiedzonego obszaru wstaw do struktury Multi-KMP
		pattern2[y] = (char) (find1.addWord(pattern)+2);
	}
	pattern2[my] = 0;
// Przygotuj strukture Multi-KMP do wyszukiwania
	find1.calcLink();
// Dla kazdego wiersza opisu labiryntu, znajdz wystapienia wierszy opisu zwiedzonego obszaru
	REP(x, cy) {
		nr = x;
		find1.searchAll(text[x], Found1);
	}
// Dokonaj wyszukiwania wzorca jednowymiarowego, reprezentujacego zwiedzony obszar (redukcja z 2 do 1-wymiarowego problemu zostala dokonana w poprzedniej fazie)
	REP(x, cx-mx+1) {
		text2[x][cy]=0;
		KMP(text2[x], pattern2, Found2);
	}
// Wypisz wynik
	cout << res;
	return 0;
}
