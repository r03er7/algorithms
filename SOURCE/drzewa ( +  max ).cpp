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
int const MAX_N=100000;
using namespace std;
//( +  max )
int w[2 * MAX_N], W[2 * MAX_N]; /* wartosci w i W */
int n; /* Zakres wartosci punktow to: [0,n-1]. */
int M; /* najmniejsza potega dwojki >=n */


/* [a,b] - przedzial, c - ustawiana wartosc */
inline void insert(int a, int b, int c)
{
     int va = M + a, vb = M + b;
     w[va] += c;
     W[va] +=c;

     if(va!=vb) {
          W[vb]+=c;
          w[vb]+=c;
     }

     while (va >= 1) {
          if (va<vb-1) {
               if (va %2 == 0) {

                    w[va + 1] +=c;
                    W[va+1]+=c;
               }
               if (vb %2 == 1) {

                    w[vb - 1] +=c;
                    W[vb-1]+=c;
               }
          }

          if(vb<M) {
               W[va] =max(W[2 * va],W[2 * va + 1])+w[va];
               W[vb] = max(W[2 * vb],W[2 * vb + 1]) +w[vb];
          }
          va /= 2;
          vb /= 2;
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

inline int query(int a, int b)
{

     int va = M + a, vb = M + b;
     int res=0;
     while (va>=1) {

          res=max(res,w[vb]);
          res=max(res,w[va]);
          if(va<vb-1) {


               if (va % 2 == 0){
               res=max(res, W[va + 1]);

               }
               if (vb % 2 == 1) {

               res=max(res,W[vb-1]);

               }
          }

          va /= 2;
          vb /= 2;
     }
     return res;
}

void init()
{
     M = 2;
     while (M < n) M *= 2;
    REP(i,2*M) w[i] = W[i] = 0;
}

int main()
{n=8;
init();
insert(1,3,4);
insert(2,5,5);
cout<<query(4,5);

     return 0;
}

