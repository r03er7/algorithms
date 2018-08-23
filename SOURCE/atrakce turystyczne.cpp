#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>
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
int const M=20200;
int const K=22;
int g;

/* Cztery makra parametryzujace zestaw operacji.
 * NIE dziala tylko f1=max, f2=+ */
#define f1(x, y) (x + y)
#define f2(x, y) max(x, y)
#define wiele(x, n) (x) /* f2(x,x,...,x) */
#define PUSTY 0 /* f2 od przedzialu bez wartosci */

#define MAX_N 60000
#define LOG_MAX_N 25 /* stala nieco wieksza od log(MAX_N) */

int w[4 * MAX_N], W[4 * MAX_N]; /* wartosci w i W */
int n; /* Zakres wartosci punktow to: [0,n-1]. */
int ile; /* najmniejsza potega dwojki >=n */


/* [a,b] - przedzial, c - ustawiana wartosc */
inline void insert(int a, int b, int c) {
  /* Operacje w lisciach. W przypadku niektorych kombinacji operacji
   * "if (a != b)" jest istotne, a dla innych nie szkodzi. */
  int va = ile + a, vb = ile + b;
  w[va] = f1(w[va], c);
  if (a != b) w[vb] = f1(w[vb], c);

  /* Spacer wskazniczkami va i vb do korzenia, polaczony z aktualizacjami
   * odpowiednich wartosci w i W. */
  int d = 0; /* odleglosc od najblizszego liscia (=wysokosc-glebokosc) */
  while (va != 1) {
    if (va / 2 != vb / 2) {
      if (va %2 == 0) w[va + 1] = f1(w[va + 1], c);
      if (vb %2 == 1) w[vb - 1] = f1(w[vb - 1], c);
    }
    va /= 2; vb /= 2;
    W[va] = f2(f1(W[2 * va],wiele(w[2 * va], (1 << d))),
               f1(W[2 * va + 1],wiele(w[2 * va + 1], (1 << d))));
    W[vb] = f2(f1(W[2 * vb],wiele(w[2 * vb], (1 << d))),
               f1(W[2 * vb + 1],wiele(w[2 * vb + 1], (1 << d))));
    d++;
  }
}


/* Makro pomocnicze do pierwszego spaceru do korzenia w zapytaniu. Jest ono
 * interesujace samo w sobie, gdyz l parametryzuje NAZWY zmiennych (dlatego
 * to musi byc makro, a nie np. funkcja). */
#define droga(l) do { \
  int w##l = 0, v##l = ile + l; \
  while (v##l != 0) { \
    pom##l[w##l++] = w[v##l]; \
    v##l /= 2; \
  } \
  for (int j = w##l - 2; j >= 0; j--) \
    pom##l[j] = f1(pom##l[j], pom##l[j + 1]); \
} while (0)

/* [a,b] - przedzial */
inline int query(int a, int b) {
  /* W przypadku zapytania chec uzyskania nierekurencyjnej implementacji sporo
   * utrudnia. Wykonujemy przez to dwa przebiegi od lisci do korzenia.
   * W pierwszym wyznaczamy sumy czesciowe sumarycznych wkladow (tablice poma
   * i pomb) wartosci w na sciezkach od wezlow do korzenia do wyniku (sa to
   * albo maksima, albo sumy). */
  int poma[LOG_MAX_N], pomb[LOG_MAX_N];
  droga(a); droga(b);
  int va = ile + a, vb = ile + b;

  /* W drugim przebiegu wyznaczamy wynik na podstawie wynikow dla przedzialow
   * bazowych z rozkladu [a,b]. */
  int wynik = ((va != vb) ? f2(poma[0], pomb[0]) : poma[0]);
  int d = 0; /* odleglosc od najblizszego liscia (=wysokosc-glebokosc) */
  while (va / 2 != vb / 2) {
    if (va % 2 == 0) wynik = f2(wynik, f1(wiele(f1(poma[d + 1], w[va + 1]), (1 << d)), W[va + 1]));
    if (vb % 2 == 1) wynik = f2(wynik, f1(wiele(f1(pomb[d + 1], w[vb - 1]), (1 << d)), W[vb - 1]));
    va /= 2; vb /= 2;
    d++;
  }
  return wynik;
}

void init() {
  ile = 2;
  while (ile < n) ile *= 2;
  for (int i = 1; i < 2*ile; i++) w[i] = W[i] = PUSTY;
}









vector<vector<int> > krawedzie(M);

int spojne[M], przetwarzane[M], liczniki[M];
int odleglosc[K][K];
int n,m,ile,k;
struct edge {
     int v;
     int l; //v-wierzchołek, l-odległość od źródła
     // int rev;//krawedz przeciwan pozycja na wektorze
     bool operator<(const edge &b) const {
          return l>b.l;
     }
} tmp,akt;
vector<vector<edge> > G;
int ogr[K+2];
int find(int a)
{
     if (spojne[a] < 0)
          return a;
     else
          return spojne[a] = find(spojne[a]);
}
void unin(int a, int b)
{
     a = find(a);
     b = find(b);
     if (a!=b) {
          if (spojne[a] > spojne[b])
               swap(a,b);
          spojne[a]+=spojne[b];//sumowanie mocy
          spojne[b] = a;//mniejszy jet reprezentantem
     }
}

void buildG()
{
     scanf("%d %d %d",&n,&m,&k);
     G.resize(n);
     REP(i,m) {
          int a,b,c;
          scanf("%d %d %d",&a, &b,&c);
          --a;
          --b;
          tmp.v=b;
          tmp.l=c;
          G[a].push_back(tmp);
          tmp.v=a;
          G[a].push_back(tmp);
     }
     REP(x, k+1) ogr[x] = 0;
     scanf("%d",&g);
     scanf("%d", &g);
     REP(x, g) {
          int a,b,c;
          scanf("%d %d", &a, &b);
          ogr[b-1] |= (1<<(a-2));
     }

}
inline int Bity(int b)
{
     int r=0;
     while(b) {
          r++;
          b &= (b-1);
     }
     return r;
}
void binar(int i)
{
    for (i ; i >= 1 ; i=i/2)
    {
     if (i%2)
         cout << "1";
     else cout << "0";
     }cout<<endl;
}
int main()
{int y;int k=3;int z;

     REP(x, 1<<k){ y = x+1 + (__builtin_popcount(x+1) << k+1);//sortowanie poo mpcy zbioru
  binar(x+1);
  binar(y);

  z=y;
  z&= (1<<4)-1;
  binar(z);
  cout<<endl;

     }

  //sort(zb, zb + (1<<k));//
  //REP(x,1<<k) zb[x] &= (1<<MaxK)-1;
      return 0;
 }
