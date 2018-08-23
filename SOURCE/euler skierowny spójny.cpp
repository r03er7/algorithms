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
#define MP make_pair
int const M=8;//131072;

#define INF 1000000000 //nieskończoność
#define MAX 100000 //maksymalna liczba wierzchołków
using namespace std;
int n;
vector <int> t[MAX];
vector<int> wynik;
set<pair<int,int> >krawedzie;

void dfs(int v)
{//euler
     while(!t[v].empty()) {
          int w=t[v].back();
          t[v].pop_back();
          dfs(w);
          wynik.PB(v);
     }
}

int main()
{
     cin>>n;
     REP(x,n) {
          int a,b;
          cin>>a;
          cin>>b;
          t[a].PB(b);
     }
     dfs(0);
     FORD(i,n-1,0)cout<<wynik[i]<<" ";
     return 0;
}
