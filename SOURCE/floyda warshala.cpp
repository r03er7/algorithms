#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <cstdio>
#include <vector>
#include <queue>
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
int const MAX=1000;//131072;

#define INF 1000000000 //nieskończoność
#define MAX 10000 //maksymalna liczba wierzchołków
using namespace std;
int n,m;
int  t[MAX][MAX];
int  s[MAX][MAX];
void buildG()
{
     scanf("%d %d", &n,&m);

     REP(k,n)REP(i,n)t[k][i]=INF,s[t][i]=-1;

     REP(x,n)t[x][x]=0;
     REP(x,m) {
          int a,b,c;
          scanf("%d %d %d", &a, &b,&c);
          --a;
          --b;
          t[a][b]=c;
          t[b][a]=c;
     }
}

void fordw()
{


     REP(k,n)REP(i,n)REP(j,n)
     t[i][j]=min(t[i][j],t[i][k]+t[k][j]);

}
int main()
{
     buildG();
     fordw();
     return 0;
}
