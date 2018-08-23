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
#include <set>
#include <map>
// Drzewo sufiksowe
template<typename _T> struct SufTree { 
// Struktura reprezentujaca wezel drzewa
	struct SufV {
// Mapa synow wezla
		map<char, SufV*> sons;
// Poczatek oraz koniec tekstu reprezentowanego przez krawedz prowadzaca do wezla
		int p, k;
// Czy wezel reprezentuje sufiks slowa
		bool s;
// Obiekt reprezentuje dodatkowe wzbogacenie wezla, ktore moze byc wykorzystywane 
// przez algorytmy korzystajace z drzew sufiksowych
		_T e;
// Wskaznik na ojca w drzewie
		SufV *par;
// Konstruktor wezla
		SufV(int p, int k, SufV *par, bool s) : p(p), k(k), par(par), s(s) {}
// Destruktor wezla usuwa wszystkich synow
		~SufV() {
			FOREACH(it, sons) delete it->second;
		}
	};
// Struktura wykorzystywana do konstrukcji drzewa sufiksowego - sluzy do 
// reprezentacji tablic lnk i test
	struct VlP {
		SufV *p;
		char l;
		VlP(SufV *p, char l) : p(p), l(l) {}
		bool operator<(const VlP &a) const {
			return (a.p > p) || (a.p == p && a.l > l);
		}
	};
// Korzeñ drzewa
	SufV root;
// Tekst, dla ktorego zostalo zbudowane drzewo sufiksowe
	string  text;
	SufTree(const string& t) : root(0, 0, 0, 0), text(t) {
		map<VlP, SufV*> lnk;
		set<VlP> test;
		int len = t.length();
// Stworz pierwszy wezel drzewa reprezentujacy ostatnia litere slowa
		SufV *v = root.sons[t[len - 1]] = new SufV(len - 1, len, &root, 1);
		lnk[VlP(&root, t[len - 1])] = v;
		test.insert(VlP(&root, t[len - 1]));
// Dla kolejnych sufiksow slowa (od najkrotszych do najdluzszych)...
		FORD(i, len - 2, 0) {
			char a = t[i];
// Jesli z korzenia nie wychodzi krawedz dla litery slowa na pozycji i...
			if (!root.sons[a]) {
// Nastepuje aktualizacja tablicy test dla wezlow na sciezce od wezla 
// reprezentujacego poprzedni sufiks do korzenia
				SufV* it = v;
				while(it) { 
					test.insert(VlP(it, a));
					it = it->par;
				}
				it = v;
// Dodanie nowego syna dla korzenia
				lnk[VlP(it, a)] = v = root.sons[t[i]] = new SufV(i, len, &root, 1);
			} else {
// Przy wykorzystaniu tablic test oraz lnk nastepuje wyznaczenie krawedzi drzewa,
// ktora trzeba podzielic w celu dodania kolejnego sufiksu
				char lw;
				SufV *head, *head2, *x, *x1;
				int lw2 = 0, gl = 0;
				for(x = v; x != &root && test.find(VlP(x, a)) == test.end(); 
					x = x->par) lw2 += x->k - x->p;
				for(x1 = x; x1 && !lnk[VlP(x1, a)]; x1 = x1->par) {
					gl += x1->k - x1->p;
					lw = t[x1->p];
				}
				if (x1) gl--;
// Nastepuje podzial krawedzi drzewa sufiksowego
				SufV* head1 = x1 ? lnk[VlP(x1, a)] : &root;
				if (x == x1) head = head1; else {
					head2 = (!x1) ? root.sons[a] : head1->sons[lw];
					head = head1->sons[t[head2->p]] = 
						new SufV(head2->p, head2->p + 1 + gl, head1, 0);
					head->sons[t[head->k]] = head2;
					head2->p = head->k;
					head2->par = head;
					for(VAR(it, test.lower_bound(VlP(head2, 0))); it->p == head2;) 
						test.insert(VlP(head, (it++)->l));
				}
// Aktualizacja zawartosci tablic test oraz lnk
				for(SufV* it = v; it != x1; it = it->par) test.insert(VlP(it, a));
				lnk[VlP(x, a)] = head;
				SufV *v1 = v;
				v = head->sons[t[len - lw2]] = new SufV(len - lw2, len, head, 1);
				lnk[VlP(v1, a)] = v;
			}
		}
	}
};
// Funkcja wyznacza liczbe roznych podslow w tekscie poprzez zliczanie dlugosci krawedzi w drzewie sufiksowym
template<typename T> int STSubWords(typename SufTree<T>::SufV& v) {
	int r = v.k - v.p;
	FOREACH(it, v.sons) r += STSubWords<T>(*(it->second));
	return r;
}
int main() {
	string text;
// Wczytaj kolejne teksty
	while(cin >> text) {
// Zbuduj drzewo sufiksowe
		SufTree<int> tree(text);
// Wyznacz liczbe roznych podslow
		cout << text << " ma " << STSubWords<int>(tree.root) << " podslow" << endl;
	}
	return 0;
}
