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
// Implementacja struktury RBST 
template <typename _T> struct RBST {
// Struktura wezla drzewa
	struct Ve {
// Wskazniki na lewego i prawego syna
		Ve *s[2]; 
// Pole e zawiera element przechowywany w wezle
		_T e; 
// Zmienna wykorzystywana do realizacji rotacji na drzewie
		int w; 
		Ve(){s[0] = s[1] = 0;}
	};
// Sygnatury funkcji do porownywania elementow oraz do aktualizacji ich zawartosci
#define _Less int (*Less)(const _T&, const _T&)
#define _Upd void (*Upd)(_T*, _T*, _T*)
	_Less;
	_Upd;
// Korzeñ drzewa oraz dodatkowa zmienna pomocnicza
	Ve *root, *v;
// Wektor wskaznikow do wezlow drzewa wykorzystywany do wyznaczania sciezki 
// od przetwarzanego wezla do korzenia drzewa
	vector<Ve*> uV;
// Funkcja usuwa dany wezel wraz z jego calym poddrzewem
	void Rem(Ve* p) {
		if (p) {
			REP(x,2) Rem(p->s[x]);
			delete p;
		}
	}
// Destruktor drzewa zwalnia zaalokowana pamiec
	~RBST() { 
		Rem(root);
	}
// Konstruktor drzewa przyjmuje jako parametry dwie funkcje - okreslajaca porzadek 
// na elementach oraz sluzaca do aktualizowania informacji elementow
	RBST(_Less, _Upd) : Less(Less), Upd(Upd) {
		root = 0;
	}
// Funkcja aktualizuje wartosci elementow znajdujacych sie na sciezce od ostatnio 
// przetwarzanego wezla do korzenia drzewa
	void Update(vector<Ve*> &uV) {
		for(int x = SIZE(uV) - 1; x >= 0 && (v = uV[x]); x--) {
			v->w = 1 + (v->s[0] ? v->s[0]->w : 0) + (v->s[1] ? v->s[1]->w : 0);
			Upd(&v->e, v->s[0] ? &(v->s[0]->e) : 0, 
				v->s[1] ? &(v->s[1]->e) : 0);
		}
		uV.clear();
	}
// Funkcja pomocnicza wyszukujaca wezel w drzewie zawierajacy zadany element
	Ve* Find(const _T& e, bool s) {
		v = root;
		if (s) uV.PB(v);
		for(int c; v && (-1 != (c = Less(v->e, e)));) {
			v = v->s[c];
			if (s) uV.PB(v);
		}
		return v;
	}
// Funkcja wyszukuje zadany element w drzewie
	_T* Find(const _T& e) {
		return (v = Find(e,0)) ? &(v->e) : 0;
	}
// Poniewaz operacja wykonywania rotacji na drzewie wymaga przechowywania 
// w wezlach informacji na temat wielkosci poddrzew, zatem informacje ta mozna 
// wykorzystac do wyznaczania statystyk pozycyjnych
	_T* StatPos(int nr) {
		Ve* v = root;
		if (!v || v->w < nr) return 0;
		while (v && nr>0) {
			if (v->s[0] && v->s[0]->w >= nr)
				v = v->s[0];
			else {
				if (v->s[0]) nr -= v->s[0]->w;
				if (--nr) v = v->s[1];
			}
		}
		if (!v) return 0;
		return &(v->e);
	}
// Funkcja pomocnicza wykonujaca rotacje na drzewie w celu jego rownowazenia
	Ve* AtRoot(Ve* p, const _T& e) {
		Ve* d = new Ve, *a, *t, *r=0;
		vector<Ve*> Up[2];
		d->e = e;
		int z = Less(p->e, e);
		a = (t = p)->s[z];
		p->s[z] = 0;
		d->s[1 - z] = t;
		d->s[z] = a;
		Up[1 - z].PB((r = d)->s[1 - z]);
		while(a) {
			if (Less(e, a->e) == z) {
				Up[z].PB(r=a);
				a = a->s[1-z];
			} else {
				r->s[r->s[0] != a] = 0;
				t->s[(t == d) ^ z] = a;
				t = r;
				z = 1 - z;
			}
		}
		REP(x, 2) Update(Up[x]);
		uV.PB(d);
		return d;
	}
// Funkcja wstawia zadany element do drzewa
	void Insert(const _T& e) {
		if (!root) {
			uV.PB(root = new Ve);
			root->e = e;
		} else if (v = Find(e, 1))
			v->e = e;
		else {
			uV.clear();
			v = root;
			int cmp = 0;
			while(v && rand() % (v->w + 1)) {
				uV.PB(v);
				v = v->s[cmp = Less(v->e, e)];
			}
			if (!v) {
				uV.PB(v = uV.back()->s[cmp] = new Ve);
				v->e = e;
			} else
				SIZE(uV) ? uV.back()->s[cmp] = AtRoot(v, e) : root = AtRoot(v, e);
		}
		Update(uV);
	}
// Funkcja usuwa okreslony element z drzewa
	bool Delete(const _T& e) {
		Ve* c = Find(e, 1), *k;
		if (!c) {
			uV.clear();
			return 0;
		}
		if (c->s[0] && c->s[1]) {
			for(k = c->s[1]; k->s[0]; k = k->s[0]) uV.PB(k);
			uV.PB(k);
			c->e = k->e;
			c = k;
		}
		if (SIZE(uV)>=2)
			(k = uV[SIZE(uV) - 2])->s[k->s[0] != c] = c->s[0] ? c->s[0] : c->s[1];
		else 
			root = c->s[0] ? c->s[0] : c->s[1];
		Update(uV);
		delete c;
		return 1;
	}
};
// Element stanowiacy zawartosc wierzcholkow drzewa
struct Element { 
// Lewy i prawy koniec odcinka oraz maksimum z koñcow odcinkow z poddrzewa
	int l, r, mr;
};
// Funkcja okreslajaca porzadek liniowy na elementach
int Cmp(const Element &a, const Element &b) {
	if (a.l == b.l && a.r == b.r) return -1;
	return (a.l == b.l) ? a.r < b.r : a.l < b.l;
}
// Funkcja aktualizujaca wartosc mr elementow
void Update(Element *p, Element *ls, Element *rs){
	p->mr = p->r;
	if (ls) p->mr = max(p->mr, ls->mr);
	if (rs) p->mr = max(p->mr, rs->mr);
}

// Funkcja znajduje odcinek zawierajacy punkt o wspolrzednej k
Element* Find(RBST<Element> &t, int k) {
	VAR(v, t.root);
	while(v) {
		if (v->e.l <= k && v->e.r >= k) return &(v->e);
		v = (v->s[0] && v->s[0]->e.mr >= k) ? v->s[0] : v->s[1];
	}
	return 0;
}

int main() {
// Skonstruuj randomizowane drzewo binarne wzbogacone obiektami typu Element
// oraz wykorzystujac funkcje Cmp i Update
	RBST<Element> Tree(Cmp, Update);
	Element e, *p;
	int cmd;
// Wczytaj operacje do wykonania i je wykonaj
	while(cin >> cmd >> e.l) {
		if (cmd == 0) {
			cin >> e.r;
			Tree.Insert(e);
			cout << "Dodawanie do drzewa odcinka (" 
				<< e.l << "," << e.r << ")" << endl;
		} else if(cmd == 1) {
			cin >> e.r;
			cout << "Usuniecie z drzewa odcinka (" 
				<< e.l << "," << e.r << ")" << endl;
			Tree.Delete(e);
		} else {
			p = Find(Tree, e.l);
			if (!p) cout << "W drzewie nie ma odcinka zawierajacego punktu " 
				<< e.l << endl;
			else cout << "Punkt " << e.l << " zawiera odcinek (" 
				<< p->l << "," << p->r << ")" << endl;
		}
	}
	return 0;
}
