#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
typedef vector<int> VI;
typedef long long LL;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
// Funkcja wyznacza tablice prefiksowa dla danego tekstu
VI Pref(char* text) {
	int k=0,q;
	VI pre(string(text).length(),0);//strlen(text)
    for(q=1;text[q];q++) {//cout<<int(text[q+1])<<" ";
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
	cin >> s;
	VI pr = Pref(s);
	//FOREACH(it,pr)cout<<*it<<" ";
	res = pos = len = string(s).length();
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
