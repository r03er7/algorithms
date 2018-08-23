#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
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
const int INF = 1000000001;





   int main()
   {int n, max;
     cin>>n;
     max = 0;
int   anti[]={1,2,4,6,12,24,36,48,120,180,240,360,720,840,1260,2520,5024,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,554400,665280,720720,10811080,1441440,2162160,2882880,3603600,4324320,6486480,7207200,8648640,10810800,14414400,17297280,21621600,32432400,36756720,43243200,61261200,73513440,110270160,122522400};
     for (int k = 122522400; k <= n; k+=10)
    {

     int ile = 0;
      int j = 1;
      while (j * j < k)
      {
        /* analizujemy liczby od 1 do pierwiastka z k w poszukiwaniu
17           dzielnikow */
        if (k % j == 0)
          ile += 2; /* mamy 2 dzielniki: j i k/j */
        j++;
      }
      if (j * j == k) /* mamy dzielnik - pierwiastek z k */
        ile++;
      if (ile > max)
      {
        /* liczba jest antypierwsza */
        max = ile;
        cout<<k<<" ";
      }
    }
    return 0;
      }

