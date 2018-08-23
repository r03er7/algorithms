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
// Implementacja struktury BST
template <typename _T> struct BST {
// Struktura wezla drzewa
    struct Ve {
// Wskazniki na lewego i prawego syna
		Ve *s[2];
// Pole e zawiera element przechowywany w wezle
		_T e; 
		Ve(){s[0]=s[1]=0;}};
// sygnatury funkcji do porownywania elementow oraz do aktualizacji ich zawartosci
#define _Less int (*Less)(const _T&, const _T&)
#define _Upd void (*Upd)(_T*, _T*, _T*)
    _Less;
    _Upd;
// Korzeñ drzewa oraz dodatkowa zmienna pomocnicza
    Ve* root,*v;
// Wektor wskaznikow do wezlow drzewa, wykorzystywany do wyznaczania sciezki od przetwarzanego wezla do korzenia drzewa
    vector<Ve*> uV;
// Funkcja usuwa dany wezel wraz z jego calym poddrzewem
    void Rem(Ve* p)	{
	if (p) {
	    REP(x,2) Rem(p->s[x]);
	    delete p;
	}
    }
// Destruktor drzewa zwalnia zaalokowana pamiec
    ~BST(){Rem(root);}
// Konstruktor drzewa przyjmuje jako parametry dwie funkcje - funkcje okreslajaca porzadek na elementach oraz funkcje sluzaca do aktualizowania informacji elementow
    BST(_Less, _Upd) : Less(Less), Upd(Upd) {root=0;}
// Funkcja aktualizuje wartosci elementow, znajdujacych sie na sciezce od ostatnio przetwarzanego wezla do korzenia drzewa
	void Update() {
	for(int x=SIZE(uV)-1;x>=0 && (v=uV[x]);x--)
	    Upd(&v->e, v->s[0] ? &(v->s[0]->e) : 0, v->s[1] ? &(v->s[1]->e) : 0);
        uV.clear();
    }
// Funkcja pomocnicza wyszukujaca wezel w drzewie zawierajacy zadany element
    Ve* Find(const _T& e, bool s) {
	v=root;
	if (s) uV.PB(v);
	for(int c;v && (-1 != (c=Less(v->e,e)));) { 
	    if(s) uV.PB(v);
	    v=v->s[c];
	}
	return v;
    }
// Funkcja wyszukuje zadany element w drzewie
    _T* Find(const _T& e) {return (v = Find(e,0)) ? &(v->e) : 0;}
// Funkcja wstawia zadany element do drzewa
    void Insert(const _T& e) {
// Jesli drzewo nie jest puste...
	if (root) {
// Znajdz odpowiednie miejsce w drzewie dla dodawanego elementu i go dodaj
	    Find(e,1); v=uV.back();
	    int cmp=Less(v->e,e);
	    if (cmp!=-1)
		uV.PB(v=v->s[cmp]=new Ve);
        }
// Stworz nowy korzeñ drzewa z zadanym elementem
	else uV.PB(v=root=new Ve);
        v->e=e;
// Zaktualizuj elementy na sciezce od dodanego elementu do korzenia
        Update();
    }
// Funkcja usuwa z drzewa wezel zawierajacy zadany element
    bool Delete(const _T& e) {
	Ve* c=Find(e,1),*k;
// Jesli elementu nie ma w drzewie, to przerwij
    	if (!c) {uV.resize(0); return 0;}
	if (c!=root) uV.PB(c);
// Jesli wezel ma obu synow, to musi nastapic zamiana elementow w wezle aktualnym z kolejnym elementem...
	if (c->s[0] && c->s[1]) {
	    for(k=c->s[1]; k->s[0]; k=k->s[0]) uV.PB(k);
	    uV.PB(k);
	    c->e=k->e;
	    c=k;
	}
// Usuniecie odpowiednich wezlow z drzewa
	if(SIZE(uV)>1)
	    (k=uV[SIZE(uV)-2])->s[k->s[0] != c] = c->s[0] ? c->s[0] : c->s[1];
	else root=c->s[0] ? c->s[0] : c->s[1];
// Aktualizacja elementow na sciezce
	Update();
	delete c;
	return 1;
    }
};
// Element stanowiacy zawartosc wierzcholkow drzewa 
struct Element {
	int val, stat;
};
// Funkcja okreslajaca porzadek na wierzcholkach drzewa 
// w kolejnosci rosnacych wartosci val
int Cmp(const Element &a, const Element &b) {
	return (a.val == b.val) ? -1 : a.val < b.val;
}
// Funkcja aktualizujaca wartosc stat wierzcholka
void Update(Element *p, Element *ls, Element *rs){
	p->stat = 1 + (ls ? ls->stat : 0);
}
// Funkcja zwraca wskaznik do elementu drzewa, 
// stanowiacego k-ta statystyke pozycyjna
Element* Stat(BST<Element> &t, int k) {
	VAR(v, t.root);
	while(v && k != v->e.stat) {
		if (v->s[0] && v->s[0]->e.stat >= k) v = v->s[0];
		else {
			if (v->s[0]) k -= v->s[0]->e.stat; 
			k--;
			v = v->s[1];
		}
	}
	return v ? &(v->e) : 0;
}

int main() {
// Skonstruuj drzewo binarne wzbogacajac je obiektami typu Element 
// oraz wykorzystujac funkcje Cmp i Update
	BST<Element> Tree(Cmp,Update);
	Element e, *p;
	int cmd;
// Wczytaj operacje do wykonania i je wykonaj
	while(cin >> cmd >> e.val) {
		if (cmd == 0) {
			Tree.Insert(e);
			cout << "Dodawanie do drzewa elementu " << e.val << endl;
		} else if(cmd == 1) {
			cout << "Usuwanie z drzewa elementu " << e.val << endl;
			Tree.Delete(e);
		} else {
			p = Stat(Tree, e.val);	
			if (!p) 
				cout << "W drzewie nie ma wezla bedacego " << e.val << 
					" statystyka pozycyjna" << endl;
			else cout << e.val << " statystyka pozycyjna to: " << p->val << endl;
		}
	}
	return 0;
}
