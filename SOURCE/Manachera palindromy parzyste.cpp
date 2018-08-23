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
int const MAXN=10000;
int n;//dlugosl
int *P;//prefiks
vector<char> s;//slowo
vector<int> R;
//funkcja prefikosowa
void manecherparzste()
{
R.resize(n);
     int i=0,t=0;
     R[0]=0;
     while (i<n) {
          //t<=R[i]
          while((i+t+1)<n &&s[i-t]==s[i+1+t])++t;
          //t=R[i];
          int k=1;
          while( k<=R[i] && R[i-k]!=(R[i]-k)) {
               R[i+k]=min(R[i-k],R[i]-k);
               ++k;
          }
          i+=k;
          t-=k;
     }
}void men(){
s[0] = '#'; s[n + 1] = '$'; // Strażnicy, żeby nie musieć wypisywać ifów w stylu "czy nie wyszliśmy poza słowo".
R[0] = 0;
int i = 1;
int t = 0; // Zbieżność nazw zmiennych t z tego kodu i kodu KMP jest nieprzypadkowa.
while (i <= n)
{
   // Niezmiennik: t ≤ R[i], czyli innymi słowy: musimy jeszcze spróbować poszerzyć
   // palindrom o środku w i, który już mamy.
   // No to poszerzamy:
   while (s[i - t] == s[i + t + 1]) t++;
   R[i] = t;

   // Stosujemy obserwację pod daszkiem, dopóki możemy.
   int k = 1;
   while (k <= t && R[i - k] != R[i] - k)
   {
      R[i + k] = min(R[i - k], R[i] - k));
      k++;
   }
   // Skoro wyszliśmy z pętli, to nierówność R[i-k] ≠ R[i]-k z obserwacji nie jest
   // spełniona (albo k > t, ale to jest dużo łatwiejszy przypadek). To oznacza, że
   // daszek nad pozycją i+k jest co najmniej równy R[i]-k (=R[i-k]), ale potencjalnie może
   // być większy. Kwestię ewentualnego powiększenia rozwiąże kolejny przebieg zewnętrznej
   // pętli while, który zacznie od pozycji i+k i będzie próbował powiększać t - czyli zrobi
   // dokładnie to, co trzeba.
   t -= k; t = max(0, t);
   i += k;
}
}
int main()
{
n=10;
s.resize(n);
REP(x,n)scanf("%c",&s[x]);
manecherparzste();
FOREACH(it,R)cout<<*it<<" ";
     return 0;
}
