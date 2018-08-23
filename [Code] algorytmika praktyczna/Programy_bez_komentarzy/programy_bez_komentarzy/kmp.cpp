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
void KMP(const char* str,const char* wzo, void (*fun)(int)) { 
#define KMPH(z) while(k > 0 && wzo[k] != z[q]) k = p[k]; if(wzo[k] == z[q]) k++;
	int p[strlen(wzo) + 1], k = 0, q, m;
	p[1] = 0;
	for (q = 1; wzo[q]; q++) {
		KMPH(wzo);
		p[q + 1] = k;
	}
	m = q;
	k = 0;
	for (q = 0; str[q]; q++) {
		KMPH(str);
		if(m == k) {
			fun(q - m + 1); 
			k = p[k];
		}
	}
}
void Disp(int x) {
	cout << "Znaleziono wystapienie wzorca na pozycji " << x << endl;
}

int main() {
	string pattern, text;
	cin >> text >> pattern;
	cout << "Wyszukiwanie " << pattern << " w " << text << endl;
	KMP(text.c_str(), pattern.c_str(), Disp);
	return 0;
}
