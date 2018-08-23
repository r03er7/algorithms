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
#define MP make_pair
// Funkcja wyznacza tablice prefiksowa dla danego tekstu
VI Pref(char* text) {
	int k=0,q;
	VI pre(string(text).length(),0);//strlen(text)
    for(q=1;text[q];q++) {
		while(k>0 && text[k] != text[q]) k=pre[k-1]; if(text[k]==text[q]) k++;
		pre[q]=k;
    }
	return pre;
}
// Funkcja wyszukuje wystapienia wzorca w tekscie i dla kazdego znalezionego wystapienia wywoluje funkcje fun
void KMP(const char* str,const char* wzo, void (*fun)(int)) {
#define KMPH(z) while(k > 0 && wzo[k] != z[q]) k = p[k]; if(wzo[k] == z[q]) k++;
	int p[string(wzo).length() + 1], k = 0, q, m;//trlen(wzo)
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
int lpos, pos, res, len;
char s[500001];
bool cover;

// Funkcja sprawdzajaca, czy wyszukiwany wzorzec w tekscie pokrywa caly tekst (czy wzorzec jest szablonem dla tekstu)
void Check(int x) {
	if (x > pos+lpos) cover = false;
	lpos = x;
}

int main() {
// Wczytaj tekst
	cin >> s;
// Wyznacz tablice prefiksowa
	VI pr = Pref(s);
	res = pos = len = strlen(s);
// Przetwarzaj kolejne prefiksy tekstu bedace jednoczesnie sufiksami
	while(pos) {
// Jesli kolejny prefiks jest krotszy o polowe (lub wiecej), to sprawdz, czy aktualny prefiks jest szablonem
		if (pr[pos-1] <= pos/2) {
			cover = true; lpos = 0;
			KMP(s, s+len-pos, Check);
			if (cover) res = pos;
		}
// Przejdz do kolejnego prefiksu
		pos = pr[pos-1];
	}
// Wypisz wynik
	cout << res << endl;
	return 0;
}
