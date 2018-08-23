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
using namespace std;

/* Cztery makra parametryzujace zestaw operacji.
 * NIE dziala tylko f1=max, f2=+ */
#define f1(x, y) (x + y)
#define f2(x, y) max(x, y)
#define wiele(x, n) (x) /* f2(x,x,...,x) */
#define PUSTY 0 /* f2 od przedzialu bez wartosci */


int const MAX_N =60000;
int const LOG_MAX_N =25;
int w[4 * MAX_N], W[4 * MAX_N];
int n;
int M;
/* [a,b] - przedzial, c - ustawiana wartosc */
inline void insert(int a, int b, int c) {
  int va = M + a, vb = M + b;
  w[va] = f1(w[va],c);
  if (a != b) w[vb] = f1(w[vb], c);

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
#define droga(l) do { \
  int w##l = 0, v##l = M + l; \
  while (v##l != 0) { \
    pom##l[w##l++] = w[v##l]; \
    v##l /= 2; \
  } \
  for (int j = w##l - 2; j >= 0; j--) \
    pom##l[j] = f1(pom##l[j], pom##l[j + 1]); \
} while (0)

inline int query(int a, int b) {

  int poma[LOG_MAX_N], pomb[LOG_MAX_N];
  droga(a); droga(b);
  int va = M + a, vb = M + b;

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
  M = 2;
  while (M < n) M *= 2;
  for (int i = 1; i < 2*M; i++)
  w[i] = W[i] = 0;
}

int main() {
  int N, M, Z;
  scanf("%d%d%d", &N, &M, &Z);
  n = N - 1; /* gdyz licza sie odcinki miedzy stacjami, a nie same stacje */
  init();
  while (Z--) {
    int p, k, l;
    scanf("%d%d%d", &p, &k, &l);
    p--; k -= 2;
    if (query(p, k) + l > M)
      puts("N");
    else {
      puts("T");
      insert(p, k, l);
    }
  }
  return 0;
}

