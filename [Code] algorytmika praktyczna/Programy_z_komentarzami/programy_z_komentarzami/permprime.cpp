#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <bvector.h>

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
namespace PermAntyLex {
// Wskaznik na wektor liczb reprezentujacych generowana permutacje
	VI* V;
// Wskaznik na funkcje, ktora jest wywolywana dla kazdej wygenerowanej permutacji
	void (*fun)(VI&);
// Funkcja rekurencyjna, wyznaczajaca wszystkie m-elementowe permutacje
	void Perm(int m) {
		if (!m) fun(*V); else
		FOR(i,0,m) {
			Perm(m-1);
			if(i<m) {
// Zamiana miejscami elementu i-tego oraz m-1-szego
				swap((*V)[i],(*V)[m]);
// Odwrocenie kolejnosci wszystkich elementow na przedziale [0..m-1]. W miejscu tym wykorzystywana jest niejawna informacja na temat budowy wektorow, gdyby elementy nie znajdowaly sie w pamieci w postaci ciaglej, nie wolno byloby skorzystac z funkcji reverse
				reverse(&(*V)[0],&(*V)[m]);
			}
		}
	}
// Wlasciwa funkcja wywolywana z zewnatrz przestrzeni nazw PermAntyLex
	void Gen(VI& v, void (*f)(VI&)) {
		V=&v; fun=f; Perm(SIZE(v)-1);
	}
};
namespace PermMinTr { 
// Wskaznik na wektor liczb reprezentujacych generowana permutacje
	VI* V;
// Wskaznik na funkcje, ktora jest wywolywana dla kazdej wygenerowanej permutacji
	void (*fun)(VI&);
// Funkcja rekurencyjna, wyznaczajaca wszystkie m-elementowe permutacje 
	void Perm(int m){
		if(m == 1) fun(*V); else
		REP(i, m) {
			Perm(m - 1);
			if(i < m - 1) swap((*V)[(!(m & 1) && m > 2) ? 
				(i < m - 1) ? i : m - 3 : m - 2], (*V)[m - 1]);
		}
	}
// Wlasciwa funkcja wywolywana z zewnatrz przestrzeni nazw PermAntyLex
	void Gen(VI& v, void (*f)(VI&)) {
		V = &v; 
		fun = f; 
		Perm(SIZE(v));
	}
};
// Funkcja realizuje algorytm sita Eratostenesa
bit_vector Sieve(int s) { 
	bit_vector V(s+1,1);
	V[0] = V[1] = 0;
// Dla kolejnej liczby, jesli nie zostala ona wykreslona, to wykresl wszystkie jej wielokrotnosci
	FOR(x, 2, s) if(V[x] && LL(s) >= LL(x) * LL(x)) 
		for(int y = x * x; y <= s; y += x) V[y] = 0;
	return V;
}
bit_vector primes;
int off[10];

// Funkcja jest modyfikacja funkcji PermMinTrAdj, ktora sprawdza, czy dla danej sekwencji cyfr, liczba ktora ta sekwencja reprezentuje jest permutacyjnie-antypierwsza
bool Perm(VI& p) {
	int x,k,i=0,s=p.size(), sum = 0;
	VI c(s, 1);
	vector<bool> pr(s, 1);
	c[s-1] = 0;
	while(i < s-1) {
		i=x=0;
		while(c[i] == s-i) {
			pr[i]=!pr[i];
			if(pr[i]) x++;
			c[i++]=1;
		}
		if(i < s-1) {
			k = pr[i] ? c[i]+x : s-i-c[i]+x;
			swap(p[k-1], p[k]);
// Zaktualizuj roznice wartosci miedzy analizowana liczba a aktualna permutacja
			sum += off[k-1]*(p[k-1] - p[k]);
// Jesli roznica jest postaci 9*liczba_pierwsza, to zwroc prawde
			if (abs(sum) < 1111111 && primes[abs(sum)])
				return true;
			c[i]++;
		}
	}
	return false;
}

// Funkcja dla zadanej liczby generuje jej reprezentacje w postaci wektora cyfr
VI Digit(int v) {
	VI res;
	while(v) {
		res.PB(v%10);
		v/=10;
	}
	return res;
}

int main() {
	int n,a,b;
// Wyznacz liczby pierwsze z zakresu [0..1111111]
	primes = Sieve(1111111);
// Oblicz wartosci 10^n, potrzebne do pozniejszego szybkiego aktualizowania roznicy wartosci permutacji
	off[0] = 1;
	FOR(x,1,9) off[x] = 10*off[x-1];
// Wczytaj liczbe testow
	cin >> n;
	while(n--) {
// Wczytaj zakres [a..b]
		cin >> a >> b;
		int res = 0;
// Dla kazdej liczby w zakresie...
		FOR(x,a,b) {
// Wygeneruj jej rozklad na cyfry
			VI v = Digit(x);
// Sprawdz, czy wektor cyfr zachowuje wlasnosc liczb permutacyjnie-pierwszych
			if (Perm(v)) res++;
		}
// Wypisz wynik
		cout << res << endl;
	}
	return 0;
}
