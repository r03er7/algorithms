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
int n;//dlugosl
int *P;//prefiks
int *s;//slowo
//funkcja prefikosowa
void pref1d(){
P[1] = 0;
int t = P[1];
for (int i = 2; i <= n; i++) {
     // Niezmiennik: t=P[i-1]
     while (t > 0 && s[t + 1] != s[i]) t = P[t]; // COFANIE SIE DO ODPOWIEDNIEGO PREFI SUF
     if (s[t + 1] == s[i]) t++;//PRZYPASOWALO TO PRZEDLURAMY/ALBO ZERO
     P[i] =  t;
}
}
//KMP 1 wzorzec pref1d od lowa w#s P[i]=w i= w+1 w+n
//KMP 2 dlai>=w+1 pamietamy tylko poprzednie p[i+i];
VI Pref(char* text) {
	int k=0,q;
	VI pre(string(text).length(),0);//strlen(text)
    for(q=1;text[q];q++) {
		while(k>0 && text[k] != text[q]) k=pre[k-1]; if(text[k]==text[q]) k++;
		pre[q]=k;
    }
	return pre;
}


int main() {

	return 0;
}
