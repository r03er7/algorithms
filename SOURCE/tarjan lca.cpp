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
int const M=8;//131072;

#define INF 1000000000 //nieskończoność
#define MAX 100000 //maksymalna liczba wierzchołków
using namespace std;
vector <int> g[MAX];
int a,b,n,m; //n-wierzchołków, m-krawędzi
bool color[MAX];
int ancestor[MAX];
int ile=0;//ile zbiorow
vector<int> reprezentant,ranga,jaki;
//FU spojne przetwarzane
void Makeset(int x)
{
     //reprezentant[ile]= ile;
     jaki[ile]=x;
     reprezentant[x]=ile;
     ranga[ile]=-1;
     ++ile;

}
int find(int a)
{
     if (ranga[a] < 0)
          return a;
     else
          return ranga[a] = find(ranga[a]);
}
void unin(int a, int b)
{
     a = find(a);
     b = find(b);
     if (a!=b) {
          if (ranga[a] > ranga[b])
               swap(a,b);
          ranga[a]+=ranga[b];//sumowanie mocy
          ranga[b] = a;//mniejszy jet reprezentantem
     }
}
void tarjanLCA(int u)
{
     Makeset(u);
     ancestor[find(reprezentant[u])]=reprezentant[u];

     FOREACH(it,g[u])if(*it!=u) {//kazdy syn
          tarjanLCA(*it);
          unin(reprezentant[u],reprezentant[*it]);
          ancestor[find(reprezentant[u])]=reprezentant[u];
     }
     color[u]=1;

   /*  REP(i,3) {
          if(color[i]&&(i!=u)) {
          cout<<"LCA "<<i<<" "<<u<<" = "<<ancestor[find(reprezentant[i])]<<endl;

          }

     }
     */
}
void write(){
REP(x,5)Makeset(x*2);
     REP(x,5)cout<<ranga[x]<<" ";
     cout<<endl;
      REP(x,5)cout<<jaki[find(x)]<<" ";
cout<<endl;
REP(x,5)cout<<reprezentant[x*2]<<" ";
cout<<endl;

}
void eulerlca(int root){



}
void kruskal(){


}
int main()
{
     n=50;
     reprezentant.resize(n);
     ranga.resize(n);
     jaki.resize(n);

     REP(x,3)color[x]=0;
     g[0].PB(1);
     g[1].PB(0);
     g[0].PB(2);
     g[2].PB(0);
      tarjanLCA(0);



     return 0;
}
